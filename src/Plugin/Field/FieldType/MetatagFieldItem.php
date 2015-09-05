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
  public static function defaultStorageSettings() {
    return array(
      'max_length' => 255,
    ) + parent::defaultStorageSettings();
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

}
