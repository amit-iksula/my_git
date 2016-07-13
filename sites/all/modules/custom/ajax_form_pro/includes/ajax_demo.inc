<?php

function ajax_demo_form($form, &$form_state) {
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
      if($form_state['values']['country'] == 'ind'){
        $form['state'] = array(
        '#title' => t("Choose State and then state"),
        '#type' => 'select',
        '#options' => array(
            '' => 'Select State of India',
            'mp' => 'Madhya Pradesh',
            'up' => 'Uttar Pradesh',
            'mah' => 'Maharastra',
            ),
            '#ajax' => array(
                'callback' => 'display_state_callback',
                'wrapper' => 'state_form_div',
                ),
           );
        }
        if($form_state['values']['country'] == 'pak'){
           $form['state'] = array(
            '#title' => t("Choose State and then state"),
            '#type' => 'select',
            '#options' => array(
              '' => 'Select State of Pakistan',
              'bal' => 'Balochistan',
              'lp' => 'Khyber Pakhtunkhwa',
              'sin' => 'Sindh',
            ),
             '#ajax' => array(
                'callback' => 'display_state_callback',
                'wrapper' => 'state_form_div',
                ),
          );
        }
        if($form_state['values']['country'] == 'shk'){
           $form['state'] = array(
            '#title' => t("Choose State and then state"),
            '#type' => 'select',
            '#options' => array(
              '' => 'Select State of Shrilanka',
              'el' => 'Elizabeth',
              'ck' => 'Chandrika Kumaratunga',
              'mr' => 'Mahinda Rajapaksa',
            ),
             '#ajax' => array(
                'callback' => 'display_state_callback',
                'wrapper' => 'state_form_div',
                ),
          );
        }
    }
    
  if(isset($form_state['values']['state'])){
        if($form_state['values']['state'] == 'mp')
        {
           $form['city'] = array(
            '#title' => t("Choose city of selected state"),
            '#type' => 'select',
            '#options' => array(
              '' => 'Cities of Madhya Pradesh',
              'ind' => 'Indore',
              'ujn' => 'Ujjain',
              'rtlm' => 'Ratlam',
                ),
            );     
        }
  }

  $form['form_end'] = array(
    '#type' => 'markup',    
    '#suffix' => '</div>'
  );
    return $form;
}

function ajax_demo_form_callback($form, &$form_state) {
  // The form has already been submitted and updated. We can return the replaced
  // item as it is.
  //return $form['state'];
  //$form_state['rebuild'] = TRUE;
  return $form;

  // echo "hello";
}
function display_state_callback($form, &$form_state)
{
    return $form;
}

