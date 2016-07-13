<?php

function current_posts_form($form, &$form_state) {
  $form['current_posts_max'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum number of posts'),
    '#default_value' => variable_get('current_posts_max', 3),
    '#size' => 2,
    '#maxlength' => 2,
    '#description' => t('The maximum number of links to display in the block.'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}