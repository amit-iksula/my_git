<?php

function ajax_display_form($form, &$form_state) {
  $form = array();

  $form['form_start'] = array(
    '#type' => 'markup',    
    '#prefix' => '<div id="state_form_div">',
  );

  $form['country'] = array(
    '#title' => t("Choose Country and then state"),
    '#type' => 'select',
    '#options' => array(
      '' => 'Select',
      'ind' => 'India',
      'pak' => 'Pakistan',
      'shk' => 'Shri Lanka',
    ),
    '#ajax' => array(
      'callback' => 'ajax_demo_form_callback',
      'wrapper' => 'state_form_div',
     ),
  );
  if (!empty($form_state['values']['country'])) {
      $val = $form_state['values']['country'];
      $form['display'] = array(
        '#type' => 'textfield',
        '#value' => $val,
      );
  }
    $form['form_end'] = array(
    '#type' => 'markup',    
    '#suffix' => '</div>'
  );
    return $form;
}
function ajax_demo_form_callback($form, &$form_state)
{
    return $form;
}