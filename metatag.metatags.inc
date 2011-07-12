<?php

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
