<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function ajax_dependent_demo($form, &$form_state)
{
     
   
    $form['product_form'] = array(
       '#type' => 'fieldset',       
        '#prefix' => '<div id="product_form_div">',
        '#suffix' => '</div>'
    );
    
    //dsm($form_state['values']);
    
    $category_id = isset($form_state['values']['category']) ? $form_state['values']['category'] : NULL;
    $brand_options = _get_brand($category_id);
    $form['product_form']['brand'] = array(
        '#title' => t("Select brand"),
        '#type' => 'select',
        '#options' => $brand_options,
        '#multiple' => TRUE,
        '#ajax' => array(
          'callback' => '_get_category_callback',
          'wrapper' => 'product_form_div',
         ),
      );

    $brand_id = isset($form_state['values']['brand']) ? $form_state['values']['brand'] : NULL;
     $category_options = _get_category($brand_id);
        $form['product_form']['category'] = array(
        '#title' => t("Select category"),
        '#type' => 'select',
        '#options' => $category_options,
        '#multiple' => TRUE,
        '#ajax' => array(
          'callback' => '_get_brand_callback',
          'wrapper' => 'product_form_div',
         ),
      );
        
      $form['reset'] = array(
      '#type' => 'button',
      '#value' => t('Reset'),
      '#ajax' => array(
          'callback' => 'ajax_dependent_demo_reset',
          'wrapper' => 'product_form_div',
         ),  
//      '#weight' => 100,
//      '#validate' => array(),
//      '#attributes' => array('onclick' => 'this.form.reset(); return false;'),
    );  
    return $form;    
}

function ajax_dependent_demo_reset($form, &$form_state){
    unset($form_state);
    return $form['product_form']; 
     // dsm($form_states);
}

function _get_category_callback($form, &$form_state){
//     dsm($form_state['values']);
    $form_state['values']['category'] = NULL;
//    $form_state['values']['brand'] = $form_state['values']['brand'];
    return $form['product_form'];
//    $form_state['rebuild'];
}

function _get_brand_callback($form, &$form_state){
//     dsm($form_state['values']);
    $form_state['values']['brand'] = NULL;
    return $form['product_form'];
//    $form_state['rebuild'];
}


function _get_brand($category_id){
    $query = db_select('dependent','d');
    $query->fields('d', array('brand_id', 'brand_name'));
    if(!empty($category_id))
    {
        $query->condition('category_id', $category_id);
    }
    $query->orderBy('category_id', 'ASC');
    $results = $query->distinct()->execute()->fetchAll();
    $brands = array();
    foreach($results as $row) {
        $brands[$row->brand_id]= $row->brand_name;
    }
    return $brands;
}
function _get_category($brand_id){
    $query = db_select('dependent','d');
    $query->fields('d', array('category_id', 'category_name'));
    if(!empty($brand_id))
    {
        $query->condition('brand_id', $brand_id);
    }
    $query->orderBy('brand_id', 'ASC');
    $results = $query->execute()->fetchAll();
    $category = array();
    foreach($results as $row) {
        $category[$row->category_id]= $row->category_name;
    }
    return $category;
    
}