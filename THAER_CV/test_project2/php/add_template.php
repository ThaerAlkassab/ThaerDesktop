<?php
// Include the database connection file
require_once 'connection.php';

// Process form data
if ($_SERVER["REQUEST_METHOD"] == "POST") {
 // Retrieve form data
 $template_name = mysqli_real_escape_string($con, $_POST['template_name']);
 $questions_counter = mysqli_real_escape_string($con, $_POST['questions_counter']);
 $template_timer = mysqli_real_escape_string($con, $_POST['template_timer']);

 // Insert new template into the 'templates_table'
 $insert_query = "INSERT INTO templates_table (template_name, first_question_ID, questions_counter, template_timer) 
                     VALUES ('$template_name', -1, '$questions_counter', '$template_timer')";
 $insert_result = mysqli_query($con, $insert_query);

 if ($insert_result) {
  // Template added successfully
  echo "Template added successfully!";
 } else {
  // Error adding template
  echo "Error adding template: " . mysqli_error($con);
 }
}
