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
class MetatagFirehose extends WidgetBase {

  /**
   * Instance of MetatagManager service.
   */
  protected $metatagManager;


  /**
   * {@inheritdoc}
   */
  public function __construct($plugin_id, $plugin_definition, FieldDefinitionInterface $field_definition, array $settings, array $third_party_settings) {
    parent::__construct($plugin_id, $plugin_definition, $field_definition, $settings, $third_party_settings);

    $this->metatagManager = \Drupal::service('metatag.manager');
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
