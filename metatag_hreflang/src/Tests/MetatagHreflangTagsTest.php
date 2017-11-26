<?php

namespace Drupal\metatag_hreflang\Tests;

use Drupal\metatag\Tests\MetatagTagsTestBase;

/**
 * Tests that each of the Metatag hreflang tags work correctly.
 *
 * @group metatag
 */
class MetatagHreflangTagsTest extends MetatagTagsTestBase {

  /**
   * {@inheritdoc}
   */
  private $tags = [
    'hreflang_xdefault',
  ];

  /**
   * {@inheritdoc}
   */
  private $testTag = 'link';

  /**
   * {@inheritdoc}
   */
  private $testNameAttribute = 'hreflang';

  /**
   * {@inheritdoc}
   */
  private $testValueAttribute = 'href';

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::$modules[] = 'metatag_hreflang';
    parent::setUp();
  }

  /**
   * Each of these meta tags has a different tag name vs its internal name.
   */
  private function getTestTagName($tag_name) {
    return str_replace('hreflang_', '', $tag_name);
  }

  /**
   * Implements {tag_name}TestOutputXpath() for 'hreflang_xdefault'.
   */
  private function hreflangXdefaultTestOutputXpath() {
    return "//link[@hreflang='x-default']";
  }

}
