Metatag
-------
This module allows you to automatically provide structured metadata, aka "meta
tags", about your website and web pages.

In the context of search engine optimization, providing an extensive set of
meta tags may help improve your site's & pages' ranking, thus may aid with
achieving a more prominent display of your content within search engine
results. Additionally, using meta tags can help control the summary content
that is used within social networks when visitors link to your site,
particularly the Open Graph submodule for use with Facebook, Pinterest,
LinkedIn, etc (see below).

This version of the module only works with the v8.0.x releases of Drupal.


Requirements
--------------------------------------------------------------------------------
Metatag for Drupal 8 requires the following:

* Token
  https://www.drupal.org/project/token
  Provides a popup browser to see the available tokens for use in meta tag
  fields.


Features
--------------------------------------------------------------------------------
The primary features include:

* An administration interface to manage default meta tags.

* Use of standard fields for entity support, allowing for meta tag translations
  and revisioning.

* A large volume of meta tags available, covering X basic tags, Y Open Graph
  tags, Z Twitter Cards tags, Å Dublin Core tags, ∫ Google+ tags, ç App Links
  tags, 8 site verification tags.

* A plugin interface allowing for additional meta tags to be easily added via
  custom modules.

* Integration with DrupalConsole [1] to provide a quick method of generating new
  meta tags.

* Site verification meta tags can be added, e.g. as used by the Google search
  engine to confirm ownership of the site; see the "Metatag: Verification"
  submodule.

* Certain meta tags used by Google+ may be added by enabling the "Metatag:
  Google+" submodule.


Standard usage scenario
--------------------------------------------------------------------------------
1. Install the module.
2. Open admin/config/search/metatag.
3. Adjust global and entity defaults. Fill in reasonable default values for any
   of the meta tags that need to be customized. Tokens may be used to
   automatically assign values.
4. You can add bundle defaults by clicking on "Add metatag defaults" and filling
   out the form.
5. If you want to adjust metatags for a specific entity, then you need to add
   the Metatag field. Follow these steps:

   5.1 Go to the "Manage fields" of the bundle where you want the metatag field
       to appear.
   5.2 Select "Meta tags" from the "Add a new field" selector.
   5.3 Fill in a label for the field, e.g. "Meta tags", and set an appropriate
       machine name, e.g. "meta_tags".
   5.4 Click the "Save and continue" button.
   5.5 If the site supports multiple languages, and translations have been
       enabled for this entity, select "Users may translate this field" to use
       Drupal's translation system.


Programmatically assign meta tags to an entity
--------------------------------------------------------------------------------
There are two ways to assign an entity's meta tags in custom module. Both
scenarios require a "Metatag" field be added to the entity's field settings, the
field name "field_meta_tags" is used but this is completely arbitrary.

Option 1:

  $entity_type = 'node';
  $values = [
    'nid' => NULL,
    'type' => 'article',
    'title' => 'Testing metatag creation',
    'uid' => 1,
    'status' => TRUE,
    'field_meta_tags' => serialize([
      'title' => 'Some title',
      'description' => 'Some description.',
      'keywords' => 'Some,Keywords',
    ]),
  ];
  $node = \Drupal::entityTypeManager()->getStorage($entity_type)->create($values);
  $node->save();

Option 2:

  $node = Node::create(array(
    'type' => article,
    'langcode' => 'en',
    'status' => 1,
    'uid' => 1,
  ));
  $node->set('title', 'Testing metatag creation');
  $node->set('field_meta_tags', serialize([
    'title' => 'Some title',
    'description' => 'Some description.',
    'keywords' => 'Some,Keywords',
  ]));
  $node->save();

In both examples, the custom meta tag values will still be merged with the
values defined via the global defaults prior to being output - it is not
necessary to copy each value to the new record.


DrupalConsole integration
--------------------------------------------------------------------------------
Using the DrupalConsole, it is possible to generate new meta tags, either for
use in new custom modules that require custom meta tags, or to create patches
for extending Metatag's options.

To generate a new tag, install DrupalConsole and then use the following command:

  drupal generate:plugin:metatag:tag

This will guide the site builder through the necessary steps to create a new
meta tag plugin and add it to a module.

There is also a command for generating meta tag groups:

  drupal generate:plugin:metatag:group

Again, this provides a guided process to create a new group.


Related modules
--------------------------------------------------------------------------------
Some modules are available that extend Metatag with additional or complimentary
functionality:

* Yoast SEO
  https://www.drupal.org/project/yoast_seo
  Adds integration with the Yoast service (https://yoast.com/).


Known issues
--------------------------------------------------------------------------------
* In order to uninstall the module any "Metatag" fields must first be removed
  from all entities. In order to see whether there are fields blocking the
  module from being uninstalled, load the module uninstall page
  (admin/modules/uninstall) and see if any are listed, it will look something
  like the following:
    The Meta tags field type is used in the following field:
    node.field_meta_tags
  In order to uninstall the module, go to the appropriate field settings pages
  and remove the Metatag field listed in the message. Once this is done it will
  be possible to uninstall the module.


Credits / contact
--------------------------------------------------------------------------------
Currently maintained by Damien McKenna [2] and Dave Reid [3]. Drupal 7 module
originally written by Dave Reid. Drupal 8 port by Damien McKenna and Michelle
Cox [4], and sponsored by Mediacurrent [5], with contributions from Lee Rowlands
[6], Rakesh James [7], Ivo Van Geertruyen [8], Michael Kandelaars [9], and many
others.

Ongoing development is sponsored by Mediacurrent and Palantir.net [10].

The best way to contact the authors is to submit an issue, be it a support
request, a feature request or a bug report, in the project issue queue:
  http://drupal.org/project/issues/metatag


References
--------------------------------------------------------------------------------
1: https://www.drupal.org/project/console
2: https://www.drupal.org/u/damienmckenna
3: https://www.drupal.org/u/dave-reid
4: https://www.drupal.org/u/michelle
5: http://www.mediacurrent.com/
6: https://www.drupal.org/u/larowlan
7: https://www.drupal.org/u/rakesh.gectcr
8: https://www.drupal.org/u/mr.baileys
9: https://www.drupal.org/u/mikeyk
10: http://www.palantir.net/
