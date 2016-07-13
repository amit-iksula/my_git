<?php
/**
 * Implements hook_form.
 */
 function crud_form_form($form, &$form_state) {
	$form['full_name'] = array(
 		'#title' => 'Full Name',
 		'#type' => 'textfield',
 		'#size' => 30,
 		);
 	$form['email'] = array(
 		'#title' => 'Email Id',
 		'#type' => 'textfield',
 		'#size' => 30,
 		);
 	$form['pass'] = array(
		'#type' => 'password_confirm',
		'#size' => 25,
		);
	$form['gender'] = array(
		'#type' =>'radios', 
		'#required' => TRUE,
		'#title' => t('Gender'),

		'#options' => array(
			'male' => 'Male',
			'female' => 'Female'
			),
		);
	$form['dob'] = array(
		'#type' => 'date',
		'#title' => t('Date Of Birth'),
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
		'#required' => TRUE,
		'#title' => t('Select City'),
		'#options' => $dropdown_array,
		);
	$form['contact'] = array(
 		'#title' => 'Contact Number',
 		'#type' => 'textfield',
 		'#size' => 30,
 		);
	$form['address'] = array(
	'#type' => 'textarea',
	'#title' => t('Full Address'),
		);
	$form['submit'] = array(
 		'#type' => 'submit',
 		'#value' => 'Submit Info'
 		);
 	return $form;
  }
  /**
 * Implements hook_validate.
 */
  function crud_form_form_validate($form, &$form_state) {
  	$fname = $form_state['values']['full_name'];
  	$email_id = $form_state['values']['email'];
  	$contact = $form_state['values']['contact'];
  	$address = $form_state['values']['address'];
  	$count = 0;
  	if (!preg_match("/^[a-zA-Z ]*$/",$fname) || empty($fname)) {
  		form_set_error ('full_name',t('Please Enter Full Name'));
  		 $count++;
  	 }
  	 if (!filter_var($email_id, FILTER_VALIDATE_EMAIL)) {
  		form_set_error ('email',t('Please Enter Valid Email'));
  		$count++;
	}
	if($form_state['values']['pass'] == '' || strlen($form_state['values']['pass']) < 8 )
  	{
  		form_set_error ('pass',t('Please Enter Valid Password'));
  		 $count++;
  	}
  	if (!is_numeric($contact) || strlen($contact) != 10) {
  		form_set_error ('contact',t('Please Enter valid contact number'));
  		 $count++;
  	 }

  	if (strlen($address) < 20) {
  		form_set_error ('address',t('Please Enter Address'));
  		 $count++;
  	 }
  	 $result = db_select('student_info', 'n')
       ->fields('n', array('email'))
       ->condition('email', $email_id)
       ->execute()
       ->fetchAssoc();
       if($result > 0)
       {
       	drupal_set_message('Email Already Exists','error');
       	return false;
      }
  	 if($count > 0)
  	{
  		return false;
  	}

}	
    /**
 * Implements hook_submit.
 */
  function crud_form_form_submit($form, &$form_state) {
  	$fname = $form_state['values']['full_name'];
  	$email = $form_state['values']['email'];
  	$pass = $form_state['values']['pass'];
  	$gender = $form_state['values']['gender'];
  	$dob = $form_state['values']['dob'];
  	$city = $form_state['values']['city'];
  	$contact = $form_state['values']['contact'];
  	$address = $form_state['values']['address'];
  	$month = $dob['month'];
    $day = $dob['day'];
     if(strlen($month == 1))
        {
          $month = "0".$month;
        }
        if(strlen($day == 1))
        {
          $day = "0".$month;
        }
    $dates = $dob['year']."-". $month."-".$day;
    $tdate= strtotime($dates); 
      	$query = db_insert('student_info');
          $query-> fields(array(
          	'full_name' => $fname,
            'email' => $email,
            'pass' => $pass,
            'gender' => $gender,
            'dob' => $tdate,
            'city' => $city,
            'contact' => $contact,
            'address' => $address,
               ));
          $res = $query-> execute();
          if($res)
          {
            drupal_set_message('Data Save Successfully','status');
          }
	}							