<?php 
/**
 * Edit Form.
 */

function form_edit($form, &$form_state, $id) {
	 $result = db_select('student_info', 'n')
      ->fields('n')
      ->condition('user_id', $id)
       ->execute()
       ->fetchAssoc();
       $udate = format_date($result['dob'], 'custom', 'n j y');

	$form['full_name'] = array(
 		'#title' => 'Full Name',
 		'#type' => 'textfield',
 		'#size' => 30,
 		'#default_value' => $result['full_name'],
 		);
	$form['email'] = array(
 		'#title' => 'Email Id',
 		'#type' => 'textfield',
 		'#size' => 30,
 		'#default_value' => $result['email'],
 		);
	$form['gender'] = array(
		'#type' =>'radios', 
		'#required' => TRUE,
		'#title' => t('Gender'),
		'#default_value' => $result['gender'],
		'#options' => array(
			'male' => 'Male',
			'female' => 'Female'
			)
		);
	$form['dob'] = array(
		'#type' => 'date',
		'#title' => t('Date Of Birth'),
		'#default_value' => $udate,
		);
		$dropdown_source = taxonomy_get_tree(3);
		$dropdown_array = array('0' => '--none--');
		foreach ($dropdown_source as $item) {
			$key = $item->name;
			// $term = taxonomy_term_load($key);
			// $name = $term->name;
			$value = $item->name;
			$dropdown_array[$key] = $value;
		}
	$form['city'] = array(
		'#type' => 'select',
		'#required' => TRUE,
		'#title' => t('Select City'),
		'#default_value' => $result['city'],
		'#options' => $dropdown_array,
		);
	$form['contact'] = array(
 		'#title' => 'Contact Number',
 		'#type' => 'textfield',
 		'#size' => 30,
 		'#default_value' => $result['contact'],
 		);
	$form['address'] = array(
	'#type' => 'textarea',
	'#title' => t('Full Address'),
	'#default_value' => $result['address'],
		);
	$form['user_id'] = array(
 		'#type' => 'hidden',
 		'#default_value' => $result['user_id'],
 		);
	$form['submit'] = array(
 		'#type' => 'submit',
 		'#value' => 'Submit Info',
 		);
 	return $form;
  }

 /**
 * function to validate  Form.
 */

  function form_edit_validate($form, &$form_state) {
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
  	if (!is_numeric($contact) || strlen($contact) != 10) {
  		form_set_error ('contact',t('Please Enter valid contact number'));
  		 $count++;
  	 }

  	if (strlen($address) < 20) {
  		form_set_error ('address',t('Please Enter Address'));
  		 $count++;
  	 }
  	 if($count > 0)
  	{
  		return false;
  	}

}	
    /**
 * function for submit edit form.
 */
    function form_edit_submit($form, &$form_state) {
  	$fid = $form_state['values']['user_id'];
  	$fname = $form_state['values']['full_name'];
  	$email = $form_state['values']['email'];
  	$gender = $form_state['values']['gender'];
  	$dob = $form_state['values']['dob'];
  	$city = $form_state['values']['city'];
  	$contact = $form_state['values']['contact'];
  	$address = $form_state['values']['address'];
  	dsm($form_state);
  	exit();
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
      	$query = db_update('student_info');
          $query-> fields(array(
          	'full_name' => $fname,
            'email' => $email,
            'gender' => $gender,
            'dob' => $tdate,
            'city' => $city,
            'contact' => $contact,
            'address' => $address,
               ));
          $query->condition('user_id', $fid);
          $res = $query-> execute();
          if($res)
          {
            drupal_set_message('Data updated Successfully','status');
          }
	}			
