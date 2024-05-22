<?php
include 'connection.php';
session_start();

$data = json_decode(file_get_contents('php://input'), true);
$user_id = $_SESSION['user_id'];
$template_id = $_POST['template_id'];
$answers = $_POST['answers'];

$score = 0;
foreach ($answers as $answer) {
 $question_id = $answer['question_id'];
 $selected_answer = $answer['answer'];

 $sql = "SELECT answer FROM questions_table WHERE question_ID='$question_id'";
 $result = mysqli_query($con, $sql);
 $row = mysqli_fetch_assoc($result);
 if ($row['answer'] == $selected_answer) {
  $score++;
 }
}

$sql = "INSERT INTO taken_exams (user_ID, template_ID, score) VALUES ('$user_id', '$template_id', '$score')";
if (mysqli_query($con, $sql)) {
 echo json_encode(['success' => true, 'score' => $score]);
} else {
 echo json_encode(['success' => false]);
}

mysqli_close($con);
