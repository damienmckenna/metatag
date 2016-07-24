<?php

namespace Drupal\metatag_google_plus\Tests;

use Drupal\simpletest\WebTestBase;
use Drupal\metatag\Tests\MetatagTagsTestBase;

/**
 * Tests that each of the Metatag Google Plus tags work correctly.
 *
 * @group Metatag
 */
class MetatagGooglePlusTagsTest extends MetatagTagsTestBase {

  /**
   * {@inheritdoc}
   */
  public $tags = [
    'google_plus_description',
    'google_plus_image',
    'google_plus_name',
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::$modules[] = 'metatag_google_plus';
    parent::setUp();
  }

  // /**
  //  * Implements {meta_tag_name}_test_xpath() for 'twitter_cards_type'.
  //  */
  // public function twitter_cards_type_test_xpath() {
  //   return "//select[@name='twitter_cards_type']";
  // }
  //
  // /**
  //  * Implements {meta_tag_name}_test_value() for 'twitter_cards_type'.
  //  */
  // public function twitter_cards_type_test_value() {
  //   return 'summary_large_image';
  // }

}
