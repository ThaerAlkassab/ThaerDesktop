<?php
include 'connection.php';

$template_id = $_POST['template_id'];
$name = $_POST['name'];
$question_count = $_POST['question_count'];
$time_limit = $_POST['time_limit'];

$sql = "UPDATE templates_table SET name='$name', question_count='$question_count', time_limit='$time_limit' WHERE template_ID='$template_id'";

if (mysqli_query($con, $sql)) {
 header('Location: ../html/edit_templates.html');
} else {
 echo "Error: " . $sql . "<br>" . mysqli_error($con);
}

mysqli_close($con);
