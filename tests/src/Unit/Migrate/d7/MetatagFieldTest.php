<?php

namespace Drupal\Tests\metatag\Unit\Migrate\d7;

use Drupal\Tests\migrate\Unit\MigrateSqlSourceTestCase;

/**
 * Tests Metatag-D7 field source plugin.
 *
 * @group metatag
 */
class MetatagFieldTest extends MigrateSqlSourceTestCase {

  const PLUGIN_CLASS = 'Drupal\metatag\Plugin\migrate\source\d7\MetatagField';

  protected $migrationConfiguration = [
    'id' => 'test',
    'source' => [
      'plugin' => 'd7_metatag_field',
    ],
  ];

  protected $expectedResults = [
    [
      'entity_type' => 'node',
    ],
    [
      'entity_type' => 'taxonomy_term',
    ],
    [
      'entity_type' => 'user',
    ],
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    // Make sure that the 'entity_type' values stay the same, so this is really
    // just a regression test.
    $this->databaseContents['metatag'] = $this->expectedResults;

    parent::setUp();
  }

}
