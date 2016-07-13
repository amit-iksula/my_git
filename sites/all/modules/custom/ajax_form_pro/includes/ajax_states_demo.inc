<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function ajax_states_demo($form, &$form_state){
    
    //dsm($form);
    
    $form['address_form'] = array(
       '#type' => 'fieldset',       
        '#prefix' => '<div id="state_form_div">',
        '#suffix' => '</div>'
    );
    
    //dsm($form_state['values']);
    
    $country_options = _get_country();
    $form['address_form']['country'] = array(
        '#title' => t("Select country"),
        '#type' => 'select',
        '#options' => $country_options,
        '#required' => TRUE,
        '#ajax' => array(
          'callback' => '_get_state_callback',
          'wrapper' => 'state_form_div',
         ),
      );

    $country_id = isset($form_state['values']['country']) ? $form_state['values']['country'] : NULL;
     $state_options = _get_state($country_id);
        $form['address_form']['state'] = array(
        '#title' => t("Select state"),
        '#type' => 'select',
        '#options' => $state_options,
        '#required' => TRUE,
        '#ajax' => array(
          'callback' => '_get_city_callback',
          'wrapper' => 'state_form_div',
         ),
      );
        
      
    $state_id = isset($form_state['values']['state']) ? $form_state['values']['state'] : NULL;
    
      $city_options = _get_city($state_id);
      $form['address_form']['city'] = array(
        '#title' => t("Select city"),
        '#type' => 'select',
        '#options' => $city_options,
        '#required' => TRUE,
      );
    
    
    
    return $form;
}

function _get_state_callback($form, &$form_state){
//     dsm($form_state['values']);
    $form_state['values']['state'] = NULL;
    $form_state['values']['city'] = NULL;
    return $form['address_form'];
//    $form_state['rebuild'];
}

function _get_city_callback($form, &$form_state){
//     dsm($form_state['values']);
    $form_state['values']['state'] = NULL;
    $form_state['values']['city'] = NULL;
    return $form['address_form'];
//    $form_state['rebuild'];
}

function _get_country(){
    $query = db_select('country','c');
    $query->fields('c');
    $results = $query->execute()->fetchAll();
    $countrys = array();
    foreach($results as $row) {
        $countrys[$row->id] = $row->country_name;
    }
    return $countrys;

}
function _get_state($country_id = NULL){
    $query = db_select('state','s');
    $query->fields('s');    
    $query->condition('s.country_id', $country_id);
    $results = $query->execute()->fetchAll();
    $states = array();
    foreach($results as $row) {
        $states[$row->id] = $row->state_name;
    }
    return $states;
    
}
function _get_city($state_id = NULL){
    $query = db_select('city','c');
    $query->fields('c');
    $query->condition('c.state_id', $state_id);
    $results = $query->execute()->fetchAll();
    $cities = array();
    foreach($results as $row) {
        $cities[$row->id] = $row->city_name;
    }
    return $cities;
}