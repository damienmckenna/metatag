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
    'label' => 'Site verification',
    'description' => 'These meta tags are used to confirm site ownership with search engines and other services.',
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
    'label' => 'Google',
    'description' => 'A string provided by <a href="https://www.google.com/">Google</a>.',
    'weight' => ++$weight,
  ) + $defaults;

  $info['tags']['p:domain_verify'] = array(
    'label' => 'Pinterest',
    'description' => 'A string provided by <a href="@pinterest">Pinterest</a>, full details are available from the <a href="@verify_url">Pinterest online help</a>.',
    'description args' => array(
      '@pinterest' => 'https://www.pinterest.com/',
      '@verify_url' => 'https://help.pinterest.com/en/articles/verify-your-website',
    ),
    'weight' => ++$weight,
  ) + $defaults;

  $info['tags']['msvalidate.01'] = array(
    'label' => 'Bing',
    'description' => 'A string provided by <a href="@bing">Bing</a>, full details are available from the <a href="@verify_url">Bing online help</a>.',
    'description args' => array(
      '@bing' => 'http://www.bing.com/',
      '@verify_url' => 'http://www.bing.com/webmaster/help/how-to-verify-ownership-of-your-site-afcfefc6',
      ),
    'weight' => ++$weight,
  ) + $defaults;

  $info['tags']['yandex-verification'] = array(
    'label' => 'Yandex',
    'description' => 'A string provided by <a href="@yandex">Yandex</a>, full details are available from the <a href="@verify_url">Yandex online help</a>.',
    'description args' => array(
      '@yandex' => 'http://www.yandex.com/',
      '@verify_url' => 'http://api.yandex.com/webmaster/doc/dg/reference/hosts-type.xml',
    ),
    'weight' => ++$weight,
  ) + $defaults;

  return $info;
}
