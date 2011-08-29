<?php

/**
 * Implements hook_metatag_config_default().
 */
function metatag_metatag_config_default() {
  $configs = array();

  $config = new stdClass();
  $config->instance = 'global';
  $config->api_version = 1;
  $config->disabled = FALSE;
  $config->config = array(
    'generator' => array('value' => 'Drupal 7 (http://drupal.org)'),
  );
  $configs[$config->instance] = $config;

  $config = new stdClass();
  $config->instance = 'node';
  $config->api_version = 1;
  $config->disabled = FALSE;
  $config->config = array(
    'description' => array('value' => '[node:summary]'),
    'title' => array('value' => '[node:title]'),
  );
  $configs[$config->instance] = $config;

  $config = new stdClass();
  $config->instance = 'node:article';
  $config->api_version = 1;
  $config->disabled = FALSE;
  $config->config = array(
    'keywords' => array('value' => '[node:field_tags]'),
  );
  $configs[$config->instance] = $config;

  return $configs;
}

/**
 * Implements hook_metatag_context_info().
 */
function metatag_metatag_context_info() {
  $info['global'] = array(
    'label' => t('Global'),
    'bundles' => array(
      'frontpage' => array(
        'label' => t('Front page'),
      ),
      '403' => array(
        'label' => t('403 page not found'),
      ),
      '404' => array(
        'label' => t('404 page not found'),
      ),
    ),
  );

  // Add context information for entities.
  $entity_types = entity_get_info();
  foreach ($entity_types as $entity_type => $entity_info) {
    if (metatag_entity_supports_metatags($entity_type)) {
      $info[$entity_type] = array('label' => $entity_info['label']);
      foreach ($entity_info['bundles'] as $bundle => $bundle_info) {
        $info[$entity_type]['bundles'][$bundle] = array('label' => $bundle_info['label']);
      }
    }
  }

  return $info;
}

/**
 * Implements hook_metatag_info().
 */
function metatag_metatag_info() {
  $info['description'] = array(
    'label' => t('Description'),
    'description' => t('The meta description tag allows you to influence the description of your page in the crawlers that support the tag.'),
    'class' => 'DrupalTextMetaTag',
    'form' => array(
      '#type' => 'textarea',
      '#rows' => 3,
      '#wysiwyg' => FALSE,
    ),
  );
  $info['keywords'] = array(
    'label' => t('Keywords'),
    'description' => '',
    'class' => 'DrupalTextMetaTag',
  );
  $info['title'] = array(
    'label' => t('Title'),
    'description' => '',
    'class' => 'DrupalTitleMetaTag',
  );
  $info['generator'] = array(
    'label' => t('Generator'),
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'element' => array(
      '#id' => 'system_meta_generator',
    ),
    'header' => 'X-Generator',
    'context' => array('global'),
  );
  $info['copyright'] = array(
    'label' => t('Copyright'),
    'description' => '',
    'class' => 'DrupalTextMetaTag',
  );

  // Link tags.
  $info['canonical'] = array(
    'label' => t('Canonical URL'),
    'description' => '',
    'class' => 'DrupalLinkMetaTag',
  );
  $info['shortlink'] = array(
    'label' => t('Shortlink URL'),
    'description' => '',
    'class' => 'DrupalLinkMetaTag',
  );

  return $info;
}
