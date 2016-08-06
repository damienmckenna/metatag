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
   * The attribute to look for to indicate which tag.
   */
  public $test_name_attribute = 'itemprop';

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::$modules[] = 'metatag_google_plus';
    parent::setUp();
  }

  /**
   * Each of these meta tags has a different tag name vs its internal name.
   */
  public function get_test_tag_name($tag_name) {
    return str_replace('google_plus_', 'itemprop:', $tag_name);
  }

}
