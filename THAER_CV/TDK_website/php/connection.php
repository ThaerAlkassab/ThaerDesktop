<?php
// Read connection details from .info.txt file
$info_file = '../.info.txt'; // Adjust the path as needed
$info = file($info_file, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

// Parse connection details
$hostname = '';
$username = '';
$password = '';
$database = '';

foreach ($info as $line) {
 list($key, $value) = explode('=', $line, 2);
 $key = trim($key);
 $value = trim($value);

 if ($key === 'hostname') {
  $hostname = $value;
 } elseif ($key === 'username') {
  $username = $value;
 } elseif ($key === 'password') {
  $password = $value;
 } elseif ($key === 'database') {
  $database = $value;
 }
}

// Create connection
$con = mysqli_connect($hostname, $username, $password, $database);

// Check connection
if (!$con) {
 die("Connection failed: " . mysqli_connect_error());
}
