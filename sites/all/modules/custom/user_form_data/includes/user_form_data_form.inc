<?php
/**
 * Implements hook_form.
 */
 function user_form_data_form($form, &$form_state) {

//Personal  Info Form

 	$form['first_name'] = array(
 		'#title' => 'First Name',
 		'#type' => 'textfield',
 		'#size' => 30,
 		);
 	$form['last_name'] = array(
 		'#title' => 'Last Name',
 		'#type' => 'textfield',
 		'#size' => 30,
 		);
        $form['email'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Enter Valid Email id')
                );
 	$form['pass'] = array(
		'#type' => 'password_confirm', 
		'#size' => 25,
		);
 	$form['hobby'] = array(
		'#type' =>'checkboxes', 
		'#title' => t('Hobbies'),
		'#options' => array(
		'play' => 'Play',
		'sing' => 'Sing'
		)
	);
	$form['gender'] = array(
		'#type' =>'radios', 
		'#title' => t('Gender'),
		'#options' => array(
		'male' => 'Male',
		'female' => 'Female'
		)
	);
	 
	  $form['date'] = array(
	    '#type' => 'date',
	    '#title' => t('Select Date')
  );
	   $form['address'] = array(
	    '#type' => 'textarea',
	    '#title' => t('Enter Full Address'),
	    '#resizable' => FALSE
  );
      $form['pincode'] = array(
      '#type' => 'textfield',
      '#title' => t('Enter Your City Pincode'),
      '#size' => 30,
  );

  $form['state'] = array(
   '#type' => 'select',
   '#title' => t('State'),
   '#options' => array(
   'mp' => t('Madhya Pradesh'),
   'raj' => t('Rajisthan'),
   'up' => t('Uttar Pradesh')
    ),
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
  function user_form_data_form_validate($form, &$form_state) {
    echo "<pre>"; print_r($form_state['values']); echo "</pre>";
  	$count = 0;
  
  	if($form_state['values']['first_name'] == '')
  	{
  		 form_set_error ('first_name',t('Please Enter First Name'));
  		 $count++;
  	}
  	if($form_state['values']['last_name'] == '')
  	{
  		form_set_error ('last_name',t('Please Enter First Name'));
  		 $count++;
  	}
  	if($form_state['values']['pass'] == '' || strlen($form_state['values']['pass']) < 8 )
  	{
  		form_set_error ('pass',t('Please Enter Valid Password'));
  		 $count++;
  	}
  	if(!isset($form_state['values']['gender']))
  	{
  		form_set_error ('gender',t('Please select gender'));
  		 $count++;
  	}
//         $file = file_save_upload('upload', array(
//  	'file_validate_is_image' => array(),
//  	'file_validate_extensions' => array('png gif jpg jpeg'),
//          ));
//          if ($file) {
//            if ($file = file_move($file, 'public://')) {
//              $form_state['values']['upload'] = $file;
//            }
//            else {
//              form_set_error('upload', t('Failed to write the uploaded file the site\'s file folder.'));
//            }
//          }
//          else {
//            form_set_error('upload', t('No file was uploaded.'));
//          }
      

  	// if (!valid_email_address($form['email'])) {
   //  	form_set_error('email', 'Invalid Email');
  	// }
  	if($count > 0)
  	{
  		return false;
  	}
        // else
        // {
        //   $new_query = db_insert('professional_info');
        //   $new_query-> fields(array(
        //     'employee_id' => $eid,
        //     'user_id' => $lname,
        //     'company_name' => $email,
        //     'designation' => $pass,
        //     'department' => $hobbies,
        //     'company_email' => $gender,
        //     'joining_date' => $tdate,
        //     'company_city' => $address,
        //     ));
        //   $new_query-> execute();
        // }
  }
//   /**
//  * Implements hook_submit.
//  */
 function user_form_data_form_submit($form, &$form_state) {
  $fname = $form_state['values']['first_name'];
        $lname = $form_state['values']['last_name'];
        $email = $form_state['values']['email'];
        $pass = $form_state['values']['pass'];
        $hobby = array_filter($form_state['values']['hobby']);
        $gender = $form_state['values']['gender'];
        $date = $form_state['values']['date'];
        $address = $form_state['values']['address'];
        $state = $form_state['values']['state'];
        $pin = $form_state['values']['pincode'];
        $month = $date['month'];
        $day = $date['day'];
        $hobbies = implode(",",$hobby);
        if(strlen($month == 1))
        {
          $month = "0".$month;
        }
        if(strlen($day == 1))
        {
          $day = "0".$month;
        }
        $dates = $date['year']."-". $month."-".$day;
        $tdate= strtotime($dates); 
  $query = db_insert('save_data');
          $query-> fields(array(
            'first_name' => $fname,
            'last_name' => $lname,
            'email' => $email,
            'pass' => $pass,
            'hobby' => $hobbies,
            'gender' => $gender,
            'date' => $tdate,
            'address' => $address,
            'state' => $state,
            'pincode' => $pin,
            ));
          $result = $query-> execute();
          if($result)
          {
            drupal_set_message('Data Save Successfully','status');
          }
   }
