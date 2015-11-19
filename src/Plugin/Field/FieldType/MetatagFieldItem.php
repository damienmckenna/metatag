<?php

/**
 * @file
 * Contains \Drupal\metatag\Plugin\Field\FieldType\MetatagFieldItem.
 */

namespace Drupal\metatag\Plugin\Field\FieldType;

use Drupal\Component\Utility\Random;
use Drupal\Core\Field\FieldDefinitionInterface;
use Drupal\Core\Field\FieldItemBase;
use Drupal\Core\Field\FieldStorageDefinitionInterface;
use Drupal\Core\TypedData\DataDefinition;
use Drupal\Core\Form\FormStateInterface;

/**
 * Plugin implementation of the 'metatag' field type.
 *
 * @FieldType(
 *   id = "metatag",
 *   label = @Translation("Meta tags"),
 *   description = @Translation("This field stores code meta tags."),
 *   default_widget = "metatag_firehose",
 *   default_formatter = "metatag_empty_formatter"
 * )
 */
class MetatagFieldItem extends FieldItemBase {

  /**
   * {@inheritdoc}
   */
  public static function schema(FieldStorageDefinitionInterface $field_definition) {
    return array(
      'columns' => array(
        'value' => array(
          'type' => 'text',
          'size' => 'big',
          'not null' => FALSE,
        ),
      ),
    );
  }

  /**
   * {@inheritdoc}
   */
  public static function propertyDefinitions(FieldStorageDefinitionInterface $field_definition) {
    $properties['value'] = DataDefinition::create('string')
      ->setLabel(t('Metatag'))
      ->setRequired(TRUE);

    return $properties;
  }

  /**
   * {@inheritdoc}
   */
  public function isEmpty() {
    $value = $this->get('value')->getValue();
    return $value === NULL || $value === '';
  }

  /**
   * Returns the default settings on the field.
   */
  public function getFieldDefaults() {
    return $this->getFieldDefinition()->getDefaultValueLiteral();
  }

  /**
   * {@inheritdoc}
   */
  public function preSave() {
    parent::preSave();

    // Get the field's default values.
    $field_default_tags_value =  $this->getFieldDefaults();
    $field_default_tags = unserialize($field_default_tags_value[0]['value']);

    // Get the value about to be saved.
    $current_value = $this->value;
    $current_tags = unserialize($current_value);

    // Only include values that differ from the default.
    // @TODO: When site defaults are added, account for those.
    $tags_to_save = array();
    foreach ($current_tags as $tag_id => $tag_value) {
      if ($tag_value != $field_default_tags[$tag_id]) {
        $tags_to_save[$tag_id] = $tag_value;
      }
    }

    // Update the value to only save overridden tags.
    $this->value = serialize($tags_to_save);
  }

}
