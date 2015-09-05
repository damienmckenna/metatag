<?php

/**
 * @file
 * Contains the \Drupal\metatag\MetatagManager class.
 */

namespace Drupal\metatag;

use Drupal\Core\Entity\ContentEntityInterface;

/**
 * Class MetatagManager.
 *
 * @package Drupal\metatag
 */
class MetatagManager {

  protected $groupPluginManager;
  protected $tagPluginManager;

  protected $tokenService;

  /**
   * Constructor for MetatagManager.
   *
   * @param MetatagGroupPluginManager $groupPluginManager
   * @param MetatagTagPluginManager $tagPluginManager
   * @param MetatagToken $token
   */
  public function __construct(MetatagGroupPluginManager $groupPluginManager,
                              MetatagTagPluginManager $tagPluginManager,
                              MetatagToken $token) {
    $this->groupPluginManager = $groupPluginManager;
    $this->tagPluginManager = $tagPluginManager;
    $this->tokenService = $token;
  }

  /**
   * Converts the metatags on an entity to a formatted array suitable to
   * use as attachments in hook_page_attachments().
   *
   * @param ContentEntityInterface $entity
   *
   * @return array
   */
  public function attachmentsFromEntity(ContentEntityInterface $entity) {
    $tags = array();
    $fields = $this->getFields($entity);

    foreach ($fields as $field_name => $field_info) {
      $tags = $this->getFieldTags($entity, $field_name);

      // No data found for this entity? Use the field's default values.
      if (empty($tags) && !empty($field_info->default_value[0]['value'])) {
        $tags = unserialize($field_info->default_value[0]['value']);
      }
    }

    $attachments = $this->generateElements($tags, $entity);

    return $attachments;
  }


  public function groupDefinitions() {
    return $this->groupPluginManager->getDefinitions();
  }

  public function tagDefinitions() {
    return $this->tagPluginManager->getDefinitions();
  }

  /**
   * Returns an array of group plugin information sorted by weight.
   *
   * @return array
   */
  public function sortedGroups() {
    $metatag_groups = $this->groupDefinitions();

    // Pull the data from the definitions into a new array.
    $groups = array();
    foreach ($metatag_groups as $group_name => $group_info) {
      $id  = $group_info['id'];
      $groups[$id]['label'] = $group_info['label']->render();
      $groups[$id]['description'] = $group_info['description'];
      $groups[$id]['weight'] = $group_info['weight'];
    }

    // Create the 'sort by' array.
    $sort_by = array();
    foreach ($groups as $group) {
      $sort_by[] = $group['weight'];
    }

    // Sort the groups by weight.
    array_multisort($sort_by, SORT_ASC, $groups);

    return $groups;
  }

  /**
   * Returns an array of tag plugin information sorted by group then weight.
   *
   * @return array
   */
  public function sortedTags() {
    $metatag_tags = $this->tagDefinitions();

    // Pull the data from the definitions into a new array.
    $tags = array();
    foreach ($metatag_tags as $tag_name => $tag_info) {
      $id  = $tag_info['id'];
      $tags[$id]['label'] = $tag_info['label']->render();
      $tags[$id]['group'] = $tag_info['group'];
      $tags[$id]['weight'] = $tag_info['weight'];
    }

    // Create the 'sort by' array.
    $sort_by = array();
    foreach ($tags as $key => $tag) {
      $sort_by['group'][$key] = $tag['group'];
      $sort_by['weight'][$key] = $tag['weight'];
    }

    // Sort the tags by weight.
    array_multisort($sort_by['group'], SORT_ASC, $sort_by['weight'], SORT_ASC, $tags);

    return $tags;
  }

  /**
   * Returns a weighted array of groups containing their weighted tags.
   *
   * @return array
   */
  public function sortedGroupsWithTags() {
    $groups = $this->sortedGroups();
    $tags = $this->sortedTags();

    foreach ($tags as $tag_id => $tag) {
      $tag_group = $tag['group'];

      if (!isset($groups[$tag_group])) {
        // If the tag is claiming a group that has no matching plugin, log an
        // error and force it to the basic group.
        \Drupal::logger('metatag')->error("Undefined group '%group' on tag '%tag'", array('%group' => $tag_group, '%tag' => $tag_id));
        $tag['group'] = 'basic';
        $tag_group = 'basic';
      }

      $groups[$tag_group]['tags'][$tag_id] = $tag;
    }

    return $groups;
  }

