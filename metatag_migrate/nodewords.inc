<?php

/**
 * @file
 * A basic example of using the Migrate module to import taxonomy, users, nodes,
 * and comments.
 *
 * The basic idea is
 * - The users in the source application are listed in the
 *   migrate_example_beer_account table and are transformed into Drupal users.
 * - Drupal "beer" nodes describe beers; The information to create the nodes
 *   comes from the migrate_example_beer_node table.
 * - Taxonomy terms for the beer nodes (ale, pilsner) come from the
 *   migrate_example_beer_topic table and they are applied to nodes using the
 *   source information in the migrate_example_beer_topic_node table.
 * - Comments to be attached to the beer nodes are described in the source
 *   migrate_example_beer_comment table.
 *
 * We will use the Migrate API to import and transform this data and turn it into
 * a working Drupal system.
 */

/**
 * To define a migration process from a set of source data to a particular
 * kind of Drupal object (for example, a specific node type), you define
 * a class derived from Migration. You must define a constructor to initialize
 * your migration object. By default, your class name will be the "machine name"
 * of the migration, by which you refer to it. Note that the machine name is
 * case-sensitive.
 *
 * In any serious migration project, you will find there are some options
 * which are common to the individual migrations you're implementing. You can
 * define an abstract intermediate class derived from Migration, then derive your
 * individual migrations from that, to share settings, utility functions, etc.
 */
abstract class NodewordsMigration extends Migration {
  public function __construct($arguments) {
    // Always call the parent constructor first for basic setup
    parent::__construct($arguments);

    // With migrate_ui enabled, migration pages will indicate people involved in
    // the particular migration, with their role and contact info. We default the
    // list in the shared class; it can be overridden for specific migrations.
    $this->team = array(
      // new MigrateTeamMember('Liz Taster', 'ltaster@example.com', t('Product Owner')),
      // new MigrateTeamMember('Larry Brewer', 'lbrewer@example.com', t('Implementor')),
    );

    // Individual mappings in a migration can be linked to a ticket or issue
    // in an external tracking system. Define the URL pattern here in the shared
    // class with ':id:' representing the position of the issue number, then add
    // ->issueNumber(1234) to a mapping.
    // $this->issuePattern = 'http://drupal.org/node/:id:';
  }
}

/**
 * The BeerNodeMigration uses the migrate_example_beer_node table as source
 * and creates Drupal nodes of type 'Beer' as destination.
 */
class NodewordsNodeMigration extends NodewordsMigration {
  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('');

    // Create a map object for tracking the relationships between source rows
    // and their resulting Drupal objects. Usually, you'll use the MigrateSQLMap
    // class, which uses database tables for tracking. Pass the machine name
    // (BeerTerm) of this migration to use in generating map and message tables.
    // And, pass schema definitions for the primary keys of the source and
    // destination - we need to be explicit for our source, but the destination
    // class knows its schema already.
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'bid' => array(
          'type' => 'int',
          'not null' => TRUE,
          'description' => 'Beer ID.',
          'alias' => 'b',
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // We have a more complicated query. The Migration class fundamentally
    // depends on taking a single source row and turning it into a single
    // Drupal object, so how do we deal with zero or more terms attached to
    // each node? One way (demonstrated for MySQL) is to pull them into a single
    // comma-separated list.
    $query = db_select('nodewords', 'nw')
             ->fields('nw', array('mtid', 'type', 'id', 'name', 'content'))
             // This sort assures that parents are saved before children.
             ->orderBy('type', 'ASC');

    // By default, MigrateSourceSQL derives a count query from the main query -
    // but we can override it if we know a simpler way
    $count_query = db_select('nodewords', 'nw');
    $count_query->addExpression('COUNT(mtid)', 'cnt');

    // Passing the cache_counts option means the source count (shown in
    // drush migrate-status) will be cached - this can be very handy when
    // dealing with a slow source database.
    $this->source = new MigrateSourceSQL($query, array(), $count_query,
      array('cache_counts' => TRUE));

    // Set up our destination - nodes of type migrate_example_beer
    $this->destination = new MigrateDestinationNode('metatag');

    // Mapped fields
    // $this->addFieldMapping('title', 'name')
    //      ->description(t('Mapping beer name in source to node title'));
    // $this->addFieldMapping('sticky')
    //      ->description(t('Should we default this to 0 or 1?'))
    //      ->issueGroup(t('Client questions'))
    //      ->issueNumber(765736)
    //      ->issuePriority(MigrateFieldMapping::ISSUE_PRIORITY_LOW);

    // To maintain node identities between the old and new systems (i.e., have
    // the same unique IDs), map the ID column from the old system to nid and
    // set is_new to TRUE. This works only if we're importing into a system that
    // has no existing nodes with the nids being imported.
    // $this->addFieldMapping('nid', 'bid')
    //      ->description(t('Preserve old beer ID as nid in Drupal'));
    // $this->addFieldMapping('is_new')
    //      ->defaultValue(TRUE);

    // References to related objects (such as the author of the content) are
    // most likely going to be identifiers from the source data, not Drupal
    // identifiers (such as uids). You can use the mapping from the relevant
    // migration to translate from the old ID to the Drupal identifier.
    // Note that we also provide a default value of 1 - if the lookup fails to
    // find a corresponding uid for the aid, the owner will be the administrative
    // account.
    // $this->addFieldMapping('uid', 'aid')
    //      ->sourceMigration('BeerUser')
    //      ->defaultValue(1);

    // This is a multi-value text field
    // $this->addFieldMapping('field_migrate_example_country', 'countries')
    //      ->separator('|');
    // These are related terms, which by default will be looked up by name
    // $this->addFieldMapping('migrate_example_beer_styles', 'terms')
    //      ->separator(',');

    // Some fields may have subfields such as text formats or summaries
    // (equivalent to teasers in previous Drupal versions).
    // These can be individually mapped as we see here.
    // $this->addFieldMapping('body', 'body');
    // $this->addFieldMapping('body:summary', 'excerpt');

    // Copy an image file, write DB record to files table, and save in Field storage.
    // We map the filename (relative to the source_dir below) to the field itself.
    // $this->addFieldMapping('field_migrate_example_image', 'image');
    // Here we specify the directory containing the source files.
    // $this->addFieldMapping('field_migrate_example_image:source_dir')
    //      ->defaultValue(drupal_get_path('module', 'migrate_example'));
    // And we map the alt and title values in the database to those on the
    // image.
    // $this->addFieldMapping('field_migrate_example_image:alt', 'image_alt');
    // $this->addFieldMapping('field_migrate_example_image:title', 'image_title');

    // No description for images, only alt and title
    // $this->addUnmigratedSources(array('image_description'));

    // Unmapped destination fields
    // $this->addUnmigratedDestinations(array('created', 'changed', 'status',
    //   'promote', 'revision', 'language', 'revision_uid', 'log', 'tnid',
    //   'body:format', 'body:language', 'migrate_example_beer_styles:source_type',
    //   'migrate_example_beer_styles:create_term', 'field_migrate_example_image:destination_dir',
    //   'field_migrate_example_image:language', 'field_migrate_example_image:file_replace',
    //   'field_migrate_example_image:preserve_files', 'field_migrate_example_country:language', 'comment',
    //   'field_migrate_example_image:file_class', 'field_migrate_example_image:destination_file'));
  }
}
