<?php
/**
 * @file
 * API documentation for the Metatag module.
 */

/**
 * To enable Metatag support in custom entities, add 'metatag' => TRUE to the
 * entity definition in hook_entity_info(), e.g.:
 * 
 * /**
 *  * Implements hook_entity_info().
 *  *
 *  * Taken from the Examples module.
 *  * /
 * function entity_example_entity_info() {
 *   $info['entity_example_basic'] = array(
 *     'label' => t('Example Basic Entity'),
 *     'controller class' => 'EntityExampleBasicController',
 *     'base table' => 'entity_example_basic',
 *     'uri callback' => 'entity_example_basic_uri',
 *     'fieldable' => TRUE,
 *     'metatag' => TRUE,
 *     'entity keys' => array(
 *       'id' => 'basic_id' , // The 'id' (basic_id here) is the unique id.
 *       'bundle' => 'bundle_type' // Bundle will be determined by the 'bundle_type' field
 *     ),
 *     'bundle keys' => array(
 *       'bundle' => 'bundle_type',
 *     ),
 *     'static cache' => TRUE,
 *     'bundles' => array(
 *       'first_example_bundle' => array(
 *         'label' => 'First example bundle',
 *         'admin' => array(
 *           'path' => 'admin/structure/entity_example_basic/manage',
 *           'access arguments' => array('administer entity_example_basic entities'),
 *         ),
 *       ),
 *     ),
 *     'view modes' => array(
 *       'tweaky' => array(
 *         'label' => t('Tweaky'),
 *         'custom settings' =>  FALSE,
 *       ),
 *     )
 *   );
 * 
 *   return $info;
 * }
 *
 * The definition of each bundle may be handled separately, thus support may be
 * disabled for the entity as a whole but enabled for individual bundles. This
 * is handled via the 'metatag' value on the bundle definition, e.g.:
 *
 *     'bundles' => array(
 *       'first_example_bundle' => array(
 *         'label' => 'First example bundle',
 *         'metatag' => TRUE,
 *         'admin' => array(
 *           'path' => 'admin/structure/entity_example_basic/manage',
 *           'access arguments' => array('administer entity_example_basic entities'),
 *         ),
 *       ),
 *     ),
 */

/**
 * 
 */
function hook_metatag_config_default() {
  return array();
}

/**
 * 
 */
function hook_metatag_config_default_alter(&$config) {
}

/**
 * 
 */
function hook_metatag_config_delete($type, $ids) {
}

/**
 * 
 */
function hook_metatag_config_insert($config) {
}

/**
 * 
 */
function hook_metatag_config_instance_info() {
  return array();
}

/**
 * 
 */
function hook_metatag_config_instance_info_alter(&$info) {
}

/**
 * 
 */
function hook_metatag_config_load() {
}

/**
 * 
 */
function hook_metatag_config_load_presave() {
}

/**
 * 
 */
function hook_metatag_config_presave($config) {
}

/**
 * 
 */
function hook_metatag_config_update($config) {
}

/**
 * 
 */
function hook_metatag_info() {
  return array();
}

/**
 * 
 */
function hook_metatag_info_alter(&$info) {
}

/**
 * 
 */
function hook_metatag_load_entity_from_path_alter(&$path, $result) {
}

/**
 * Alter metatags before being cached.
 *
 * This hook is invoked prior to the meta tags for a given page are cached.
 *
 * @param array $output
 *   All of the meta tags to be output for this page in their raw format. This
 *   is a heavily nested array.
 * @param string $instance
 *   An identifier for the current page's page type, typically a combination
 *   of the entity name and bundle name, e.g. "node:story".
 */
function hook_metatag_metatags_view_alter(&$output, $instance) {
  if (isset($output['description']['#attached']['drupal_add_html_head'][0][0]['#value'])) {
    $output['description']['#attached']['drupal_add_html_head'][0][0]['#value'] = 'O rly?';
  }
}

/**
 * 
 */
function hook_metatag_page_cache_cid_parts_alter(&$cid_parts) {
}

/**
 * 
 */
function hook_metatag_presave(&$metatags, $type, $id) {
}
