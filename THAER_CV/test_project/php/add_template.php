<?php
include 'connection.php';

$name = $_POST['name'];
$question_count = $_POST['question_count'];
$time_limit = $_POST['time_limit'];

$sql = "INSERT INTO templates_table (name, question_count, time_limit) VALUES ('$name', '$question_count', '$time_limit')";

if (mysqli_query($con, $sql)) {
 header('Location: ../html/edit_templates.html');
} else {
 echo "Error: " . $sql . "<br>" . mysqli_error($con);
}

mysqli_close($con);
