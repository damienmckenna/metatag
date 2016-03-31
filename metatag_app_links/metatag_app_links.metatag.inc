<?php
/**
 * @file
 * Metatag integration for the Metatag:App Links module.
 */

/**
 * Implements hook_metatag_info().
 */
function metatag_app_links_metatag_info() {
  $info['groups']['app_links'] = array(
    'label' => 'App Links',
    'description' => 'Meta tags used to expose App Links for app deep linking. See <a href="@url">applinks.org</a> for details and documentation.',
    'description args' => array('@url' => 'http://applinks.org'),
    'form' => array(
      '#weight' => 90,
    ),
  );

  // Default values for each meta tag.
  $defaults = array(
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'app_links',
    'element' => array(
      '#theme' => 'metatag_property',
    ),
  );
  // Stack these codes after most others.
  $weight = 80;

  $info['tags']['al:android:package'] = array(
    'label' => 'Android App Package ID',
    'description' => 'A fully-qualified package name for intent generation. <strong>This attribute is required by the App Links specification.</strong>',
    'weight' => ++$weight,
  ) + $defaults;

  $info['tags']['al:android:url'] = array(
    'label' => 'Android App URL scheme',
    'description' => 'A custom scheme for the Android app.',
  ) + $defaults;

  $info['tags']['al:android:class'] = array(
    'label' => 'Android App Activity Class',
    'description' => 'A fully-qualified Activity class name for intent generation.',
  ) + $defaults;

  $info['tags']['al:android:app_name'] = array(
    'label' => 'Android App Name',
    'description' => 'The name of the app (suitable for display)',
  ) + $defaults;

  $info['tags']['al:ios:url'] = array(
    'label' => 'iOS App URL scheme',
    'description' => 'A custom scheme for the iOS app. <strong>This attribute is required by the App Links specification.</strong>',
  ) + $defaults;

  $info['tags']['al:ios:app_store_id'] = array(
    'label' => 'iOS App Store ID',
    'description' => 'The app ID for the App Store.',
    'devel_generate' => array(
      'type' => 'integer',
    ),
  ) + $defaults;

  $info['tags']['al:ios:app_name'] = array(
    'label' => 'iOS App Name',
    'description' => 'The name of the app (suitable for display)',
  ) + $defaults;

  $info['tags']['al:ipad:url'] = array(
    'label' => 'iPad App URL scheme',
    'description' => 'A custom scheme for the iPad app. <strong>This attribute is required by the App Links specification.</strong>',
  ) + $defaults;

  $info['tags']['al:ipad:app_store_id'] = array(
    'label' => 'iPad App Store ID',
    'description' => 'The app ID for the App Store.',
    'devel_generate' => array(
      'type' => 'integer',
    ),
  ) + $defaults;

  $info['tags']['al:ipad:app_name'] = array(
    'label' => 'iPad App Name',
    'description' => 'The name of the app (suitable for display)',
  ) + $defaults;

  $info['tags']['al:iphone:url'] = array(
    'label' => 'iPhone App URL',
    'description' => 'A custom scheme for the iPhone app. <strong>This attribute is required by the App Links specification.</strong>',
  ) + $defaults;

  $info['tags']['al:iphone:app_store_id'] = array(
    'label' => 'iPhone App Store ID',
    'description' => 'The app ID for the App Store.',
    'devel_generate' => array(
      'type' => 'integer',
    ),
  ) + $defaults;

  $info['tags']['al:iphone:app_name'] = array(
    'label' => 'iPhone App Name',
    'description' => 'The name of the app (suitable for display)',
  ) + $defaults;

  $info['tags']['al:windows_phone:url'] = array(
    'label' => 'Windows Phone App URL scheme',
    'description' => 'A custom scheme for the Windows Phone app. <strong>This attribute is required by the App Links specification.</strong>',
  ) + $defaults;

  $info['tags']['al:windows_phone:app_id'] = array(
    'label' => 'Windows Phone App GUID',
    'description' => 'The app ID (a GUID) for app store.',
  ) + $defaults;

  $info['tags']['al:windows_phone:app_name'] = array(
    'label' => 'Windows Phone App Name',
    'description' => 'The name of the app (suitable for display)',
  ) + $defaults;

  $info['tags']['al:windows:url'] = array(
    'label' => 'Windows App URL scheme',
    'description' => 'A custom scheme for the Windows app. <strong>This attribute is required by the App Links specification.</strong>',
  ) + $defaults;

  $info['tags']['al:windows:app_id'] = array(
    'label' => 'Windows App GUID',
    'description' => 'The app ID (a GUID) for app store.',
  ) + $defaults;

  $info['tags']['al:windows:app_name'] = array(
    'label' => 'Windows App Name',
    'description' => 'The name of the app (suitable for display)',
  ) + $defaults;

  $info['tags']['al:windows_universal:url'] = array(
    'label' => 'Windows Universal App URL scheme',
    'description' => 'A custom scheme for the Windows Universal app. <strong>This attribute is required by the App Links specification.</strong>',
  ) + $defaults;

  $info['tags']['al:windows_universal:app_id'] = array(
    'label' => 'Windows Universal App GUID',
    'description' => 'The app ID (a GUID) for app store.',
  ) + $defaults;

  $info['tags']['al:windows_universal:app_name'] = array(
    'label' => 'Windows Universal App Name',
    'description' => 'The name of the app (suitable for display)',
  ) + $defaults;

  $info['tags']['al:web:url'] = array(
    'label' => 'Web URL',
    'description' => 'The web URL; defaults to the URL for the content that contains this tag.',
  ) + $defaults;

  $info['tags']['al:web:should_fallback'] = array(
    'label' => 'Should fallback',
    'description' => 'Indicates if the web URL should be used as a fallback; defaults to "true".',
  ) + $defaults;

  return $info;
}
