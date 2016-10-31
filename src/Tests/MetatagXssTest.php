<?php

namespace Drupal\metatag\Tests;

use Drupal\simpletest\WebTestBase;

/**
 * Ensures that metatags do not allow xss vulnerabilities.
 *
 * @group metatag
 */
class MetatagXssTest extends WebTestBase {

  /**
   * String that causes an alert when metatags aren't filtered for xss.
   *
   * @var string
   */
  private $xssString = '"><script>alert("xss");</script><meta "';

  /**
   * Rendered xss tag that has escaped attribute to avoid xss injection.
   *
   * @var string
   */
  private $escapedXssTag = '<meta name="abstract" content="&quot;&gt;alert(&quot;xss&quot;);" />';

  /**
   * String that causes an alert when metatags aren't filtered for xss.
   *
   * "Image" meta tags are processed differently to others, so this checks for a
   * different string.
   *
   * @var string
   */
  private $xssImageString = '"><script>alert("image xss");</script><meta "';

  /**
   * Rendered xss tag that has escaped attribute to avoid xss injection.
   *
   * @var string
   */
  private $escapedXssImageTag = '<meta name="image_src" content="&quot;&gt;alert(&quot;image xss&quot;);" />';

  /**
   * Administrator user for tests.
   *
   * @var \Drupal\user\UserInterface
   */
  protected $adminUser;

  /**
   * {@inheritdoc}
   */
  public static $modules = [
    'metatag',
    'node',
    'system',
    'field_ui',
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp() {
    parent::setUp();

    // Create a user that can manage content types and create content.
    $admin_permissions = [
      'administer content types',
      'administer nodes',
      'bypass node access',
      'administer meta tags',
      'administer site configuration',
      'access content',
      'administer content types',
      'administer nodes',
      'administer node fields',
    ];

    // Create and login a with the admin-ish permissions user.
    $this->adminUser = $this->drupalCreateUser($admin_permissions);
    $this->drupalLogin($this->adminUser);

    // Set up a content type.
    $this->drupalCreateContentType(['type' => 'metatag_node', 'name' => 'Test Content Type']);

    // Add a metatag field to the content type.
    $this->drupalGet('admin/structure/types/manage/metatag_node/fields/add-field');
    $this->assertResponse(200);
    $edit = [
      'label' => 'Metatag',
      'field_name' => 'metatag_field',
      'new_storage_type' => 'metatag',
    ];
    $this->drupalPostForm(NULL, $edit, t('Save and continue'));
    $this->drupalPostForm(NULL, [], t('Save field settings'));
  }

  /**
   * Verify XSS injected in global config is not rendered.
   */
  public function testXssMetatagConfig() {
    $this->drupalGet('admin/config/search/metatag/global');
    $values = [
      'abstract' => $this->xssString,
      'image_src' => $this->xssImageString
    ];
    $this->drupalPostForm(NULL, $values, 'Save');
    $this->assertText('Saved the Global Metatag defaults.');
    $this->rebuildAll();

    $this->drupalGet('<front>');
    $this->assertResponse(200);

    // Check for the basic meta tag.
    $this->assertRaw($this->escapedXssTag);
    $this->assertNoRaw($this->xssString);

    // Check for the image meta tag.
    $this->assertRaw($this->escapedXssImageTag);
    $this->assertNoRaw($this->xssImageString);
  }

  /**
   * Verify XSS injected in the entity metatag override field is not rendered.
   */
  public function testXssEntityOverride() {
    $this->drupalGet('node/add/metatag_node');
    $edit = [
      'title[0][value]' => $this->randomString(32),
      'field_metatag_field[0][basic][abstract]' => $this->xssString,
      'field_metatag_field[0][advanced][image_src]' => $this->xssImageString,
    ];
    $this->drupalPostForm(NULL, $edit, t('Save and publish'));

    // Check for the basic meta tag.
    $this->assertRaw($this->escapedXssTag);
    $this->assertNoRaw($this->xssString);

    // Check for the image meta tag.
    $this->assertRaw($this->escapedXssImageTag);
    $this->assertNoRaw($this->xssImageString);
  }

}
