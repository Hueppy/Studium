<?php
require_once(__DIR__ . '/vendor/autoload.php');
session_start();
$meApi = new OpenAPI\Client\Api\MeApi();
$meApi->getConfig()
  ->setUsername($_SESSION['email'])
  ->setPassword($_SESSION['pw']);
  $meApi->meStatusPost(0);

session_destroy();
header("Location: index.php");
 ?>
