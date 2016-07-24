<?php

namespace Drupal\metatag_verification\Tests;

use Drupal\simpletest\WebTestBase;
use Drupal\metatag\Tests\MetatagTagsTestBase;

/**
 * Tests that each of the Metatag Verification tags work correctly.
 *
 * @group Metatag
 */
class MetatagVerificationTagsTest extends MetatagTagsTestBase {

  /**
   * {@inheritdoc}
   */
  public $tags = [
    'baidu',
    'bing',
    'google',
    'norton_safe_web',
    'pinterest',
    'yandex',
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::$modules[] = 'metatag_verification';
    parent::setUp();
  }
  //
  // /**
  //  * Implements {meta_tag_name}_test_xpath() for 'open_graph_type'.
  //  */
  // public function open_graph_type_test_xpath() {
  //   return "//select[@name='open_graph_type']";
  // }
  //
  // /**
  //  * Implements {meta_tag_name}_test_value() for 'open_graph_type'.
  //  */
  // public function open_graph_type_test_value() {
  //   return 'summary_large_image';
  // }

}
