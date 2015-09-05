<?php
/**
 * @file
 * Contains \Drupal\metatag\Plugin\metatag\Tag\MetaNameBase.
 */

/**
 * Each meta tag will extend this base.
 */

namespace Drupal\metatag\Plugin\metatag\Tag;

use Drupal\Component\Plugin\PluginBase;
use Drupal\Core\Form\FormStateInterface;

abstract class MetaNameBase extends PluginBase {
  /**
   * Machine name of the meta tag plugin.
   *
   * @var string
   */
  protected $id;

  /**
   * Official metatag name.
   *
   * @var string
   */
  protected $name;

  /**
   * The title of the plugin.
   *
   * @var \Drupal\Core\Annotation\Translation
   *
   * @ingroup plugin_translatable
   */
  protected $label;

  /**
   * A longer explanation of what the field is for.
   *
   * @var \Drupal\Core\Annotation\Translation
   *
   * @ingroup plugin_translatable
   */
  protected $description;

  /**
   * The category this meta tag fits in.
   *
   * @var string
   */
  protected $group;

  /**
   * The value of the metatag in this instance.
   *
   * @var mixed
   */
  protected $value;

  /**
   * {@inheritdoc}
   */
  public function __construct(array $configuration, $plugin_id, array $plugin_definition) {
    parent::__construct($configuration, $plugin_id, $plugin_definition);

    // Set the properties from the annotation.
    // @TODO: Should we have setProperty() methods for each of these?
    $this->id = $plugin_definition['id'];
    $this->name = $plugin_definition['name'];
    $this->label = $plugin_definition['label'];
    $this->description = $plugin_definition['description'];
    $this->group = $plugin_definition['group'];
    $this->weight = $plugin_definition['weight'];
  }

  public function id() {
    return $this->id;
  }
  public function label() {
    return $this->label;
  }
  public function description() {
    return $this->description;
  }
  public function name() {
    return $this->name;
  }
  public function group() {
    return $this->group;
  }
  public function weight() {
    return $this->weight;
  }

  /**
   * @return bool
   *   Whether this meta tag has been enabled.
   */
  public function isActive() {
    return TRUE;
  }

  /**
   * Generate a form element for this meta tag.
   */
  public function form(array $element) {
    $form = array(
      '#type' => 'textfield',
      '#title' => $this->label(),
      '#default_value' => $this->value(),
      '#maxlength' => 255,
      '#required' => $element['#required'],
      '#description' => $this->description(),
      '#element_validate' => array(array(get_class($this), 'validateTag')),
    );

    return $form;
  }

  protected function value() {
    return $this->value;
  }

  public function setValue($value) {
    $this->value = $value;
  }

  public function output() {
    if (empty($this->value)) {
      // If there is no value, we don't want a tag output.
      $element = '';
    }
    else {
      $element = array(
        '#tag' => 'meta',
        '#attributes' => array(
          'name' => $this->name,
          'content' => $this->value(),
        )
      );
    }

    return $element;
  }

  /**
   * Validates the metatag data.
   *
   * @param array $element
   *   The form element to process.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   The form state.
   */
  public static function validateTag(array &$element, FormStateInterface $form_state) {
    //@TODO: If there is some common validation, put it here. Otherwise, make it abstract?
  }
  
}
