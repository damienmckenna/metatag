<?php

/**
 * @file
 * Administration page callbacks for the metatag_ui module.
 */

function _metatag_ui_config_sort($a, $b) {
  $return = NULL;
  $a_contexts = explode(':', $a->instance);
  $b_contexts = explode(':', $b->instance);
  for ($i = 0; $i < max(count($a_contexts), count($b_contexts)); $i++) {
    $a_context = isset($a_contexts[$i]) ? $a_contexts[$i] : '';
    $b_context = isset($b_contexts[$i]) ? $b_contexts[$i] : '';
    if ($a_context == $b_context) {
      continue;
    }
    elseif ($a_context == 'global') {
      $return = -1;
    }
    elseif ($a_context == '') {
      $return = -1;
    }
    else {
      $return = strcmp($a_context, $b_context);
    }
  }
  return $return;
}

function metatag_ui_config_overview() {
  ctools_include('export');

  $contexts = metatag_get_context_info();

  $configs = ctools_export_crud_load_all('metatag_config');
  ksort($configs);
  //uasort($configs, '_metatag_ui_config_sort');

  $rows = array();
  foreach ($configs as $config) {
    $row = array();
    $context = explode(':', $config->instance);
    $row[] = $contexts[$context[0]]['label'];
    $row[] = isset($context[1]) ? $contexts[$context[0]]['bundles'][$context[1]]['label'] : t('Default');

    $operations = array();
    $operations['edit'] = array(
      'title' => ($config->export_type & EXPORT_IN_DATABASE) ? t('Edit') : t('Override'),
      'href' => 'admin/config/search/metatags/config/' . $config->instance,
    );
    if (metatag_ui_config_access('revert', $config)) {
      $operations['revert'] = array(
        'title' => t('Revert'),
        'href' => 'admin/config/search/metatags/config/' . $config->instance . '/revert',
      );
    }
    if (metatag_ui_config_access('delete', $config)) {
      $operations['delete'] = array(
        'title' => t('Delete'),
        'href' => 'admin/config/search/metatags/config/' . $config->instance . '/delete',
      );
    }
    $operations['export'] = array(
      'title' => t('Export'),
      'href' => 'admin/config/search/metatags/config/' . $config->instance . '/export',
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
    '#description' => t('Select the type of data to add a configuration.'),
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
  $form['actions']['cancel'] = array(
    '#type' => 'link',
    '#title' => t('Cancel'),
    '#href' => isset($_GET['destination']) ? $_GET['destination'] : 'admin/config/search/metatags',
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

function metatag_ui_config_delete_form($form, &$form_state, $config) {
  $form['cid'] = array('#type' => 'value', '#value' => $config->cid);
  $form['instance'] = array('#type' => 'value', '#value' => $config->instance);
  $delete = metatag_ui_config_access('delete', $config);

  return confirm_form(
    $form,
    $delete ? t('Are you sure you want to delete the configuration?') : t('Are you sure you want to revert the configuration?'),
    'admin/config/search/metatags',
    t('This action cannot be undone.')
  );
}

function metatag_ui_config_delete_form_submit($form, &$form_state) {
  $config = metatag_config_load($form_state['values']['instance']);
  metatag_config_delete($config->instance);
  $delete = metatag_ui_config_access('delete', $config);
  $title = $delete ? t('The configuration has been deleted.') : t('The configuration has been reverted.');
  drupal_set_message($title);
  $form_state['redirect'] = 'admin/config/search/metatags';
}

function metatag_ui_config_export_form($config) {
  ctools_include('export');
  return drupal_get_form('ctools_export_form', ctools_export_crud_export('metatag_config', $config), t('Export'));
}
