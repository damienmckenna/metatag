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


Features
--------------------------------------------------------------------------------
The primary features include:

* A large volume of meta tags available, covering X basic tags, Y Open Graph
  tags, Z Twitter Cards tags, Å Dublin Core tags, ∫ Google+ tags, ç App Links
  tags, ∂ site verification tags.

* Use of standard fields for entity support, allowing for meta tag translations
  and revisioning.

* A plugin interface allowing for additional meta tags to be easily added via
  custom modules.

* The front page's meta tags can be customized if a node is used for the front
  page.

* Integration with DrupalConsole [1] to provide a quick method of generating new
  meta tags.


Standard usage scenario
--------------------------------------------------------------------------------
For any entity / bundle types that require meta tag output:

* Go to the "Manage fields" page for that entity, e.g. for an "Article" content
  type it would be: admin/structure/types/manage/article/fields

* Click the "Add field" button.

* If the field was added to this type of entity before, e.g. to another content
  type:

  * In the "Re-use an existing field" selector, look for an item that starts
    with "Meta tags", e.g. "Meta tags: field_meta_tags".

  * Fill in a label for the field, e.g. "Meta tags"; the machine name cannot be
    changed.

* If the field was not added to this type of entity before:

  * Select "Meta tags" from the "Add a new field" selector.

  * Fill in a label for the field, e.g. "Meta tags", and ensure a the field's
    machine name is appropriate, e.g. "meta_tags".

* Click the "Save and continue" button.

* Note, that on the "Field settings" tab it won't be possible to change the
  "Allowed number of values", it's limited to only one item.

* Fill in an appropriate "Help text" that would be useful for the site's
  content creators & maintainers.

* If the site supports multiple languages, and translations have been enabled
  for this entity, select "Users may translate this field" to use Drupal's
  translation system.

* Fill in reasonable default values for any of the meta tags that need to be
  customized. Tokens may be used to automatically assign values; if the Token
  module is enabled there will be a "Browse available tokens" link that opens
  a popup to list & insert the available tokens.


DrupalConsole integration
--------------------------------------------------------------------------------
Using the DrupalConsole, it is possible to generate new meta tags, either for
use in new custom modules that require custom meta tags, or to create patches
for extending Metatag's options.

To generate a new tag, install DrupalConsole and then use the following command:

  drupal generate:metatag:tag

This will guide the site builder through the necessary steps to create a new
meta tag plugin and add it to a module.


Related modules
--------------------------------------------------------------------------------
Some modules are available that extend Metatag with additional functionality:

* Token
  https://www.drupal.org/project/token
  Provides a popup browser to see the available tokens for use in meta tag
  fields.


Credits / contact
--------------------------------------------------------------------------------
Currently maintained by Damien McKenna [2] and Dave Reid [3]. Drupal 7 module
originally written by Dave Reid. Drupal 8 port by Damien McKenna and Michelle
Cox [4], and sponsored by Mediacurrent [5], with contributions from Lee Rowlands
[6], Rakesh James [7] and many others.

Ongoing development is sponsored by Mediacurrent and Palantir.net [8].

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
8: http://www.palantir.net/
