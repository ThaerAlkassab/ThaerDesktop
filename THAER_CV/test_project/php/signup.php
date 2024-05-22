<?php
include 'connection.php';

$username = $_POST['username'];
$email = $_POST['email'];
$password = password_hash($_POST['password'], PASSWORD_BCRYPT);

$sql = "INSERT INTO users_table (username, email, password) VALUES ('$username', '$email', '$password')";

if (mysqli_query($con, $sql)) {
 header('Location: ../html/login.html');
} else {
 echo "Error: " . $sql . "<br>" . mysqli_error($con);
}

mysqli_close($con);
