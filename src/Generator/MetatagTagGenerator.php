<?php
/**
 * @file
 * Contains \Drupal\metatag\Generator\MetatagTagGenerator.
 */

namespace Drupal\metatag\Generator;

use Drupal\AppConsole\Generator\Generator;

class MetatagTagGenerator extends Generator {
  /**
   * Generator Plugin Block
   * @param $module
   * @param $name
   * @param $label
   * @param $description
   * @param $plugin_id
   * @param $class_name
   * @param $group
   * @param $weight
   */
  public function generate($module, $name, $label, $description, $plugin_id, $class_name, $group, $weight) {
    $parameters = [
      'module' => $module,
      'name' => $name,
      'label' => $label,
      'description' => $description,
      'plugin_id' => $plugin_id,
      'class_name' => $class_name,
      'group' => $group,
      'weight' => $weight,
    ];

    $this->renderFile(
      // $this->getModulePath('metatag') . '/templates/tag.php.twig',
      'tag.php.twig',
      $this->getPluginPath($module, 'metatag/Tag') . '/' . $class_name . '.php',
      $parameters
    );
  }
}
