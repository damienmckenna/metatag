<?php
/**
 * @file
 * Metatag integration for the metatag_opengraph_product module.
 */

/**
 * Implements hook_metatag_info().
 */
function metatag_opengraph_products_metatag_info() {
  // Open Graph products.
  $info['groups']['open-graph-products'] = array(
    'label' => 'Open Graph - Products',
    'description' => "These Open Graph meta tags for describing products.",
    'description args' => array('@ogp' => 'http://ogp.me/'),
    'form' => array(
      '#weight' => 51,
    ),
  );

  // Default values for each meta tag.
  $defaults = array(
    'description' => '',
    'class' => 'DrupalTextMetaTag',
    'group' => 'open-graph-products',
    'element' => array(
      '#theme' => 'metatag_property',
    ),
  );

  $weight = 50;

  $info['tags']['product:price:amount'] = array(
    'label' => 'Price',
    'description' => "The numeric price with decimal point, without currency indicator. Values below 0.01 may not be supported by clients.",
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:price:currency'] = array(
    'label' => 'Currency',
    'description' => "The currency for the price (if any).",
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:availability'] = array(
    'label' => 'Availability',
    'description' => 'Case-insensitive string, possible values: "instock", "pending", "oos"; per <a href="@url">Facebook\' documentation</a>.',
    'description args' => array('@url' => 'https://developers.facebook.com/docs/reference/opengraph/object-type/product'),
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:brand'] = array(
    'label' => 'Brand',
    // 'description' => '',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:upc'] = array(
    'label' => 'UPC',
    // 'description' => '',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:ean'] = array(
    'label' => 'EAN',
    // 'description' => '',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:isbn'] = array(
    'label' => 'ISBN',
    // 'description' => '',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:plural_title'] = array(
    'label' => 'Plural Title',
    'description' => 'A title to be used to describe multiple items of this product',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:retailer'] = array(
    'label' => 'Retailer ID',
    'description' => 'A Facebook ID (or reference to the profile) of the retailer.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:retailer_title'] = array(
    'label' => 'Retailer Name',
    'description' => 'The name of the retailer.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:retailer_part_no'] = array(
    'label' => 'Retailer SKU/Product Number',
    'description' => 'A retailer part number.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:mfr_part_no'] = array(
    'label' => 'Manufacturer SKU/Part Number',
    'description' => 'A manufacturer part number.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:size'] = array(
    'label' => 'Size',
    'description' => 'A size describing the product, such as S, M, L.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:product_link'] = array(
    'label' => 'Product Link',
    'description' => 'A link to find out more about the product',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:category'] = array(
    'label' => 'Category',
    // 'description' => 'A category',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:color'] = array(
    'label' => 'Color',
    // 'description' => 'The product\'s color.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:material'] = array(
    'label' => 'Material',
    'description' => 'A description of the material used to make the product.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:pattern'] = array(
    'label' => 'Pattern',
    'description' => 'A description of the pattern used.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:shipping_cost:amount'] = array(
    'label' => 'Shipping Cost Amount',
    'description' => 'The shipping costs.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:shipping_cost:currency'] = array(
    'label' => 'Shipping Cost Currency',
    'description' => 'The shipping cost currency.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:weight:value'] = array(
    'label' => 'Product Weight',
    'description' => 'The weight, without shipping materials.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:weight:units'] = array(
    'label' => 'Product Weight Units',
    'description' => 'The unit of weight.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:shipping_weight:value'] = array(
    'label' => 'Shipping Weight',
    'description' => 'The shipping weight.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:shipping_weight:units'] = array(
    'label' => 'Shipping Weight Units',
    'description' => 'The unit of shipping weight.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:expiration_time'] = array(
    'label' => 'Expiration',
    'description' => 'A time representing when the product expired, or will expire.',
    'weight' => ++$weight,
  ) + $defaults;
  $info['tags']['product:condition'] = array(
    'label' => 'Condition',
    'description' => 'The condition of the product.',
    'weight' => ++$weight,
  ) + $defaults;

  return $info;
}
