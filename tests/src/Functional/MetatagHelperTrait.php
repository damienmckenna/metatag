<?php

namespace Drupal\Tests\metatag\Functional;

use Drupal\user\Entity\User;
use Drupal\Component\Utility\Html;

/**
 * Misc helper functions for the automated tests.
 */
trait MetatagHelperTrait {

  /**
   * Log in as user 1.
   */
  protected function loginUser1() {
    // Load user 1.
    /* @var \Drupal\user\Entity\User $account */
    $account = User::load(1);

    // Reset the password.
    $password = 'foo';
    $account->setPassword($password)->save();

    // Support old and new tests.
    $account->passRaw = $password;
    $account->pass_raw = $password;

    // Login.
    $this->drupalLogin($account);
  }

  /**
   * {@inheritdoc}
   */
  protected function verbose($message, $title = NULL) {
    // Handle arrays, objects, etc.
    if (!is_string($message)) {
      $message = "<pre>\n" . print_r($message, TRUE) . "\n</pre>\n";
    }

    // Optional title to go before the output.
    if (!empty($title)) {
      $title = '<h2>' . Html::escape($title) . "</h2>\n";
    }

    parent::verbose($title . $message);
  }

  /**
   * Create a content type and a node.
   *
   * @param string $title
   *   A title for the node that will be returned.
   * @param string $body
   *   The text to use as the body.
   *
   * @return \Drupal\node\NodeInterface
   */
  function createContentTypeNode($title = 'Title test', $body = 'Body test') {
    $content_type = 'metatag_test';
    $args = [
      'type' => $content_type,
      'label' => 'Test content type',
    ];
    $this->createContentType($args);
    
    $args = [
      'body' => [
        [
          'value' => $body,
          'format' => filter_default_format(),
        ],
      ],
      'title' => $title,
      'type' => $content_type,
    ];

    return $this->createNode($args);
  }

}
