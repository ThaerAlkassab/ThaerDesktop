<?php
session_start();
require 'connection.php';

$email = $_POST['email'];
$password = $_POST['password'];

$stmt = $pdo->prepare('SELECT * FROM users WHERE email = ?');
$stmt->execute([$email]);
$user = $stmt->fetch();

if ($user && password_verify($password, $user['password'])) {
 $_SESSION['username'] = $user['username'];
 $_SESSION['email'] = $user['email'];
 header('Location: user_home.php');
 exit();
} else {
 echo "Invalid email or password.";
}
