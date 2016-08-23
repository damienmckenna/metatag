<?php

/**
 * @file
 * Contains \Drupal\metatag\Normalizer\FieldItemNormalizer.
 */

namespace Drupal\metatag\Normalizer;

use Drupal\Core\Field\FieldItemInterface;
use Symfony\Component\Serializer\Exception\InvalidArgumentException;
use Drupal\serialization\Normalizer\NormalizerBase;

/**
 * Converts the Metatag field item object structure to METATAG array structure.
 */
class FieldItemNormalizer extends NormalizerBase {

  /**
   * The interface or class that this Normalizer supports.
   *
   * @var string
   */
  protected $supportedInterfaceOrClass = 'Drupal\metatag\Plugin\Field\FieldType\MetatagFieldItem';

  /**
   * Implements \Symfony\Component\Serializer\Normalizer\NormalizerInterface::normalize()
   */
  public function normalize($field_item, $format = NULL, array $context = array()) {
    $values = $field_item->toArray();
    if (isset($context['langcode'])) {
      $values['lang'] = $context['langcode'];
    }

    if (strpos($format, 'json') !== false) {
        $tags = array();
        // Get serialized value and break it into an array of tags with values.
        $serialized_value = $field_item->get('value')->getValue();
        $tags += unserialize($serialized_value);
    }

    return array(
      'field_metatag' => [
        [
          'values' => $tags,
          'lang' => $values['lang']
        ]
      ]
    );
  }

}
