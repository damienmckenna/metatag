<?php
/**
 * @file
 * Context reaction for Metatag.
 */

class metatag_context_reaction extends context_reaction {
  function options_form($context) {
    // Empty form to start with.
    $form = array();
    // Don't care about the instance name, the data is being managed by
    // Context and not Metatag.
    $instance = "";
    // Load the previously saved settings.
    $data = $this->fetch_from_context($context);
    //print_r($data);
    if (!isset($data['metatags'])) {
      $data['metatags'] = array();
    }
    // No options currently available.
    $options = array();

    $form['help'] = array(
      '#prefix' => '<hr /><p><em>',
      '#markup' => t('The <a href="@url" title="Edit the global default meta tags.">global defaults</a> are used.', array('@url' => url('admin/config/search/metatags/config/global'))),
      '#suffix' => '</em></p>',
    );

    // Load the form.
    metatag_metatags_form($form, $instance, $data['metatags'], $options);

    // Stop the meta tag fields appearing within a fieldset.
    $form['metatags']['#type'] = 'container';
    unset($form['metatags']['#collapsed']);
    unset($form['metatags']['#collapsible']);
    unset($form['#submit']);
    // Flatten the ['advanced'] part of the form because otherwise the context
    // module will not pick up all values. Perhaps it can be done in a better
    // way with #tree and #parents.
    foreach($form['metatags']['advanced'] as $key => $value) {
      if(substr($key, 0, 1) == '#') {
        unset ($form['metatags']['advanced'][$key]);
        continue;
      }
      $form['metatags'][$key] = $value;
      unset($form['metatags'][$key]['#parents']);
      unset($form['metatags']['advanced'][$key]);
    }
    // Show all takens.
    $form['metatags']['tokens']['#token_types'] = 'all';
    unset($form['metatags']['advanced']);
    $form['metatag_admin'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show on metatag admin page.'),
      '#weight' => -98,
      '#default_value' => isset($data['metatag_admin']) ? $data['metatag_admin'] : '',
    );

    return $form;
  }

  /**
   * Output a list of active contexts.
   */
  function execute() {
    $output = &drupal_static('metatag_context');

    if (!isset($output)) {
      $metatags = array();
      $output = array();
      $contexts = context_active_contexts();
      $options = array();

      foreach ($contexts as $context) {
        if (!empty($context->reactions['metatag_context_reaction']['metatags'])) {
          $metadata_array = $context->reactions['metatag_context_reaction']['metatags'];
          foreach ($metadata_array as $key => $data) {
            if (!empty($data['value'])) {
              $metatags[$key] = $data;//t(check_plain($data['value']));
            }
          }
        }
      }

      $metatags += metatag_config_load_with_defaults('');

      $output = array();
      foreach ($metatags as $metatag => $data) {
        if ($metatag_instance = metatag_get_instance($metatag, $data)) {
          $output[$metatag] = $metatag_instance->getElement($options);
        }
      }

      drupal_alter('metatag_metatags_view', $output);
    }
  }
}
