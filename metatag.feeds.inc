<?php

/**
 * @file
 * Feeds mapping implementation for the Metatag module.
 */

/**
 * Implements hook_feeds_processor_targets_alter().
 */
function metatag_feeds_processor_targets_alter(&$targets, $type, $bundle) {
  if (metatag_entity_supports_metatags($type)) {
    $info = metatag_get_info();
    foreach($info['tags'] as $name => $tag) {
      $targets['meta_' . $name] = array(
        'name'        => 'Metatag ' . check_plain($tag['label']),
        'callback'    => 'metatag_feeds_set_target',
        'description' => t('@label metatag.', array(
          '@label' => $tag['label'],
        )),
      );
    }
  }
}

/**
 * Callback function to set value of a metatag tag.
 */
function metatag_feeds_set_target($source, $entity, $target, $value) {

  // Don't do anything if we weren't given any data.
  if (empty($value)) {
    return;
  }

  $name = str_replace('meta_', '', $target);

  $entity->metatags[$name]['value'] = $value;
}

