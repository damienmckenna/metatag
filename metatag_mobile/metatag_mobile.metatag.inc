<?php
/**
 * @file
 * Metatag integration for the Metatag:Facebook module.
 */

/**
 * Implements hook_metatag_info().
 */
function metatag_mobile_metatag_info() {
  $info['groups']['mobile'] = array(
    'label' => t('Mobile & UI Adjustments'),
    'description' => t("Meta tags used to control the mobile browser experience. Some of these meta tags have been replaced by newer mobile browsers. These meta tags usually only need to be set globally, rather than per-page."),
    'form' => array(
      '#weight' => 80,
    ),
  );
  $info['groups']['apple_mobile'] = array(
    'label' => t('Apple & iOS'),
    'description' => t("Custom meta tags used by Apple's software, iOS, Safari, etc."),
    'form' => array(
      '#weight' => 81,
    ),
  );
  $info['groups']['android_mobile'] = array(
    'label' => t('Android'),
    'description' => t("Custom meta tags used by the Android OS, browser, etc."),
    'form' => array(
      '#weight' => 82,
    ),
  );

  $weight = 80;

  // Default values for each meta tag.
  $tag_info_defaults = array(
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'mobile',
  );

  $info['tags']['theme-color'] = array(
    'label' => t('Theme Color'),
    'description' => t('A color in hexidecimal format, e.g. "#0000ff" for blue; must include the "#" symbol. Used by some browsers to control the background color of the toolbar, the color used with an icon, etc.'),
    'weight' => ++$weight,
  ) + $tag_info_defaults;

  $info['tags']['MobileOptimized'] = array(
    'label' => t('Mobile Optimized'),
    'description' => t('Using the value "width" tells certain mobile Internet Explorer browsers to display as-is, without being resized. Alternatively a numerical width may be used to indicate the desired page width the page should be rendered in: "240" is the suggested default, "176" for older browsers or "480" for newer devices with high DPI screens.'),
    'weight' => ++$weight,
    'multiple' => TRUE,
  ) + $tag_info_defaults;

  $info['tags']['HandheldFriendly'] = array(
    'label' => t('Handheld-Friendly'),
    'description' => t('Some older mobile browsers will expect this meta tag to be set to "true" to indicate that the site has been designed with mobile browsers in mind.'),
    'weight' => ++$weight,
    'multiple' => TRUE,
  ) + $tag_info_defaults;

  $info['tags']['viewport'] = array(
    'label' => t('Viewport'),
    'description' => t('Used by most contemporary browsers to control the display for mobile browsers. Please read a guide on responsive web design for details of what values to use.'),
    'weight' => ++$weight,
  ) + $tag_info_defaults;

  $info['tags']['cleartype'] = array(
    'label' => t('Cleartype'),
    'description' => t('A legacy meta tag for older versions of Internet Explorer on Windows, use the value "on" to enable it; this tag is ignored by all other browsers.'),
    'weight' => ++$weight,
    'element' => array(
      '#theme' => 'metatag_http_equiv',
    ),
  ) + $tag_info_defaults;

  // Default values for each meta tag.
  $tag_info_defaults = array(
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'apple_mobile',
  );

  $info['tags']['apple-mobile-web-app-capable'] = array(
    'label' => t('Web app capable?'),
    'description' => t('If set to "yes", the application will run in full-screen mode; the default behavior is to use Safari to display web content.'),
    'weight' => ++$weight,
  ) + $tag_info_defaults;

  $info['tags']['apple-mobile-web-app-status-bar-style'] = array(
    'label' => t('Status bar color'),
    'description' => t('Requires the "Web app capable" meta tag to be set to "yes". May be set to "default", "black", or "black-translucent".'),
    'weight' => ++$weight,
  ) + $tag_info_defaults;

  $info['tags']['format-detection'] = array(
    'label' => t('Format detection'),
    'description' => t('If set to "telephone=no" the page will not be checked for phone numbers, which would be presented .'),
    'weight' => ++$weight,
  ) + $tag_info_defaults;

  $info['tags']['ios-app-link-alternative'] = array(
    'label' => t('iOS app link alternative'),
    'description' => t('A custom string for deeplinking to an iOS mobile app. Should be in the format "itunes_id/scheme/host_path", e.g. 123456/example/hello-screen". The "ios-app://" prefix will be included automatically.'),
    'class' => 'DrupalLinkMetaTag',
    'weight' => ++$weight,
    'element' => array(
      '#theme' => 'metatag_mobile_ios_app',
    ),
    'header' => FALSE,
  ) + $tag_info_defaults;

  // Default values for each meta tag.
  $tag_info_defaults = array(
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'android_mobile',
  );

  $info['tags']['android-app-link-alternative'] = array(
    'label' => t('Android app link alternative'),
    'description' => t('A custom string for deeplinking to an Android mobile app. Should be in the format "package_name/host_path", e.g. "com.example.android/example/hello-screen". The "android-app://" prefix will be included automatically.'),
    'class' => 'DrupalLinkMetaTag',
    'weight' => ++$weight,
    'element' => array(
      '#theme' => 'metatag_mobile_android_app',
    ),
    'header' => FALSE,
  ) + $tag_info_defaults;

  $info['tags']['android-manifest'] = array(
    'label' => t('Manifest'),
    'description' => t('A URL to a manifest.json file that describes the application. The <a href="https://developer.chrome.com/multidevice/android/installtohomescreen">JSON-based manifest</a> provides developers with a centralized place to put metadata associated with a web application.'),
    'class' => 'DrupalLinkMetaTag',
    'weight' => ++$weight,
    'element' => array(
      '#name' => 'manifest',
    ),
  ) + $tag_info_defaults;

  return $info;
}