  /**
   * Builds the form element for a Metatag field.
   *
   * If a list of either groups or tags are passed in, those will be used to
   * limit the groups/tags on the form. If nothing is passed in, all groups
   * and tags will be used.
   *
   * @param array $values
   * @param array $element
   * @param array $included_groups
   * @param array $included_tags
   *
   * @return array
   */
  public function form(array $values, array $element, array $included_groups = NULL, array $included_tags = NULL) {

    // Add the outer fieldset.
    $element += array(
      '#type' => 'details',
    );

    // Add the token browser.
    $element['token_tree'] = \Drupal::service('metatag.token')->tokenBrowser();

    $groups_and_tags = $this->sortedGroupsWithTags();

    $first = TRUE;
    foreach ($groups_and_tags as $group_id => $group) {
      // Only act on groups that have tags and are in the list of included
      // groups (unless that list is null).
      if (isset($group['tags']) && (is_null($included_groups) || in_array($group_id, $included_groups))) {
        // Create the fieldset.
        $element[$group_id]['#type'] = 'details';
        $element[$group_id]['#title'] = $group['label'];
        $element[$group_id]['#description'] = $group['description'];
        $element[$group_id]['#open'] = $first;
        $first = FALSE;

        foreach ($group['tags'] as $tag_id => $tag) {
          // Only act on tags in the included tags list, unless that is null.
          if (is_null($included_tags) || in_array($tag_id, $included_tags)) {
            // Make an instance of the tag.
            $tag = $this->tagPluginManager->createInstance($tag_id);

            // Set the value to the stored value, if any.
            $tag_value = isset($values[$tag_id]) ? $values[$tag_id] : '';
            $tag->setValue($tag_value);

            // Create the bit of form for this tag.
            $element[$group_id][$tag_id] = $tag->form($element);
          }
        }
      }
    }

    return $element;
  }

  /**
   * Returns a list of the metatag fields on an entity.
   */
  protected function getFields(ContentEntityInterface $entity) {
    $field_list = array();

    if ($entity instanceof ContentEntityInterface) {
      // Get a list of the metatag field types.
      $field_types = $this->fieldTypes();

      // Get a list of the fields on this entity.
      $fields = $entity->getFields();

      // Iterate through all the fields looking for ones in our list.
      foreach ($fields as $key => $field) {
        // Get the field definition which holds the type.
        $field_info = $field->getFieldDefinition();

        // Get the field type, ie: metatag.
        $field_type = $field_info->getType();

        // Check the field type against our list of fields.
        if (isset($field_type) && in_array($field_type, $field_types)) {
          // Get the machine name of the field.
          $field_name = $field->getName();

          $field_list[$field_name] = $field_info;
        }
      }
    }

    return $field_list;
  }

  /**
   * Returns a list of the metatags with values from a field.
   *
   * @param $entity
   * @param $field_name
   */
  protected function getFieldTags(ContentEntityInterface $entity, $field_name) {
    $tags = array();
    foreach ($entity->{$field_name} as $item) {
      // Get serialized value and break it into an array of tags with values.
      $serialized_value = $item->get('value')->getValue();
      $tags += unserialize($serialized_value);
    }

    return $tags;
  }

  /**
   * Generate the elements that go in the attached array in
   * hook_page_attachments.
   *
   * @param $tags
   * @param $entity
   *
   * @return array
   */
  protected function generateElements($tags, $entity) {
    $metatag_tags = $this->tagPluginManager->getDefinitions();
    $elements = array();

    // Each element of the $values array is a tag with the tag plugin name
    // as the key.
    foreach ($tags as $tag_name => $value) {
      // Check to ensure there is a matching plugin.
      if (isset($metatag_tags[$tag_name])) {
        // Get an instance of the plugin.
        $tag = $this->tagPluginManager->createInstance($tag_name);

        // Render any tokens in the value.
        $value = $this->tokenService->tokenReplace($value, array('node' => $entity));

        // Tell the plugin what value to use for the metatag content.
        $tag->setValue($value);

        // Have the tag generate the output based on the value we gave it.
        $output = $tag->output();

        if (!empty($output)) {
          $elements['#attached']['html_head'][] = [
            $output,
            $tag_name
          ];
        }
      }
    }

    return $elements;
  }

  /**
   * Returns a list of fields handled by Metatag.
   *
   * @return array
   */
  protected function fieldTypes() {
    //@TODO: Either get this dynamically from field plugins or forget it and just hardcode metatag where this is called.
    return array('metatag');
  }

}
