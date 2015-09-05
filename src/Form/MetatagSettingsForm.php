<?php
/**
 * @file
 * Contains \Drupal\metatag\Form\MetatagSettingsForm.
 */

namespace Drupal\metatag\Form;

use Drupal\Core\Form\FormBase;
use Drupal\Core\Form\FormStateInterface;

/**
 * Implements the settings form for Metatag.
 */
class MetatagSettingsForm extends FormBase {

  /**
   * {@inheritdoc}.
   */
  public function getFormId() {
    return 'metatag_settings';
  }

  /**
   * {@inheritdoc}.
   */
  public function buildForm(array $form, FormStateInterface $form_state) {
    $form['phone_number'] = array(
      '#type' => 'tel',
      '#title' => $this->t('Your phone number')
    );
    $form['actions']['#type'] = 'actions';
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => $this->t('Save'),
      '#button_type' => 'primary',
    );
    return $form;
  }

  /**
   * {@inheritdoc}
   */
  public function validateForm(array &$form, FormStateInterface $form_state) {
    if (strlen($form_state->getValue('phone_number')) < 3) {
      $form_state->setErrorByName('phone_number', $this->t('The phone number is too short. Please enter a full phone number.'));
    }
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {
    drupal_set_message($this->t('Your phone number is @number', array('@number' => $form_state->getValue('phone_number'))));
  }

}
