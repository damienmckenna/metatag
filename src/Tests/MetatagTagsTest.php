<?php

namespace Drupal\metatag\Tests;

use Drupal\simpletest\WebTestBase;
use Drupal\metatag\Tests\MetatagTagsTestBase;

/**
 * Tests that each of the Metatag base tags work correctly.
 *
 * @group Metatag
 */
class MetatagTagsTest extends MetatagTagsTestBase {

  /**
   * {@inheritdoc}
   */
  public $tags = [
    'abstract',
    'canonical_url',
    'content_language',
    'description',
    'fb_admins',
    'fb_app_id',
    'generator',
    'image_src',
    'keywords',
    'news_keywords',
    'original_source',
    'referrer',
    'rights',
    'robots',
    'shortlink',
    'standout',
    'title',
  ];

  /**
   * Implements {meta_tag_name}_test_xpath() for 'referrer'.
   */
  public function referrer_test_xpath() {
    return "//select[@name='referrer']";
  }

  /**
   * Implements {meta_tag_name}_test_xpath() for 'robots'.
   */
  public function robots_test_xpath() {
    return "//input[@name='robots[index]' and @type='checkbox']";
  }

  /**
   * Implements {meta_tag_name}_test_value() for 'referrer'.
   */
  public function referrer_test_value() {
    return 'origin';
  }

  /**
   * Implements {meta_tag_name}_test_value() for 'robots'.
   */
  public function robots_test_key() {
    return 'robots[index]';
  }

  /**
   * Implements {meta_tag_name}_test_value() for 'robots'.
   */
  public function robots_test_value() {
    return TRUE;
  }

}
