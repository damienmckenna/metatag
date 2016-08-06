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
   * Implements {meta_tag_name}_test_field_xpath() for 'abstract'.
   */
  public function abstract_test_field_xpath() {
    return "//textarea[@name='abstract']";
  }

  /**
   * Implements {meta_tag_name}_test_name_attribute() for 'canonical_url'.
   */
  public function canonical_url_test_output_xpath() {
    return "//link[@rel='canonical']";
  }

  /**
   * Implements {meta_tag_name}_test_value_attribute() for 'canonical_url'.
   */
  public function canonical_url_test_value_attribute() {
    return 'href';
  }

  /**
   * Implements {meta_tag_name}_test_name_attribute() for 'content_language'.
   */
  public function content_language_test_name_attribute() {
    return 'http-equiv';
  }

  /**
   * Implements {meta_tag_name}_test_tag_name() for 'content_language'.
   */
  public function content_language_test_tag_name() {
    return 'content-language';
  }

  /**
   * Implements {meta_tag_name}_test_field_xpath() for 'description'.
   */
  public function description_test_field_xpath() {
    return "//textarea[@name='description']";
  }

  /**
   * Implements {meta_tag_name}_test_name_attribute() for 'fb_admins'.
   */
  public function fb_admins_test_name_attribute() {
    return 'property';
  }

  /**
   * Implements {meta_tag_name}_test_tag_name() for 'fb_admins'.
   */
  public function fb_admins_test_tag_name() {
    return 'fb:admins';
  }

  /**
   * Implements {meta_tag_name}_test_name_attribute() for 'fb_app_id'.
   */
  public function fb_app_id_test_name_attribute() {
    return 'property';
  }

  /**
   * Implements {meta_tag_name}_test_tag_name() for 'fb_app_id'.
   */
  public function fb_app_id_test_tag_name() {
    return 'fb:app_id';
  }

  /**
   * Implements {meta_tag_name}_test_tag_name() for 'original_source'.
   */
  public function original_source_test_tag_name() {
    return 'original-source';
  }

  /**
   * Implements {meta_tag_name}_test_field_xpath() for 'referrer'.
   */
  public function referrer_test_field_xpath() {
    return "//select[@name='referrer']";
  }

  /**
   * Implements {meta_tag_name}_test_field_xpath() for 'robots'.
   */
  public function robots_test_field_xpath() {
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

  /**
   * Implements {meta_tag_name}_test_output_xpath() for 'shortlink'.
   */
  public function shortlink_test_output_xpath() {
    return "//link[@rel='shortlink']";
  }

  /**
   * Implements {meta_tag_name}_test_value_attribute() for 'shortlink'.
   */
  public function shortlink_test_value_attribute() {
    return 'href';
  }

}
