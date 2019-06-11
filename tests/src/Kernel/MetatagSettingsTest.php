<?php

namespace Drupal\Tests\metatag\Kernel;

use Drupal\KernelTests\KernelTestBase;

/**
 * Test the Metatag settings.
 *
 * @group metatag
 */
class MetatagSettingsTest extends KernelTestBase {

  /**
   * {@inheritdoc}
   */
  public static $modules = [
    'metatag',
    'user',
  ];

  /**
   * Tests the Metatag settings.
   */
  public function testMetatagSettings() {
    $metatag_groups = \Drupal::service('metatag.manager')->sortedGroups();
    $group = reset($metatag_groups);
    $group_id = $group['id'];
    $config = \Drupal::configFactory()->getEditable('metatag.settings');
    $value = [];
    $value['user']['user'][$group_id] = $group_id;
    $config->set('entity_type_groups', $value)->save();
  }

}
