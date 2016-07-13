<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
function new_theme_callback() {
    return theme('my_theme');
}

function ajax_form_pro_theme() {
    return array(
      'my_theme' => array(
        'template' => 'template/mytheme',
        'variables' => array(
          'title' => 'Ajax State Example',
          'desc' => 'This is my another theme',
        ),
      ),
    );
}

function ajax_form_pro_preprocess_my_theme(&$vars) {
    $filter_form = drupal_get_form('yash_form');
      $header = array(
      array('data' => 'User Id' , 'field' => 'user_id'),
      array('data' => 'Full Name' , 'field' => 'full_name'),
      array('data' => 'Email' , 'field' => 'email'),
      array('data' => 'Password' , 'field' => 'pass'),
      array('data' => 'Gender' , 'field' => 'gender'),
      array('data' => 'DOB' , 'field' => 'dob'),
      array('data' => 'City' , 'field' => 'city'),
      array('data' => 'Contact' , 'field' => 'contact'),
      array('data' => 'Address' , 'field' => 'address'),
      array('data' => 'Edit'),
      array('data' => 'Delete'),
      );
      $rows = array();
      $query = db_select('student_info', 'n')
      ->fields('n')
      ->extend('PagerDefault')
      ->limit(2)
      ->extend('TableSort')
      ->orderByHeader($header);
      if(isset($_GET['full_name']) && !empty($_GET['full_name']))
       {
         $fname = $_GET['full_name'];
         $query->condition('full_name', '%' . db_like("$fname") . '%', 'LIKE');
       }
      if(isset($_GET['city']) && !empty($_GET['city']))
       {
         $city = $_GET['city'];
         $query->condition('city',$city);
       }
      $result = $query->execute();  
      if($result){
          foreach ($result as $key => $value) {
            $value->dob  = format_date($value->dob, 'custom', 'j M Y');
            $id = $value->user_id;
            $rows[] = array(
                $value->user_id,
                $value->full_name,
                $value->email,
                $value->pass,
                $value->gender,
                $value->dob,
                $value->city,
                $value->contact,
                $value->address,
                l('Edit',"crud_form/$id/edit"),
                l('Delete',"crud_form/$id/delete"),
              );
        }

     }
      // Format and print out table.


   $table_element = array(
    '#theme' => 'table',
    '#prefix' => drupal_render($filter_form),
    '#suffix' => theme('pager'),
    '#header' => $header,
    '#rows' => $rows,
    '#empty' =>t('Your table is empty'),
  );
   $vars['table_form'] = drupal_render($table_element);
}

/**
  *  function for create filter form.
*/ 
function yash_form($form, &$form_state )
{
  $form['full_name'] = array(
    '#title' => 'Filter By Name',
    '#type' => 'textfield',
    '#size' => 30,
    );
    $dropdown_source = taxonomy_get_tree(3);
    $dropdown_array = array('0' => '--none--');
    foreach ($dropdown_source as $item) {
    $key = $item->tid;
    $term = taxonomy_term_load($key);
    $name = $term->name;
    $value = $item->name;
    $dropdown_array[$value] = $term->name;
    }
  $form['city'] = array(
    '#type' => 'select',
    '#title' => t('Filter By City'),
    '#options' => $dropdown_array,
    );
  $form['#method'] = 'get';
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Filter',
    );
  return $form;
}

