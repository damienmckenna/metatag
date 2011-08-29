<?php

/**
 * @file
 * Theme callbacks for the metatag module.
 */

function theme_metatag($variables) {
  $element = &$variables['element'];
  element_set_attributes($element, array('name', 'value'));
  unset($element['#value']);
  return theme_html_tag($variables);
}

function theme_metatag_http_equiv($variables) {
  $element = &$variables['element'];
  element_set_attributes($element, array('#name' => 'http-equiv', 'value'));
  unset($element['#value']);
  return theme_html_tag($variables);
}

function theme_metatag_link_rel($variables) {
  $element = &$variables['element'];
  element_set_attributes($element, array('#name' => 'rel', '#value' => 'href'));
  unset($element['#value']);
  return theme_html_tag($variables);
}

function theme_metatag_link_rev($variables) {
  $element = &$variables['element'];
  element_set_attributes($element, array('#name' => 'rev', '#value' => 'href'));
  unset($element['#value']);
  return theme_html_tag($variables);
}
