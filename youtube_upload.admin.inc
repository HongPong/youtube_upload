<?php
// $Id$

/**
 * @file
 * Administration page for youtube_upload.
 */

/**
 * Administration settings for Youtube upload.
 */
function youtube_upload_admin() {
  $form = array();
  $form['YouTubeUploadsAdmin'] = array(
    '#description' => 'This connects the public upload form to your YouTube account and registered Developer API.',
    '#title' => 'YouTube account settings',
    '#weight' => '1',
    '#type' => 'fieldset',
  );
    // the following is no longer needed but could be useful if Zend module doesn't work for you
    /*$form['YouTubeUploadsAdmin']['youtube_upload_zend_path'] = array(
    '#weight' => '-2',
    '#required' => '0',
    '#type' => 'textfield',
    '#title' => t('Path to Zend Framework [path control not implemented yet - See Readme.txt]'),
    '#default_value' => variable_get('youtube_upload_zend_path', ''),
    '#description' => 'Include trailing slash; often = /usr/local/Zend/',
  );*/
  $form['YouTubeUploadsAdmin']['official_account'] = array(
    '#weight' => '0',
    '#required' => '1',
    '#type' => 'textfield',
    '#title' => 'YouTube account for public visitors to upload into',
    '#default_value' => variable_get('youtube_upload_account', ''),
  );
  $form['YouTubeUploadsAdmin']['official_account_passwd'] = array(
    '#weight' => '1',
    '#required' => '0',
    '#type' => 'password_confirm',
    '#description' => '<B>NOTE: Re-enter your YouTube password here. It will be saved as blank if you don\'t.</b> To change the current user password, enter the new password in both fields.',
    '#title' => t('Youtube password for account'),
  // '#default_value' => variable_get('youtube_uploads_account_passwd', ''),
  );
  $form['YouTubeUploadsAdmin']['developer_api_code'] = array(
    '#description' => t('You can apply for and find your YouTube API Developer key and Client ID at the !page.', array('!page' => l(t('YouTube Developer Dashboard'), 'http://code.google.com/apis/youtube/dashboard/'))),
    '#required' => '0',
    '#weight' => '2',
    '#type' => 'textfield',
    '#title' => t('YouTube API Developer Key'),
    '#default_value' => variable_get('youtube_upload_api_code', ''),
  );
    $form['YouTubeUploadsAdmin']['youtube_upload_login_location'] = array(
    '#type' => 'textfield',
    '#title' => t('Location for API Login Calls'),
    '#default_value' => variable_get('youtube_upload_login_location', 'https://www.google.com/youtube/accounts/ClientLogin'),
    '#description' => t('This should only be changed if the YouTube API specifications change.'),

  );

  $form['YouTubeUploadsAdmin']['youtube_upload_upload_location'] = array(
      '#type' => 'textfield',
      '#title' => t('URL for API Upload Calls'),
      '#default_value' => variable_get('youtube_upload_upload_location', 'http://uploads.gdata.youtube.com/feeds/api/users/!user/uploads'),
      '#description' => t('This should only be changed if the YouTube API specifications change. !user will be replaced by the currently logged in username'),
  );
  $form['YouTubeUploadsAdmin']['youtube_upload_app_name_code'] = array(
    '#description' => 'Please provide the registered application name @ Google',
    '#required' => '0',
    '#weight' => '4',
    '#type' => 'textfield',
    '#title' => t('YouTube Application registered name'),
    '#default_value' => variable_get('youtube_upload_app_name_code', ''),
  );
  $form['YouTubeUploadsAdmin']['youtube_upload_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Debug mode'),
    '#description' => t('Debug mode shows all end users the status and content of tokens and other variables. Useful when setting up the Google API codes.'),
    '#default_value' => variable_get('youtube_upload_debug', ''),
    '#weight' => '10',
  );
  $form['#submit'][] = 'youtube_upload_admin_submit';
  return system_settings_form($form);
}

/**
 * Process youtube_upload_admin form submissions. It saves everything into the variables!
 */
function youtube_upload_admin_submit($form, $form_values) {
  if ($form_values['values']['official_account'] != 'none') {
    variable_set('youtube_upload_account', $form_values['values']['official_account']);
  }
  if ($form_values['values']['official_account_passwd'] != 'none') {
    variable_set('youtube_upload_account_passwd', $form_values['values']['official_account_passwd']);
  }
  if ($form_values['values']['developer_api_code'] != 'none') {
    variable_set('youtube_upload_api_code', $form_values['values']['developer_api_code']);
  }
  if ($form_values['values']['youtube_upload_zend_path'] != 'none') {
    variable_set('youtube_upload_zend_path', $form_values['values']['youtube_upload_zend_path']);
  }
  if ($form_values['values']['youtube_upload_app_name_code'] != 'none') {
    variable_set('youtube_upload_app_name_code', $form_values['values']['youtube_upload_app_name_code']);
  }
  if ($form_values['values']['youtube_upload_login_location'] != 'none') {
    variable_set('youtube_upload_login_location', $form_values['values']['youtube_upload_login_location']);
  }
   if ($form_values['values']['youtube_upload_upload_location'] != 'none') {
    variable_set('youtube_upload_upload_location', $form_values['values']['youtube_upload_upload_location']);
  }
   if ($form_values['values']['youtube_upload_debug'] != 'none') {
    variable_set('youtube_upload_debug', $form_values['values']['youtube_upload_debug']);
  }
  
  watchdog('youtube_upload', 'Settings saved for youtube_upload account/API', array(), WATCHDOG_NOTICE);
  $debug = (bool)variable_get('youtube_upload_debug', '');
  if ($debug) {
    drupal_set_message(t('Settings saved for Youtube Upload account with: <b>' . variable_get('youtube_upload_account', '') . '</b> and API code ' . variable_get('youtube_upload_api_code', '')));
  } else {
  drupal_set_message(t('Settings saved for Youtube Upload account with: <b>' . variable_get('youtube_upload_account', '') . '</b>', ''));
  }
}