<?php
/**
 * @file
 * Metatag integration for the metatag_dc module.
 */

/**
 * Implements hook_metatag_bundled_config_alter().
 */
function metatag_dc_advanced_metatag_bundled_config_alter(array &$configs) {
  foreach ($configs as &$config) {
    switch ($config->instance) {
      case 'node':
        $config->config += array(
          'dcterms.modified' => array('value' => '[node:changed:custom:Y-m-d\TH:iP]'),
        );
        break;
    }
  }
}

/**
 * Implements hook_metatag_info().
 * Dublin Core Elements taken from http://purl.org/dc/elements/1.1/.
 */
function metatag_dc_advanced_metatag_info() {
  $info['groups']['dublin-core-additional'] = array(
    'label' => 'Dublin Core Additional Tags',
    'description' => 'These tags are not part of the Metadata Element Set but may be useful for certain scenarios.',
    'form' => array(
      '#weight' => 71,
    ),
  );

  // Dublin Core meta tags stack after the Twitter Cards tags.
  $weight = 80;

  // Additional tags.
  $defaults = array(
    'class' => 'DrupalTextMetaTag',
    'group' => 'dublin-core-additional',
    'element' => array(
      '#type' => 'term',
      '#theme' => 'metatag_dc',
    ),
  );

  $info['tags']['dcterms.abstract'] = array(
    'label' => 'Abstract',
    'description' => 'A summary of the resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.accessRights'] = array(
    'label' => 'Access rights',
    'description' => 'Information about who can access the resource or an indication of its security status.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.accrualMethod'] = array(
    'label' => 'Accrual Method',
    'description' => 'The method by which items are added to a collection.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.accrualPeriodicity'] = array(
    'label' => 'Accrual Periodicity',
    'description' => 'The frequency with which items are added to a collection.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.accrualPolicy'] = array(
    'label' => 'Accrual Policy',
    'description' => 'The policy governing the addition of items to a collection.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.alternative'] = array(
    'label' => 'Alternative Title',
    'description' => 'An alternative name for the resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.audience'] = array(
    'label' => 'Audience',
    'description' => 'A class of entity for whom the resource is intended or useful.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.available'] = array(
    'label' => 'Date Available',
    'description' => 'Date (often a range) that the resource became or will become available.',
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'date',
    ),
  ) + $defaults;
  $info['tags']['dcterms.bibliographicCitation'] = array(
    'label' => 'Bibliographic Citation',
    'description' => 'A bibliographic reference for the resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.conformsTo'] = array(
    'label' => 'Conforms To',
    'description' => 'An established standard to which the described resource conforms.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.created'] = array(
    'label' => 'Date Created',
    'description' => 'Date of creation of the resource.',
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'date',
    ),
  ) + $defaults;
  $info['tags']['dcterms.dateAccepted'] = array(
    'label' => 'Date Accepted',
    'description' => 'Date of acceptance of the resource.',
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'date',
    ),
  ) + $defaults;
  $info['tags']['dcterms.dateCopyrighted'] = array(
    'label' => 'Date Copyrighted',
    'description' => 'Date of copyright.',
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'date',
    ),
  ) + $defaults;
  $info['tags']['dcterms.dateSubmitted'] = array(
    'label' => 'Date Submitted',
    'description' => 'Date of submission of the resource.',
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'date',
    ),
  ) + $defaults;
  $info['tags']['dcterms.educationLevel'] = array(
    'label' => 'Audience Education Level',
    'description' => 'A class of entity, defined in terms of progression through an educational or training context, for which the described resource is intended.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.extent'] = array(
    'label' => 'Extent',
    'description' => 'The size or duration of the resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.hasFormat'] = array(
    'label' => 'Has Format',
    'description' => 'A related resource that is substantially the same as the pre-existing described resource, but in another format.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.hasPart'] = array(
    'label' => 'Has Part',
    'description' => 'A related resource that is included either physically or logically in the described resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.hasVersion'] = array(
    'label' => 'Has Version',
    'description' => 'A related resource that is a version, edition, or adaptation of the described resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.instructionalMethod'] = array(
    'label' => 'Instructional Method',
    'description' => 'A process, used to engender knowledge, attitudes and skills, that the described resource is designed to support.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.isFormatOf'] = array(
    'label' => 'Is Format Of',
    'description' => 'A related resource that is substantially the same as the described resource, but in another format.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.isPartOf'] = array(
    'label' => 'Is Part Of',
    'description' => 'A related resource in which the described resource is physically or logically included.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.isReferencedBy'] = array(
    'label' => 'Is Referenced By',
    'description' => 'A related resource that references, cites, or otherwise points to the described resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.isReplacedBy'] = array(
    'label' => 'Is Replaced by',
    'description' => 'A related resource that supplants, displaces, or supersedes the described resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.isRequiredBy'] = array(
    'label' => 'Is Required By',
    'description' => 'A related resource that requires the described resource to support its function, delivery, or coherence.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.isVersionOf'] = array(
    'label' => 'Is Version Of',
    'description' => 'A related resource of which the described resource is a version, edition, or adaptation.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.issued'] = array(
    'label' => 'Date Issued',
    'description' => 'Date of formal issuance (e.g., publication) of the resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.license'] = array(
    'label' => 'License',
    'description' => 'A legal document giving official permission to do something with the resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.mediator'] = array(
    'label' => 'Mediator',
    'description' => 'An entity that mediates access to the resource and for whom the resource is intended or useful.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.medium'] = array(
    'label' => 'Medium',
    'description' => 'The material or physical carrier of the resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.modified'] = array(
    'label' => 'Modified Date',
    'description' => 'Date on which the resource was changed.',
    'weight' => ++$weight,
    'devel_generate' => array(
      'type' => 'date',
    ),
  ) + $defaults;
  $info['tags']['dcterms.provenance'] = array(
    'label' => 'Provenance',
    'description' => 'A statement of any changes in ownership and custody of the resource since its creation that are significant for its authenticity, integrity, and interpretation.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.references'] = array(
    'label' => 'References',
    'description' => 'A related resource that is referenced, cited, or otherwise pointed to by the described resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.replaces'] = array(
    'label' => 'Replaces',
    'description' => 'A related resource that is supplanted, displaced, or superseded by the described resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.requires'] = array(
    'label' => 'Requires',
    'description' => 'A related resource that is required by the described resource to support its function, delivery, or coherence.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.rightsHolder'] = array(
    'label' => 'Rights Holder',
    'description' => 'A person or organization owning or managing rights over the resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.spatial'] = array(
    'label' => 'Spatial',
    'description' => 'Spatial characteristics of the resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.tableOfContents'] = array(
    'label' => 'Table Of Contents',
    'description' => 'A list of subunits of the resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.temporal'] = array(
    'label' => 'Temporal',
    'description' => 'Temporal characteristics of the resource.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['dcterms.valid'] = array(
    'label' => 'Valid',
    'description' => 'Date (often a range) of validity of a resource.',
    'weight' => ++$weight,
  ) + $defaults;

  return $info;
}
