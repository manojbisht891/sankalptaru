<?php

 /**
  * @file
  * Example rules module to create actions, events, and conditions
  */

/**
 * Implement hook_rules_action_info()

 * Declare any meta data about actions for Rules
 */

require 'sites/all/libraries/aws_sdk/aws-autoloader.php';
use Aws\Lambda\LambdaClient;
use GuzzleHttp\Psr7\Stream;
use GuzzleHttp\Client;
use GuzzleHttp\Psr7\Request;

function rules_aws_sdk_rules_action_info() {
$actions = array(
    'rules_aws_sdk_action_lambda_invoke' => array(
        'label' => t('Call lambda function'),
		'named parameter' => TRUE,
        'group' => t('AWS SDK'),
        'parameter' => array(
            'region' => array(
                'type' => 'text',
                'label' => t('Region'),
                ),
            'account' => array(
                'type' => 'text',
                'label' => t('Account'),
                ),
            'function' => array(
                'type' => 'text',
                'label' => t('Lambda function name'),
                ),
            'body' => array(
                'type' => 'text',
                'label' => t('Lambda function request body'),
                ),
            ),
        'provides' => array(
            'response' => array(
                'type' => 'text',
                'label' => t('Response'),
                ),
            ),
        ),
    'rules_aws_sdk_action_http_client' => array(
        'label' => t('Guzzle http client'),
		'named parameter' => TRUE,
        'group' => t('AWS SDK'),
        'parameter' => array(
            'base' => array(
                'type' => 'text',
                'label' => t('URL'),
                ),
            'method' => array(
                'type' => 'text',
                'label' => t('Method'),
                ),
            'header' => array(
                'type' => 'text',
                'label' => t('Request header'),
                ),
            'body' => array(
                'type' => 'text',
                'label' => t('Request body'),
                ),
            'username' => array(
                'type' => 'text',
                'label' => t('Username'),
				'optional'=> true
                ),
            'password' => array(
                'type' => 'text',
                'label' => t('Password'),
				'optional'=> true
                ),
            ),
        'provides' => array(
            'response' => array(
                'type' => 'text',
                'label' => t('Response'),
                ),
            ),
        )
    );

return $actions;
}


/** 
 * The action function for rules_aws_sdk_action_lambda_invoke
 */

function rules_aws_sdk_action_lambda_invoke($args, $element) {
        $client = LambdaClient::factory([
                'version' => 'latest',
                'region'  => $args['region'],
        ]);

        $result = $client->invoke([
                // The name your created Lamda function
                'FunctionName' => $args['function'],
                'InvocationType'=>'RequestResponse',
                'Payload'=>$args['body']
        ]);
        return array('response' =>$result->get('Payload')->getContents() );
}

function rules_aws_sdk_action_http_client($args, $element) {
	$client = new Client([
		'base_uri' => $args['base'],
		'timeout'  => 5.0,
	]);
	$retryCount = 0;
	do {
		$retry = false;
		try {
			$auth = (isset($args['username']))?['auth' => [$args['username'], $args['password']]]:'';
			$response = $client->request($args['method'], $auth);
			$responseBody = $response->getBody()->getContents();
		}
		catch(Exception $e){ 
			watchdog("AWS RULES","Call to:".$args['base'] );
			watchdog("AWS RULES",serialize($e->getMessage()) );
			if($retryCount <2){
				$retry = true; 
				$retryCount++;
			}
		}
	}
	while($retry);
    return array('response' =>$responseBody );
}
