<?php

namespace Drupal\metatag\Tests;

use Drupal\simpletest\WebTestBase;

/**
 * Base class to test all of the meta tags that are in a specific module.
 *
 * @group Metatag
 */
abstract class MetatagTagsTestBase extends WebTestBase {

  /**
   * {@inheritdoc}
   */
  public static $modules = [
    'token',
    'metatag',
    // 'metatag_test',
  ];

  /**
   * All of the meta tags defined by this module which will be tested.
   */
  public $tags = [];

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();

    // Use the test page as the front page.
    $this->config('system.site')->set('page.front', '/test-page')->save();

    // Initiate session with a user who can manage metatags.
    $permissions = ['administer site configuration', 'administer meta tags'];
    $account = $this->drupalCreateUser($permissions);
    $this->drupalLogin($account);
  }

  /**
   * Tests that this module's tags are available.
   */
  function testTagsArePresent() {
    // Load the global config.
    $this->drupalGet('admin/config/search/metatag/global');
    $this->assertResponse(200);

    // Confirm the various meta tags are available.
    foreach ($this->tags as $tag) {
      // Look for a custom method named "{$tagname}_test_xpath", if found use
      // that method to get the xpath definition for this meta tag, otherwise it
      // defaults to just looking for a text input field.
      $method = "{$tag}_test_xpath";
      if (method_exists($this, $method)) {
        $xpath = $this->$method();
      }
      else {
        $xpath = "//input[@name='{$tag}' and @type='text']";
      }
      $this->assertFieldByXPath($xpath);
    }

    $this->drupalLogout();
  }

  /**
   * Confirm that the meta tags can be saved.
   */
  function testTagsAreSaveable() {
    // Load the global config.
    $this->drupalGet('admin/config/search/metatag/global');
    $this->assertResponse(200);

    // Update the Global defaults and test them.
    $values = [];
    foreach ($this->tags as $tag) {
      // Look for a custom method named "{$tagname}_test_key", if found use
      // that method to get the test string for this meta tag, otherwise it
      // defaults to the meta tag's name.
      $method = "{$tag}_test_key";
      if (method_exists($this, $method)) {
        $test_key = $this->$method();
      }
      else {
        $test_key = $tag;
      }

      // Look for a custom method named "{$tagname}_test_value", if found use
      // that method to get the test string for this meta tag, otherwise it
      // defaults to just generating a random string.
      $method = "{$tag}_test_value";
      if (method_exists($this, $method)) {
        $test_value = $this->$method();
      }
      else {
        $test_value = $this->randomString();
      }

      $values[$test_key] = $test_value;
    }
    $this->drupalPostForm(NULL, $values, 'Save');
    $this->assertText('Saved the Global Metatag defaults.');
    
    $this->drupalLogout();
  }

}
