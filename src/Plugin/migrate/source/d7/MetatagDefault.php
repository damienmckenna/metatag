<?php

namespace Drupal\metatag\Plugin\migrate\source\d7;

use Drupal\migrate\Row;
use Drupal\migrate_drupal\Plugin\migrate\source\DrupalSqlBase;

/**
 * Drupal 7 Metatag configuration.
 *
 * @MigrateSource(
 *   id = "d7_metatag_default",
 *   source_module = "metatag"
 * )
 */
class MetatagDefault extends DrupalSqlBase {

  /**
   * {@inheritdoc}
   */
  public function query() {
    return $this->select('metatag_config', 'm')
      ->fields('m', ['instance', 'config']);
  }

  /**
   * {@inheritdoc}
   */
  public function fields() {
    $fields = [
      'instance' => $this->t('Configuration instance'),
      'config' => $this->t('Meta tags'),
    ];
    return $fields;
  }

  /**
   * {@inheritdoc}
   */
  public function getIds() {
    $ids['instance']['type'] = 'string';
    $ids['config']['type'] = 'string';
    return $ids;
  }

  /**
   * {@inheritdoc}
   */
  public function prepareRow(Row $row) {
    parent::prepareRow($row);

    // @todo Unserialize the 'config' value to make processing easier.
    $config = $row->getSourceProperty('config');
    try {
      $config = unserialize($config);
      $row->setSourceProperty('config_expanded', $config);
    }
    catch (\Exception $e) {
      // Log an error message about this record.
      throw new MigrateSkipRowException('Unable to unserialize record %blah');
    }
  }

}
