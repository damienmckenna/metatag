<?php
/**
 * @file
 * Contains \Drupal\metatag\Plugin\metatag\Group\AppLinks.
 */

namespace Drupal\metatag\Plugin\metatag\Group;

use Drupal\metatag\Plugin\metatag\Group\GroupBase;

/**
 * The App Links group.
 *
 * @MetatagGroup(
 *   id = "app_links",
 *   label = @Translation("App Links"),
 *   description = @Translation("Meta tags used to expose App Links for app deep linking. See <a href='http://applinks.org/'>applinks.org</a> for details and documentation.."),
 *   weight = 9
 * )
 */
class AppLinks extends GroupBase {
  // Inherits everything from Base.
}
