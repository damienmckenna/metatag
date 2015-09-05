<?php
/**
 * @file
 * Contains \Drupal\metatag\Plugin\metatag\Group\Basic.
 */

namespace Drupal\metatag\Plugin\metatag\Group;

use Drupal\metatag\Plugin\metatag\Group\GroupBase;

/**
 * The basic group.
 *
 * @MetatagGroup(
 *   id = "basic",
 *   label = @Translation("Basic tags"),
 *   description = @Translation("Simple meta tags."),
 *   weight = 1
 * )
 */
class Basic extends GroupBase {
  // Inherits everything from Base.
}
