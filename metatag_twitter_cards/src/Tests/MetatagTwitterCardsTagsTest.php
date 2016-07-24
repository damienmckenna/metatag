<?php

namespace Drupal\metatag_twitter_cards\Tests;

use Drupal\simpletest\WebTestBase;
use Drupal\metatag\Tests\MetatagTagsTestBase;

/**
 * Tests that each of the Metatag Twitter Cards tags work correctly.
 *
 * @group Metatag
 */
class MetatagTwitterCardsTagsTest extends MetatagTagsTestBase {

  /**
   * {@inheritdoc}
   */
  public $tags = [
    'twitter_cards_app_id_google_play',
    'twitter_cards_app_id_ipad',
    'twitter_cards_app_id_iphone',
    'twitter_cards_app_name_google_play',
    'twitter_cards_app_name_ipad',
    'twitter_cards_app_name_iphone',
    'twitter_cards_app_store_country',
    'twitter_cards_app_url_googleplay',
    'twitter_cards_app_url_ipad',
    'twitter_cards_app_url_iphone',
    'twitter_cards_creator',
    'twitter_cards_creator_id',
    'twitter_cards_data1',
    'twitter_cards_data2',
    'twitter_cards_description',
    'twitter_cards_gallery_image0',
    'twitter_cards_gallery_image1',
    'twitter_cards_gallery_image2',
    'twitter_cards_gallery_image3',
    'twitter_cards_image',
    'twitter_cards_image_alt',
    'twitter_cards_image_height',
    'twitter_cards_image_width',
    'twitter_cards_label1',
    'twitter_cards_label2',
    'twitter_cards_page_url',
    'twitter_cards_player',
    'twitter_cards_player_height',
    'twitter_cards_player_stream',
    'twitter_cards_player_stream_content_type',
    'twitter_cards_player_width',
    'twitter_cards_site',
    'twitter_cards_site_id',
    'twitter_cards_title',
    'twitter_cards_type',
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::$modules[] = 'metatag_twitter_cards';
    parent::setUp();
  }

  /**
   * Implements {meta_tag_name}_test_xpath() for 'twitter_cards_type'.
   */
  public function twitter_cards_type_test_xpath() {
    return "//select[@name='twitter_cards_type']";
  }

  /**
   * Implements {meta_tag_name}_test_value() for 'twitter_cards_type'.
   */
  public function twitter_cards_type_test_value() {
    return 'summary_large_image';
  }

}
