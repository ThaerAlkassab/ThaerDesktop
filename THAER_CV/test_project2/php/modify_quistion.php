<?php
// Include the database connection file
require_once 'connection.php';

// Process form submission
if ($_SERVER["REQUEST_METHOD"] == "POST") {
 // Retrieve form data
 $question_text = mysqli_real_escape_string($con, $_POST['question_text']);
 $answer_a = mysqli_real_escape_string($con, $_POST['answer_a']);
 $answer_b = mysqli_real_escape_string($con, $_POST['answer_b']);
 $answer_c = mysqli_real_escape_string($con, $_POST['answer_c']);
 $answer_d = mysqli_real_escape_string($con, $_POST['answer_d']);
 $correct_answer = mysqli_real_escape_string($con, $_POST['correct_answer']);
 $next_question_id = mysqli_real_escape_string($con, $_POST['next_question_id']);

 // Check if the next_question_id exists in the database
 $query = "SELECT * FROM questions_table WHERE question_ID = $next_question_id";
 $result = mysqli_query($con, $query);
 if (mysqli_num_rows($result) == 0) {
  // If next question ID doesn't exist, create a new question
  $insert_query = "INSERT INTO questions_table (question_text, answer_A, answer_B, answer_C, answer_D, correct_answer, next_question_ID) 
                         VALUES ('$question_text', '$answer_a', '$answer_b', '$answer_c', '$answer_d', '$correct_answer', $next_question_id)";
  mysqli_query($con, $insert_query);
 } else {
  // If next question ID exists, update the existing question
  $update_query = "UPDATE questions_table 
                         SET question_text = '$question_text', answer_A = '$answer_a', answer_B = '$answer_b', 
                             answer_C = '$answer_c', answer_D = '$answer_d', correct_answer = '$correct_answer' 
                         WHERE question_ID = $next_question_id";
  mysqli_query($con, $update_query);
 }

 // Redirect back to admin test page
 header('Location: ../admin_test.html');
 exit();
}
