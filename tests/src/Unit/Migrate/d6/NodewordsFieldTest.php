<?php

namespace Drupal\Tests\metatag\Unit\Migrate\d6;

use Drupal\Tests\migrate\Unit\MigrateSqlSourceTestCase;
use Drupal\metatag\Plugin\migrate\source\d6\NodewordsField;

/**
 * Tests Nodewords-D6 field source plugin.
 *
 * Make sure that the migration system converts Nodewords' "type" value into a
 * string that Metatag can work with.
 *
 * @see Drupal\metatag\Plugin\migrate\source\d6\NodewordsField::initializeIterator()
 *
 * @group metatag
 */
class NodewordsFieldTest extends MigrateSqlSourceTestCase {

  const PLUGIN_CLASS = NodewordsField::class;

  protected $migrationConfiguration = [
    'id' => 'test',
    'source' => [
      'plugin' => 'd6_nodewords_field',
    ],
  ];

  /**
   * Example source data for the test.
   *
   * The test is focused on making sure that Nodewords' integer values are
   * converted to Metatag's strings.
   */
  protected $databaseContents = [
    'nodewords' => [
      // This represents a node.
      [
        'type' => '5',
      ],
      // This represents a taxonomy term.
      [
        'type' => '6',
      ],
      // This represents a user.
      [
        'type' => '8',
      ],
    ],
  ];

  /**
   * Expected results after going through the conversion process.
   *
   * After going through the initializeIterator() method this is what the
   * 'nodewords' value of the database's (faked) contents above should be turned
   * into.
   */
  protected $expectedResults = [
    [
      'entity_type' => 'node',
      'type' => '5',
    ],
    [
      'entity_type' => 'taxonomy_term',
      'type' => '6',
    ],
    [
      'entity_type' => 'user',
      'type' => '8',
    ],
  ];

}
