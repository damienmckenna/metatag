<?php

/**
 * @file
 * Contains the \Drupal\metatag\MetatagToken class.
 */

namespace Drupal\metatag;

/**
 * Token handling service. Uses core token service or contributed Token.
 */
class MetatagToken {

  /**
   * Gatekeeper function to direct to either the core or contributed Token.
   *
   * @param $string
   * @param $data
   * @param array $settings
   * @return mixed|string $string
   */
  public function tokenReplace($string, $data, $settings = array()){
    if (\Drupal::moduleHandler()->moduleExists('token')) {
      return $this->contribReplace($string, $data, $settings);
    }
    else {
      return $this->coreReplace($string, $data, $settings);
    }
  }

  /**
   * Gatekeeper function to direct to either the core or contributed Token.
   *
   * @return mixed
   */
  public function tokenBrowser() {
    // @TODO: Make these optionally return rendered HTML instead of an an array.
    if (\Drupal::moduleHandler()->moduleExists('token')) {
      return $this->contribBrowser();
    }
    else {
      return $this->coreBrowser();
    }
  }

  /**
   * Replace tokens with their values using the core token service.
   *
   * @param $string
   * @param $data
   * @param array $settings
   * @return mixed|string
   */
  private function coreReplace($string, $data, $settings = array()) {
    // @TODO: Remove this temp code.
    // This is just here as a way to see all available tokens in debugger.
    $tokens = \Drupal::token()->getInfo();

    $options = array('clear' => TRUE);

    // Replace tokens with core Token service.
    $replaced = \Drupal::token()->replace($string, $data, $options);

    // Ensure that there are no double-slash sequences due to empty token values.
    $replaced = preg_replace('/\/+/', '/', $replaced);

    return $replaced;
  }

  /**
   * Replace tokens with their values using the contributed token module.
   *
   * @param $string
   * @param $data
   * @param array $settings
   * @return mixed|string
   */
  private function contribReplace($string, $data, $settings = array()) {
    // @TODO: Add contrib Token integration when it is ready.
    // For now, just redirect to the core replacement to avoid breaking sites
    // where Token is installed.
    return $this->coreReplace($string, $data, $settings);
  }

  private function coreBrowser() {
    // @TODO: Make a browser like contrib provides using core.
    return array();
  }

  private function contribBrowser() {
    return array(
      '#type' => '#markup',
      '#theme' => 'token_tree_link',
      '#weight' => -5,
    );
  }

}
