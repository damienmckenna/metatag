<?php
/**
 * @file
 * Contains \Drupal\metatag\Plugin\Field\FieldWidget\MetatagFirehose.
 */

namespace Drupal\metatag\Plugin\Field\FieldWidget;

use Drupal\Core\Field\FieldItemListInterface;
use Drupal\Core\Field\WidgetBase;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Field\FieldDefinitionInterface;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\metatag\MetatagManager;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Advanced widget for metatag field.
 *
 * @FieldWidget(
 *   id = "metatag_firehose",
 *   label = @Translation("Advanced meta tags form"),
 *   field_types = {
 *     "metatag"
 *   }
 * )
 */
class MetatagFirehose extends WidgetBase implements ContainerFactoryPluginInterface {

  /**
   * Instance of MetatagManager service.
   */
  protected $metatagManager;

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition) {
    return new static(
      $plugin_id,
      $plugin_definition,
      $configuration['field_definition'],
      $configuration['settings'],
      $configuration['third_party_settings'],
      $container->get('metatag.manager')
    );
  }

  /**
   * {@inheritdoc}
   */
  public function __construct($plugin_id, $plugin_definition, FieldDefinitionInterface $field_definition, array $settings, array $third_party_settings, MetatagManager $manager) {
    parent::__construct($plugin_id, $plugin_definition, $field_definition, $settings, $third_party_settings);
    $this->metatagManager = $manager;
  }

  /**
   * {@inheritdoc}
   */
  public function formElement(FieldItemListInterface $items, $delta, array $element, array &$form, FormStateInterface $form_state) {
    $item = $items[$delta];

    // Retrieve the values for each metatag from the serialized array.
    $values = array();
    if (!empty($item->value)) {
      $values = unserialize($item->value);
    }
    if (!empty($element['#field_parents']) && reset($element['#field_parents']) === 'default_value_input') {
      // We are on the default-values form, there won't be any default values
      // if the field has just been added - so we can return the form without
      // processing default values.
      return $this->metatagManager->form($values, $element);
    }

    // Fill in the default values for any tags that don't have stored values.
    $field_default_tags_value = $this->fieldDefinition->getDefaultValueLiteral();
    $field_default_tags = unserialize($field_default_tags_value[0]['value']);
    foreach ($field_default_tags as $tag_id => $tag_value) {
      if (!isset($values[$tag_id]) && !empty($tag_value)) {
        $values[$tag_id] = $tag_value;
      }
    }

    // Create the form element.
    $element = $this->metatagManager->form($values, $element);

    return $element;
  }

  /**
   * {@inheritdoc}
   */
  public function massageFormValues(array $values, array $form, FormStateInterface $form_state) {
    // Flatten the values array to remove the groups and then serialize all the
    // metatags into one value for storage.
    foreach ($values as &$value) {
      $flattened_value = array();
      foreach ($value as $group) {
        // Exclude the "original delta" value.
        if (is_array($group)) {
          foreach ($group as $tag_id => $tag) {
            $flattened_value[$tag_id] = $tag;
          }
        }
      }
      $value = serialize($flattened_value);
    }

    return $values;
  }

}
