<?php

/**
 * @file
 * Metatag integration for the metatag_opengraph module.
 */

function metatag_opengraph_metatag_default_config() {
  dpm(__FUNCTION__);
}

/**
 * Implements hook_metatag_default_config_alter().
 */
function metatag_opengraph_metatag_default_config_alter(&$configs) {
  dpm($configs, __FUNCTION__);
  /*if (isset($configs['global:default'])) {
    $configs['global:default'] += array(
      'og:type' => 'article',
      'og:site_name' => '[site:name]',
      'og:url' => '[current-page:url:unaliased]',
    );
  }
  if (isset($configs['node:default'])) {
    $configs['node:default'] += array(
      'og:title' => '[node:title]',
      'og:description' => '[node:summary]',
    );
  }
  if (isset($configs['taxonomy_term:default'])) {
    $configs['taxonomy_term:default'] += array(
      'og:title' => '[term:name]',
      'og:description' => '[term:description]',
    );
  }
  if (isset($configs['user:default'])) {
    $configs['user:default'] += array(
      'og:title' => '[user:name]',
      'og:type' => '[]',
    );
  }*/
}

/**
 * Implements hook_metatag_info().
 */
function metatag_opengraph_metatag_info() {
  $info['og:title'] = array(
    'label' => t('Open Graph title'),
    'description' => t('The title of your object as it should appear within the graph, e.g., <em>The Rock</em>.'),
    'class' => 'DrupalTextMetaTag',
    'group' => t('Open Graph'),
  );
  $info['og:type'] = array(
    'label' => t('Open Graph type'),
    'description' => t('The type of your object, e.g., <em>movie</em>.'),
    'class' => 'DrupalOptionsMetaTag',
    'group' => t('Open Graph'),
    'form' => array(
      '#options' => _metatag_opengraph_type_options(),
    ),
    'default' => 'article',
  );
  //if (module_exists('select_or_other')) {
  //  $info['og:type']['form']['#type'] = 'select_or_other';
  //}
  $info['og:image'] = array(
    'label' => t('Open Graph image'),
    'description' => t('An image URL which should represent your object within the graph. The image must be at least 50px by 50px and have a maximum aspect ratio of 3:1. We support PNG, JPEG and GIF formats.'),
    'class' => 'DrupalTextMetaTag',
    'group' => t('Open Graph'),
  );
  $info['og:url'] = array(
    'label' => t('Open Graph URL'),
    'description' => t('The canonical URL of your object that will be used as its permanent ID in the graph, e.g., <em>http://www.imdb.com/title/tt0117500/</em>.'),
    'class' => 'DrupalTextMetaTag',
    'group' => t('Open Graph'),
    'default' => '[current-page:url:unaliased]',
  );
  $info['og:site_name'] = array(
    'label' => t('Open Graph site name'),
    'description' => t('A human-readable name for your site, e.g., <em>IMDb</em>.'),
    'class' => 'DrupalTextMetaTag',
    'group' => t('Open Graph'),
    'default' => '[site:name]',
    'context' => array('global'),
  );
  $info['og:description'] = array(
    'label' => t('Open Graph description'),
    'description' => t('A one to two sentence description of your page.'),
    'group' => t('Open Graph'),
    'class' => 'DrupalTextMetaTag',
  );
  $info['og:latitude'] = array(
    'label' => t('Open Graph latitude'),
    'description' => t('The latitude of the page.'),
    'group' => t('Open Graph'),
    'class' => 'DrupalTextMetaTag',
  );

  return $info;
}

function _metatag_opengraph_type_options() {
  $options = array(
    t('Activities') => array(
      'activity' => t('Activity'),
      'sport' => t('Sport'),
    ),
    t('Businesses') => array(
      'bar' => t('Bar'),
      'company' => t('Company'),
      'cafe' => t('Cafe'),
      'hotel' => t('Hotel'),
      'restaurant' => t('Restaurant'),
    ),
    t('Groups') => array(
      'cause' => t('Cause'),
      'sports_league' => t('Sports league'),
      'sports_team' => t('Sports team'),
    ),
    t('Organizations') => array(
      'band' => t('Band'),
      'government' => t('Government'),
      'non_profit' => t('Non-profit'),
      'school' => t('School'),
      'university' => t('University'),
    ),
    t('People') => array(
      'actor' => t('Actor'),
      'athlete' => t('Athlete'),
      'author' => t('Author'),
      'director' => t('Director'),
      'musician' => t('Musician'),
      'politician' => t('Politician'),
      'public_figure' => t('Public figure'),
    ),
    t('Places') => array(
      'city' => t('City'),
      'country' => t('Country'),
      'landmark' => t('Landmark'),
      'state_province' => t('State or province'),
    ),
    t('Products and Entertainment') => array(
      'album' => t('Album'),
      'book' => t('Book'),
      'drink' => t('Drink'),
      'food' => t('Food'),
      'game' => t('Game'),
      'product' => t('Product'),
      'song' => t('Song'),
      'movie' => t('Movie'),
      'tv_show' => t('TV show'),
    ),
    t('Websites') => array(
      'blog' => t('Blog'),
      'website' => t('Website'),
      'article' => t('Article'),
    ),
  );

  return $options;
}
