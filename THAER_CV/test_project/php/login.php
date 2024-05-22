<?php
session_start();
include 'connection.php';

$email = $_POST['email'];
$password = $_POST['password'];

$sql = "SELECT * FROM users_table WHERE email='$email'";
$result = mysqli_query($con, $sql);
$user = mysqli_fetch_assoc($result);

if ($user && password_verify($password, $user['password'])) {
 $_SESSION['username'] = $user['username'];
 $_SESSION['email'] = $user['email'];
 $_SESSION['role'] = $user['role'];
 header('Location: ../html/user_home.html');
} else {
 echo "Invalid credentials";
}

mysqli_close($con);
