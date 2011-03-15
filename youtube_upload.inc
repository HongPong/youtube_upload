<?php


/**
 * @file 
 * youtube_upload.inc - Uses Zend_GData to upload to it. Code via youtube_api module too
 */

/**
 * Convenience method to obtain an authenticted Zend_Http_Client object.
 *
 * @return Zend_Http_Client An authenticated client.
 */
function getAuthSubHttpClient()
{
    try {
        $httpClient = Zend_Gdata_AuthSub::getHttpClient($_SESSION['sessionToken']);
    } catch (Zend_Gdata_App_Exception $e) {
        print 'ERROR - Could not obtain authenticated Http client object. '
            . $e->getMessage();
        return;
    }
    $httpClient->setHeaders('X-GData-Key', 'key='. $_SESSION['developerKey']);
    return $httpClient;
}


