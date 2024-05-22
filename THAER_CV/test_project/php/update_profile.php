<?php
session_start();
include 'connection.php';

$username = $_POST['username'];
$email = $_POST['email'];
$password = $_POST['password'];
$user_id = $_SESSION['user_id'];

$sql = "UPDATE users_table SET username='$username', email='$email'";
if (!empty($password)) {
 $password = password_hash($password, PASSWORD_BCRYPT);
 $sql .= ", password='$password'";
}
$sql .= " WHERE user_ID='$user_id'";

if (mysqli_query($con, $sql)) {
 $_SESSION['username'] = $username;
 $_SESSION['email'] = $email;
 header('Location: ../html/user_home.html');
} else {
 echo "Error updating record: " . mysqli_error($con);
}

mysqli_close($con);
