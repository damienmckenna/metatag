Metatag: Mobile
---------------
This submodule of Metatag adds a number of new meta tags commonly used for
tailoring the experience of people using mobile devices.

Mobile:
  <meta name="theme-color" value="[VALUE" />
  <meta name="MobileOptimized" value="[VALUE" />
  <meta name="HandheldFriendly" value="[VALUE" />
  <meta name="viewport" value="[VALUE" />
  <meta http-equiv="cleartype" content="[VALUE]" />

iOS:
  <meta name="apple-mobile-web-app-capable" content="[VALUE]" />
  <meta name="apple-mobile-web-app-status-bar-style" content="[VALUE]" />
  <meta name="format-detection" content="[VALUE]" />
  <link href="alternative" value="ios-app://[VALUE]" />

Android:
  <link href="manifest" value="[VALUE]" />
  <link href="alternative" value="android-app://[VALUE]" />


Configuration
--------------------------------------------------------------------------------
By default the two link alternative meta tags include a prefix - "android-app://" and "ios-app://". To remove this prefix just change the theme
functions, e.g.:

/**
 * Implements theme_metatag_mobile_android_app().
 *
  * Remove the default prefix.
 */
function MYTHEME_metatag_mobile_android_app($variables) {
  // Pass everything through to the normal 'link' tag theme.
  $variables['element']['#name'] = 'alternative';

  // Don't actually want this.
  // $variables['element']['#value'] = 'android-app://' . $variables['element']['#value'];

  return theme('metatag_link_rel', $variables);
}

/**
 * Implements theme_metatag_mobile_ios_app().
 *
  * Remove the default prefix.
 */
function MYTHEME_metatag_mobile_ios_app($variables) {
  // Pass everything through to the normal 'link' tag theme.
  $variables['element']['#name'] = 'alternative';

  // Don't actually want this.
  // $variables['element']['#value'] = 'ios-app://' . $variables['element']['#value'];

  return theme('metatag_link_rel', $variables);
}


Credits / Contact
--------------------------------------------------------------------------------
Originally developed by Damien McKenna [1].


References
--------------------------------------------------------------------------------
1: https://www.drupal.org/u/damienmckenna.
