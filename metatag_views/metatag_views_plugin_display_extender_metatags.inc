<?php
/**
 * @file
 * Custom display extender plugin for Views.
 */

class metatag_views_plugin_display_extender_metatags extends views_plugin_display_extender {

  function init(&$view, &$display) {
    $display->options['defaults']['metatags'] = array();
    parent::init($view, $display);
  }

  function defaultable_sections(&$sections, $section = NULL) {
    $sections['metatags'] = array('metatags');
  }

  protected function has_metatags() {
    $metatags = $this->display->get_option('metatags');
    return !empty($metatags);
  }

  function options_definition_alter(&$options) {
    $options['metatags'] = array('default' => array());
  }

  function options_summary(&$categories, &$options) {
    if ($this->has_metatags()) {
      $categories['metatags'] = array(
        'title' => t('Meta tags'),
        'column' => 'second',
      );
      $metatags = $this->display->get_option('metatags');
      $options['metatags'] = array(
        'category' => 'metatags',
        'title' => t('Meta tags'),
        'value' => !empty($metatags) ? t('Overridden') : t('Using defaults'),
      );
    }
  }

  function options_form(&$form, &$form_state) {
    if ($form_state['section'] == 'metatags') {
      $form['#title'] .= t('The meta tags for this display');

      // Leave some possibility for future versions to support translation.
      $metatags = $this->display->get_option('metatags');
      if (empty($metatags)) {
        $metatags = array(LANGUAGE_NONE => array());
      }
      if (!isset($metatags[LANGUAGE_NONE])) {
        $metatags = array(LANGUAGE_NONE => $metatags);
      }

      // Build/inject the Metatag form.
      $instance = 'view:' . $form_state['view']->name;
      $options['token types'] = array('view');
      $options['context'] = 'view';
      metatag_metatags_form($form, $instance, $metatags[LANGUAGE_NONE], $options);

      $form['metatags']['#type'] = 'container';
    }
  }

  function options_submit(&$form, &$form_state) {
    if ($form_state['section'] == 'metatags') {
      $metatags = $form_state['values']['metatags'];

      // Leave some possibility for future versions to support translation.
      foreach ($metatags as $langcode => $values) {
        if (!empty($form['metatags'][$langcode]['#metatag_defaults'])) {
          metatag_filter_values_from_defaults($form_state['values']['metatags'][$langcode], $form['metatags'][$langcode]['#metatag_defaults']);
        }
      }

      $this->display->set_option('metatags', $metatags);
    }
  }
}
