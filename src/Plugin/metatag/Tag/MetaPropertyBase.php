<?php
/**
 * @file
 * Contains \Drupal\metatag\Plugin\metatag\Tag\MetaPropertyBase.
 */

/**
 * This base plugin allows "property"-style meta tags, e.g. Open Graph tags, to
 * be further customized.
 */

namespace Drupal\metatag\Plugin\metatag\Tag;

use Drupal\Component\Plugin\PluginBase;
use Drupal\Core\Form\FormStateInterface;

abstract class MetaPropertyBase extends MetaNameBase {
  /**
   * Display the meta tag.
   */
  public function output() {
    if (empty($this->value)) {
      // If there is no value, we don't want a tag output.
      $element = '';
    }
    else {
      $element = array(
        '#tag' => 'meta',
        '#attributes' => array(
          'property' => $this->name,
          'content' => $this->value(),
        )
      );
    }

    return $element;
  }
}
