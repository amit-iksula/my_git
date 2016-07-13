<?php

function ajax_address_demo($form, &$form_state){
     $form['address_form'] = array(
       '#type' => 'fieldset',       
        '#prefix' => '<div id="state_form_div">',
        '#suffix' => '</div>',
    );
      $form['address_form']['ccity'] = array(
        '#title' => t("Select current city"),
        '#type' => 'select',
        '#prefix' =>"Current Address",
        '#options' => array(
          'indore' => 'Indore',
          'pune' => 'Pune',
          'delhi' => 'Dehli',
          'bangalore' => 'Bangalore',
        ),
        '#required' => TRUE,
        '#ajax' => array(
          'callback' => '_get_state_callback',
          'wrapper' => 'state_form_div',
         ),
      );
      $form['address_form']['cstate'] = array(
        '#title' => t("Select state"),
        '#type' => 'select',
        '#options' => array(
          'mp' => 'Madhya Pradesh',
          'mah' => 'Maharashtra',
          'up' => 'Utter Pradesh',
          'karnataka'=> 'Karnataka',
        ),
        '#ajax' => array(
          'callback' => '_get_state_callback',
          'wrapper' => 'state_form_div',
         ),
        '#required' => TRUE,
      );
    $form['address_form']['autofill'] = array(
        '#type' => 'checkbox',
         '#title' => 'Same permanent address',
        '#value' => 'same',
    );
    
    $form['address_form']['pcity'] = array(
        '#title' => t("Permanent city"),
        '#type' => 'select',
        '#prefix' =>"Permanent Address",
        '#options' => array(
          'indore' => 'Indore',
          'pune' => 'Pune',
          'delhi' => 'Dehli',
          'bangalore' => 'Bangalore',
        ),
        '#states' => array(
         'visible' => array(
            ':input[name="autofill"]' => array('checked' => TRUE),
            ),
        ),
        '#required' => TRUE,
      '#attributes' => array(
        'disabled'=>'desabled',
        'style'=>'background: none repeat scroll 0 0 #EAEAEA;'
        ),
      );
    
    $ccity = isset($form_state['values']['ccity']) ? $form_state['values']['ccity'] : NULL;
    if($ccity != NULL)
    {
        //dsm($ccity);
        $form['address_form']['pcity']['#value'] = $ccity;
    }
    $form['address_form']['pstate'] = array(
        '#title' => t("Permanent state"),
        '#type' => 'select',
       '#options' => array(
          'mp' => 'Madhya Pradesh',
          'mah' => 'Maharashtra',
          'up' => 'Utter Pradesh',
          'karnataka'=> 'Karnataka',
        ),
        '#states' => array(
         'visible' => array(
            ':input[name="autofill"]' => array('checked' => TRUE),
            ),
        ),
      '#required' => TRUE,
      '#attributes' => array(
        'disabled'=>'desabled',
        'style'=>'background: none repeat scroll 0 0 #EAEAEA;'
        ),
      );
    $cstate = isset($form_state['values']['cstate']) ? $form_state['values']['cstate'] : NULL;
    if($cstate != NULL)
    {
        $form['address_form']['pstate']['#value'] = $cstate;
    }
      return $form;
}
function _get_state_callback($form, &$form_state){
    return $form['address_form'];
}