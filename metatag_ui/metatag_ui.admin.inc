<?php

/**
 * @file
 * Administration page callbacks for the metatag_ui module.
 */

function metatag_ui_config_overview() {
  ctools_include('export');

  $contexts = metatag_get_context_info();
  $configs = ctools_export_crud_load_all('metatag_config');

  $rows = array();
  foreach ($configs as $config) {
    $row = array();
    $context = explode(':', $config->instance);
    $row[] = $context[0];
    $row[] = isset($context[1]) ? $context[1] : t('Default');

    $operations['edit'] = array(
      'title' => t('Edit'),
      'href' => 'admin/config/search/metatags/config/' . $config->instance,
    );
    $row[] = array(
      'data' => array(
        '#theme' => 'links',
        '#links' => $operations,
        '#attributes' => array('class' => array('links', 'inline')),
      ),
    );

    $rows[$config->instance] = $row;
  }

  $build['config_table'] = array(
    '#theme' => 'table',
    '#header' => array(
      'type' => t('Type'),
      'subtype' => t('Subtype'),
      'operations' => t('Operations'),
    ),
    '#rows' => $rows,
    '#empty' => t('No configurations available yet.'),
  );

  return $build;
}

function metatag_ui_config_add_form($form, &$form_state) {
  $options = array();
  $contexts = metatag_get_context_info();

  foreach ($contexts as $context_key => $context) {
    $group = $context['label'];
    $options[$group] = array();
    if (!metatag_config_load($context_key)) {
      $options[$group][$context_key] = t('Default');
    }
    if (!empty($context['bundles'])) {
      foreach ($context['bundles'] as $bundle_key => $bundle) {
        $instance = $context_key . ':' . $bundle_key;
        if (!metatag_config_load($instance)) {
          $options[$group][$instance] = $bundle['label'];
        }
      }
    }
    if (empty($options[$group])) {
      unset($options[$group]);
    }
  }

  $form['instance'] = array(
    '#type' => 'select',
    '#title' => t('Instance'),
    '#options' => $options,
    '#required' => TRUE,
  );
  $form['config'] = array(
    '#type' => 'value',
    '#value' => array(),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Add and configure'),
  );
  $form['actions']['cancel'] = array(
    '#type' => 'link',
    '#title' => t('Cancel'),
    '#href' => isset($_GET['destination']) ? $_GET['destination'] : 'admin/config/search/metatags',
  );

  return $form;
}

function metatag_ui_config_add_form_submit($form, &$form_state) {
  form_state_values_clean($form_state);
  $config = (object) $form_state['values'];
  metatag_config_save($config);
  $form_state['redirect'] = 'admin/config/search/metatags/config/' . $config->instance;
}

function metatag_ui_config_edit_form($form, &$form_state, $config) {
  $form['cid'] = array(
    '#type' => 'value',
    '#value' => !empty($config->cid) ? $config->cid : NULL,
  );
  $form['instance'] = array(
    '#type' => 'value',
    '#value' => $config->instance,
  );

  $contexts = explode(':', $config->instance);
  $options['context'] = $contexts[0];
  if ($contexts[0] != 'global') {
    $options['token types'] = array(token_get_entity_mapping('entity', $contexts[0]));
  }

  // Ensure that this configuration is properly compared to its parent 'default'
  // configuration values.
  if (count($contexts) > 1) {
    // If the config is something like 'node:article' or 'taxonomy_term:tags'
    // then the parent default config is 'node' or 'taxonomy_term'.
    $default_instance = $contexts;
    array_pop($default_instance);
    $default_instance = implode(':', $default_instance);
    $options['defaults'] = metatag_config_load_with_defaults($default_instance);
  }
  elseif ($contexts[0] != 'global') {
    // If the config is something like 'node' or 'taxonomy_term' then the
    // parent default config is 'global'.
    $options['defaults'] = metatag_config_load_with_defaults('global');
  }
  else {
    // If the config is 'global' than there are no parent defaults.
    $options['defaults'] = array();
  }

  metatag_metatags_form($form, $config->instance, $config->config, $options);
  $form['metatags']['#type'] = 'container';

  $form['actions']['#type'] = 'actions';
  $form['actions']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['#submit'][] = 'metatag_ui_config_edit_form_submit';
  return $form;
}

function metatag_ui_config_edit_form_submit($form, &$form_state) {
  // Build the configuration object and save it.
  form_state_values_clean($form_state);
  $config = (object) $form_state['values'];
  // @todo Consider renaming the config field from 'config' to 'metatags'
  $config->config = $config->metatags;
  unset($config->metatags);
  metatag_config_save($config);

  drupal_set_message(t('The metatag configuration has been saved.'));
  $form_state['redirect'] = 'admin/config/search/metatags';
}
