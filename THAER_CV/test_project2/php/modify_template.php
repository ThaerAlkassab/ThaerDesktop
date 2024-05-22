<?php
// Include the database connection file
require_once 'connection.php';

// Process form data
if ($_SERVER["REQUEST_METHOD"] == "POST") {
 // Retrieve form data
 $template_name = mysqli_real_escape_string($con, $_POST['template_name']);
 $first_question_ID = mysqli_real_escape_string($con, $_POST['first_question_ID']);
 $questions_counter = mysqli_real_escape_string($con, $_POST['questions_counter']);
 $template_timer = mysqli_real_escape_string($con, $_POST['template_timer']);

 // Update template in the 'templates_table'
 $update_query = "UPDATE templates_table 
                        SET template_name = '$template_name', questions_counter = '$questions_counter', template_timer = '$template_timer' 
                        WHERE first_question_ID = '$first_question_ID'";
 $update_result = mysqli_query($con, $update_query);

 if ($update_result) {
  // Template modified successfully
  echo "Template modified successfully!";
 } else {
  // Error modifying template
  echo "Error modifying template: " . mysqli_error($con);
 }
}
