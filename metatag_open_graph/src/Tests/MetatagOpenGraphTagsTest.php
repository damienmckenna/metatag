<?php

namespace Drupal\metatag_open_graph\Tests;

use Drupal\simpletest\WebTestBase;
use Drupal\metatag\Tests\MetatagTagsTestBase;

/**
 * Tests that each of the Metatag Open Graph tags work correctly.
 *
 * @group Metatag
 */
class MetatagOpenGraphTagsTest extends MetatagTagsTestBase {

  /**
   * {@inheritdoc}
   */
  public $tags = [
    'article_author',
    'article_expiration_time',
    'article_modified_time',
    'article_published_time',
    'article_publisher',
    'article_section',
    'article_tags',
    'og_country_name',
    'og_description',
    'og_determiner',
    'og_email',
    'og_fax_number',
    'og_image',
    'og_image_height',
    'og_image_secure_url',
    'og_image_type',
    'og_image_url',
    'og_image_width',
    'og_latitude',
    'og_locale',
    'og_locale_alternative',
    'og_locality',
    'og_longitude',
    'og_phone_number',
    'og_postal_code',
    'og_region',
    'og_see_also',
    'og_site_name',
    'og_street_address',
    'og_title',
    'og_type',
    'og_updated_time',
    'og_url',
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::$modules[] = 'metatag_open_graph';
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
