<?php
include 'connection.php';

$template_id = $_POST['template_id'];
$question_text = $_POST['question_text'];
$options = implode("\n", $_POST['options']);
$answer = $_POST['answer'];

$sql = "INSERT INTO questions_table (template_ID, question_text, options, answer) VALUES ('$template_id', '$question_text', '$options', '$answer')";

if (mysqli_query($con, $sql)) {
 header("Location: ../html/edit_template_question.html?template_id=$template_id");
} else {
 echo "Error: " . $sql . "<br>" . mysqli_error($con);
}

mysqli_close($con);
