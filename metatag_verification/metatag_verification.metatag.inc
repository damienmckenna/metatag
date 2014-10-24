<?php
/**
 * @file
 * Metatag integration for the Metatag: Verification module.
 */

/**
 * Implements hook_metatag_info().
 */
function metatag_verification_metatag_info() {
  $info['groups']['verification'] = array(
    'label' => t('Site verification'),
    'description' => t('These meta tags are used to confirm site ownership with search engines and other services.'),
    'form' => array(
      '#weight' => 110,
    ),
  );

  // Stack the verification codes after most others.
  $weight = 100;

  // Defaults used for all meta tags.
  $defaults = array(
    'class' => 'DrupalTextMetaTag',
    'context' => array('global'),
    'group' => 'verification',
  );

  $info['tags']['google-site-verification'] = array(
    'label' => t('Google'),
    'description' => t('A string provided by <a href="https://www.google.com/">Google</a>.'),
    'weight' => ++$weight,
  ) + $defaults;

  return $info;
}
