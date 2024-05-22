<?php
include 'connection.php';

$question_id = $_POST['question_id'];
$template_id = $_POST['template_id'];

$sql = "DELETE FROM questions_table WHERE question_ID='$question_id'";

if (mysqli_query($con, $sql)) {
 header("Location: ../html/edit_template_question.html?template_id=$template_id");
} else {
 echo "Error: " . $sql . "<br>" . mysqli_error($con);
}

mysqli_close($con);
