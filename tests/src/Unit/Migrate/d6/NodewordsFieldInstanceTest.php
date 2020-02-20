<?php

namespace Drupal\Tests\metatag\Unit\Migrate\d7;

use Drupal\Core\Entity\EntityManagerInterface;
use Drupal\Core\Entity\EntityTypeBundleInfo;
use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\Core\State\StateInterface;
use Drupal\metatag\Plugin\migrate\source\d6\NodewordsFieldInstance;
use Drupal\Tests\migrate\Unit\MigrateSqlSourceTestCase;

/**
 * Tests Metatag-D7 field instance source plugin.
 *
 * Make sure that the migration system converts Nodewords' "type" value into a
 * string that Metatag can work with.
 *
 * @see Drupal\metatag\Plugin\migrate\source\d6\NodewordsField::initializeIterator()
 *
 * @group metatag
 */
class NodewordsFieldInstanceTest extends MigrateSqlSourceTestCase {

  const PLUGIN_CLASS = NodewordsFieldInstance::class;

  protected $migrationConfiguration = [
    'id' => 'test',
    'source' => [
      'plugin' => 'd7_metatag_field_instance',
    ],
  ];

  protected $databaseContents =
    ['nodewords' => [
      [
        'type' => 5,
        'bundle' => 'article',
      ],
      [
        'type' => 6,
        'bundle' => 'tags',
      ],
      [
        'type' => 8,
        'bundle' => 'user',
      ],
    ],
  ];

  protected $expectedResults = [
    [
      'entity_type' => 'node',
      'type' => 5,
      'bundle' => 'test_content_type',
    ],
    [
      'entity_type' => 'taxonomy_term',
      'type' => 6,
      'bundle' => 'test_vocabulary',
    ],
    [
      'entity_type' => 'user',
      'type' => 8,
      'bundle' => 'user',
    ],
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    $module_handler = $this->getMock(ModuleHandlerInterface::class);
    $state = $this->getMock(StateInterface::class);
    $entity_manager = $this->getMock(EntityManagerInterface::class);
    $entity_type_bundle_info = $this->getMockBuilder(EntityTypeBundleInfo::class)
      ->disableOriginalConstructor()
      ->getMock();
    $entity_type_bundle_info->expects($this->any())
      ->method('getBundleInfo')
      ->willReturnMap([
        ['node', ['test_content_type' => 'test_content_type']],
        ['taxonomy_term', ['test_vocabulary' => 'test_vocabulary']],
        ['user', ['user' => 'user']],
      ]);

    $migration = $this->getMigration();
    // @todo Replace this.
    // $migration->expects($this->any())
    // ->method('getHighWater')
    // ->will($this->returnValue(static::ORIGINAL_HIGH_WATER));
    // Setup the plugin.
    $plugin_class = static::PLUGIN_CLASS;
    $plugin = new $plugin_class($this->migrationConfiguration['source'], $this->migrationConfiguration['source']['plugin'], [], $migration, $state, $entity_manager, $entity_type_bundle_info);

    // Do some reflection to set the database and moduleHandler.
    $plugin_reflection = new \ReflectionClass($plugin);
    $database_property = $plugin_reflection->getProperty('database');
    $database_property->setAccessible(TRUE);
    $module_handler_property = $plugin_reflection->getProperty('moduleHandler');
    $module_handler_property->setAccessible(TRUE);

    // Set the database and the module handler onto our plugin.
    $database_property->setValue($plugin, $this->getDatabase($this->databaseContents + ['test_map' => []]));
    $module_handler_property->setValue($plugin, $module_handler);

    $plugin->setStringTranslation($this->getStringTranslationStub());
    $migration->expects($this->any())
      ->method('getSourcePlugin')
      ->will($this->returnValue($plugin));
    $this->source = $plugin;
    $this->expectedCount = count($this->expectedResults);
  }

}
