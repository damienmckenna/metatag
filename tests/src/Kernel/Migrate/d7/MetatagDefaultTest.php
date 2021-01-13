<?php

namespace Drupal\Tests\metatag\Kernel\Migrate\d7;

use Drupal\Tests\migrate_drupal\Kernel\d7\MigrateDrupal7TestBase;

/**
 * Tests Metatag-D7 configuration source plugin.
 *
 * @group metatag
 * @covers \Drupal\metatag\Plugin\migrate\source\d7\MetatagDefault
 */
class MetatagDefaultTest extends MigrateDrupal7TestBase {

  /**
   * {@inheritdoc}
   */
  public static $modules = [
    // Core modules.
    // @see testAvailableConfigEntities
    // 'comment',
    // 'content_translation',
    // 'datetime',
    // 'filter',
    // 'image',
    'language',
    // 'link',
    // 'menu_link_content',
    // 'menu_ui',
    // 'node',
    // 'taxonomy',
    // 'telephone',
    // 'text',

    // Contrib modules.
    'token',

    // This module.
    'metatag',
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    if (version_compare(\Drupal::VERSION, '8.9', '<')) {
      $this->markTestSkipped('This test requires at least Drupal 8.9');
    }
    parent::setUp();
    $this->loadFixture(__DIR__ . '/../../../../fixtures/d7_metatag.php');

    $this->installConfig(static::$modules);
    $this->installSchema('system', ['sequences']);
    $this->installEntitySchema('metatag_defaults');

    // @todo Can any of these be skipped?
    $this->executeMigrations([
      'language',
      'd7_metatag_default',
    ]);
  }

  /**
   * Test Metatag default configuration migration from Drupal 7 to 8.
   */
  public function testMetatag() {
    // @todo Load Metatag configuration entities.
    // @todo Confirm the Metatag configuration entities have the expected data.
  }

}
