<?php

/**
 * @file
 * Metatag integration for the Metatag Google Scholar module.
 */

/**
 * Implements hook_metatag_bundled_config_alter().
 */
function metatag_google_scholar_metatag_bundled_config_alter(array &$configs) {
  foreach ($configs as &$config) {
    switch ($config->instance) {
      case 'global':
        $config->config += array(
          'itemprop:name' => array('value' => '[current-page:title]'),
        );
        break;

      case 'global:frontpage':
        $config->config += array(
          'itemprop:name' => array('value' => '[site:name]'),
          'itemprop:description' => array('value' => '[site:slogan]'),
        );
        break;

      // On error pages point everything to the homepage.
      case 'global:403':
      case 'global:404':
        $config->config += array(
          'itemprop:name' => array('value' => '[site:name]'),
        );
        break;

      case 'node':
        $config->config += array(
          'itemprop:description' => array('value' => '[node:summary]'),
          'itemprop:name' => array('value' => '[node:title]'),
          'itemtype' => array('value' => 'Article'),
        );
        break;

      case 'taxonomy_term':
        $config->config += array(
          'itemprop:description' => array('value' => '[term:description]'),
          'itemprop:name' => array('value' => '[term:name]'),
        );
        break;

      case 'user':
        $config->config += array(
          'itemprop:name' => array('value' => '[user:name]'),
          'itemtype' => array('value' => 'Person'),
        );
        if (variable_get('user_pictures')) {
          $config->config += array(
            'itemprop:image' => array('value' => '[user:picture:url]'),
          );
        }
        break;
    }
  }
}

/**
 * Implements hook_metatag_info().
 */
function metatag_google_scholar_metatag_info() {
  $info['groups']['google-scholar'] = array(
    'label' => t('Google Scholar'),
    'description' => t('A set of meta tags specially for controlling Google Scholar Indexing terms'),
    'form' => array(
      '#weight' => 80,
    ),
  );

  $weight = 60;

  // Defaults used for all cards.
  $defaults = array(
    'class' => 'DrupalTextMetaTag',
    'group' => 'google-scholar',
    'element' => array(
      '#theme' => 'metatag_google_scholar',
    ),
  );

  $info['tags']['citation_title'] = array(
    'label' => t('Citation Title'),
    'description' => t('The title of the pubilcation.'),
    'maxlength' => 0,
    'weight' => ++$weight,
  ) + $defaults;

  $info['tags']['citation_author'] = array(
    'label' => t('Citation Author'),
    'description' => t('A Google Scholar author tag.'),
    'maxlength' => 0,
    'element' => array(),
    'weight' => ++$weight,
  ) + $defaults;

  
  $info['tags']['citation_publication_date'] = array(
    'label' => t('Citation Publication Date'),
    'description' => t('Follow "yyyy/mm/dd".'),
    'weight' => ++$weight,
    'maxlength' => 0,
  ) + $defaults;

  $info['tags']['citation_journal_title'] = array(
    'label' => t('Citation Journal Title'),
    'description' => t("Name of the Venue."),
    'weight' => ++$weight,
    'maxlength' => 0,
  ) + $defaults;
  
  $info['tags']['citation_volume'] = array(
    'label' => t('Citation Volume'),
    'description' => t("The volume number of the publication."),
    'weight' => ++$weight,
    'maxlength' => 0,
  ) + $defaults;

  $info['tags']['citation_issue'] = array(
    'label' => t('Citation Issue'),
    'description' => t("The issue number of the publiation."),
    'weight' => ++$weight,
    'maxlength' => 0,
  ) + $defaults;

  $info['tags']['citation_firstpage'] = array(
    'label' => t('Citation First Page'),
    'description' => t("The first page number of the publication."),
    'weight' => ++$weight,
    'maxlength' => 0,
  ) + $defaults;

  $info['tags']['citation_lastpage'] = array(
    'label' => t('Citation Last Page'),
    'description' => t("The last page number of the publication."),
    'weight' => ++$weight,
    'maxlength' => 0,
  ) + $defaults;

  $info['tags']['citation_pdf_url'] = array(
    'label' => t('Citation PDF URL'),
    'description' => t("The URL of the publication PDF file."),
    'weight' => ++$weight,
    'maxlength' => 0,
    'element' => array(),
  ) + $defaults;

  return $info;
}
