<?php
function ajax_submit_demo($form, &$form_state)
{
    $form['#action'] = url('display-msg');
    $form['#suffix'] = '<div id="form-msg"></div>';
    $form['name'] = array(
      '#title' => t('Name'),
      '#type' => 'textfield',
      '#required' => TRUE,
    );
    // submit
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
     '#ajax' => array(
        'callback' => 'ajax_registration_form_submit',
        'wrapper' => 'form-msg'
      ),
      //'#submit' => array('ajax_registration_form_submit'),
    );
    return $form;
}
function ajax_registration_form_submit($form, &$form_state)
{ 
$name = $form_state['values']['name'];
    $query = db_insert('ajax_submit_pro');
    $query-> fields(array('name' => $name));
    $res = $query-> execute();
    if($res)
    {
     $msg = drupal_set_message('Data Save Successfully','status');
    }
    return $msg;
//dsm($form_state);
  //$content = t('Thank you for registering.');
  //return $content;
}