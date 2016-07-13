<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function hash_states_demo($form, &$form_state){
  $form = array();

  $form['form_start'] = array(
    '#type' => 'markup',    
    '#prefix' => '<div id="state_form_div">',
  );  
  $form['address_detail'] = array(
    '#type' => 'checkbox',
    '#title' => 'Display Select Field',
  );
  
  $form['States'] = array(
    '#title' => t("Select to visible fields"),
    '#type' => 'select',
    '#options' => array(
      '' => 'Select',
      'f1' => 'Field1',
      'f2' => 'Field2',
      'f3' => 'Field3',
    ),
    '#states' =>array(
      'visible' => array(
        'input[name="address_detail"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['field1'] = array(
    '#title' => 'Name',
    '#type' => 'textfield',
    '#states' => array( 
    'visible' => array(
        'select[name="States"]' => array('value' => 'f1'),
      ),
    ),  
   ); 
    $form['state'] = array(
        '#title' => t("Choose State and then state"),
        '#type' => 'select',
        '#options' => array(
            '' => 'Select State of India',
            'mp' => 'Madhya Pradesh',
            'up' => 'Uttar Pradesh',
            'mah' => 'Maharastra',
            ),
      '#states' => array( 
            'visible' => array(
            'select[name="States"]' => array('value' => 'f2'),
      ),
    ),
   );
     	$form['gender'] = array(
		'#type' =>'radios', 
		'#required' => TRUE,
		'#title' => t('Gender'),
		'#options' => array(
			'male' => 'Male',
			'female' => 'Female'
			),
       '#states' => array( 
             'visible' => array(
                'select[name="States"]' => array('value' => 'f3'),
      ),
    ),
   );
   $form['form_end'] = array(
    '#type' => 'markup',    
    '#suffix' => '</div>'
  );
    return $form;
}