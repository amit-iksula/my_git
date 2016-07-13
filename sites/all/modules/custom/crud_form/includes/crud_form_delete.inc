<?php
 /**
  *  function for delete record from database table using db_delete.
  */
function delete_record($form, &$form_state, $id) {
    global $base_url;
    $form = confirm_form($form, 'Are you sure, Do you want to delete?', 'crud_form/form/student-list', $description = 'Are you sure, Do you want to delete?', $yes = 'Delete', $no = 'Cancel', $name = 'confirm');
  $form['user_id'] = array(
 		'#type' => 'hidden',
 		'#default_value' => $id,
 		);
    return $form;

  }
function delete_record_submit($form, &$form_state) {
	$uid = $form_state['values']['user_id'];
	if($form_state['values']['confirm'] ==1)
	{
		$del = db_delete('student_info')
                ->condition('user_id',$uid)
                ->execute();
          if($del)
          {
            drupal_goto('crud_form/form/student-list');
            drupal_set_message('Data Sucessfully deleted','status');
          }   
	}
}
