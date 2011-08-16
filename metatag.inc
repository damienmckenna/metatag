<?php

interface DrupalMetaTagInterface {

  /**
   * Constructor
   *
   * @param array $info
   *   The information about the meta tag from metatag_get_info().
   */
  function __construct(array $info, array $data = array());

  function getForm();

  //function validateForm();

  //function processForm();

  function getElement();
}

abstract class DrupalDefaultMetaTag implements DrupalMetaTagInterface {
  private $info;
  private $data = array('value' => '');

  function __construct(array $info, array $data = NULL) {
    $this->info = $info;
    if (isset($data)) {
      $this->data = $data;
    }
  }
}

/**
 * Text-based meta tag controller.
 */
class DrupalTextMetaTag extends DrupalDefaultMetaTag {
  function __construct(array $info, array $data = NULL) {
    $this->info = $info;
    if (isset($data)) {
      $this->data = $data;
    }
  }

  public function getForm(array $options = array()) {
    $options += array(
      'token types' => array(),
    );

    $form['value'] = isset($this->info['form']) ? $this->info['form'] : array();

    $form['value'] += array(
      '#type' => 'textfield',
      '#title' => $this->info['label'],
      '#description' => !empty($this->info['description']) ? $this->info['description'] : '',
      '#default_value' => isset($this->data['value']) ? $this->data['value'] : '',
      '#element_validate' => array('token_element_validate'),
      '#token_types' => $options['token types'],
    );

    return $form;
  }

  public function getValue(array $options = array()) {
    $options += array(
      'token data' => array(),
      'clear' => TRUE,
    );

    $value = token_replace($this->data['value'], $options['token data'], $options);
    $value = trim(strip_tags($value));
    return $value;
  }

  public function getElement(array $options = array()) {
    $element = isset($this->info['element']) ? $this->info['element'] : array();

    $value = $this->getValue($options);
    if (strlen($value) === 0) {
      return array();
    }

    $element += array(
      '#tag' => 'meta',
      '#attributes' => array(),
      '#id' => 'metatag_' . $this->info['name'],
    );
    $element['#attributes'] += array(
      'name' => $this->info['name'],
      'content' => $value,
    );

    // Add header information if desired.
    if (!empty($this->info['header'])) {
      $element['#attached']['drupal_add_http_header'][] = array($this->info['header'], $value);
    }

    return array(
      '#attached' => array('drupal_add_html_head' => array(array($element, $element['#id']))),
    );
    return $element;
  }
}

class DrupalOptionsMetaTag extends DrupalDefaultMetaTag {
  function __construct(array $info, array $data = NULL) {
    $this->info = $info;
    if (isset($data)) {
      $this->data = $data;
    }
  }

  public function getForm(array $options = array()) {
    $options += array(
      'token types' => array(),
    );

    $form['value'] = isset($this->info['form']) ? $this->info['form'] : array();

    $form['value'] += array(
      '#type' => 'select',
      '#title' => $this->info['label'],
      '#description' => !empty($this->info['description']) ? $this->info['description'] : '',
      '#default_value' => isset($this->data['value']) ? $this->data['value'] : '',
      '#element_validate' => array('token_element_validate'),
      '#token_types' => $options['token types'],
    );

    return $form;
  }

  public function getValue(array $options = array()) {
    $options += array(
      'token data' => array(),
      'clear' => TRUE,
    );

    return token_replace($this->data['value'], $options['token data'], $options);
  }

  public function getElement(array $options = array()) {
    $element = isset($this->info['element']) ? $this->info['element'] : array();

    $value = $this->getValue($options);
    if (strlen($value) === 0) {
      return array();
    }

    $element += array(
      '#tag' => 'meta',
      '#attributes' => array(),
      '#id' => 'metatag_' . $this->info['name'],
    );
    $element['#attributes'] += array(
      'name' => $this->info['name'],
      'content' => $value,
    );

    // Add header information if desired.
    if (!empty($this->info['header'])) {
      $element['#attached']['drupal_add_http_header'][] = array($this->info['header'], $value);
    }

    return array(
      '#attached' => array('drupal_add_html_head' => array(array($element, $element['#id']))),
    );
    return $element;
  }
}

/**
 * Link type meta tag controller.
 */
class DrupalLinkMetaTag extends DrupalTextMetaTag {
  public function getElement(array $options = array()) {
    $element = isset($this->info['element']) ? $this->info['element'] : array();

    $value = $this->getValue($options);
    if (strlen($value) === 0) {
      return array();
    }

    $element += array(
      '#type' => 'html_tag',
      '#tag' => 'link',
      '#attributes' => array(),
      '#id' => 'metatag_' . $this->info['name'],
    );
    $element['#attributes'] += array(
      'rel' => $this->info['name'],
      'href' => $value,
    );

    if (!isset($this->info['header']) || !empty($this->info['header'])) {
      // Also send the generator in the HTTP header.
      $element['#attached']['drupal_add_http_header'][] = array('Link', '<' . check_plain($value) . '>;' . drupal_http_header_attributes(array_diff_key($element['#attributes'], array('href' => ''))), TRUE);
    }

    return array(
      '#attached' => array('drupal_add_html_head' => array(array($element, $element['#id']))),
    );
    return $element;
  }
}

/**
 * Title meta tag controller.
 *
 * This extends DrupalTextMetaTag as we need to alter variables in
 * template_preprocess_html() rather output a normal meta tag.
 */
class DrupalTitleMetaTag extends DrupalTextMetaTag {
  public function getElement(array $options = array()) {
    $element = array();
    $value = check_plain($this->getValue($options));
    $element['#attached']['metatag_set_preprocess_variable'][] = array('html', 'head_title', $value);
    $element['#attached']['metatag_set_preprocess_variable'][] = array('html', 'head_array', array('title' => $value));
    return $element;
  }
}
