<?php
session_start();
require "connection.php";

// Check if the form is submitted
if ($_SERVER["REQUEST_METHOD"] == "POST") {
 // Initialize variables with form data
 $name = mysqli_real_escape_string($con, $_POST['name']);
 $email = mysqli_real_escape_string($con, $_POST['email']);
 $subject = mysqli_real_escape_string($con, $_POST['subject']);
 $message = mysqli_real_escape_string($con, $_POST['message']);

 // Check if any of the fields are empty
 if (empty($name) || empty($email) || empty($subject) || empty($message)) {
  // Redirect back to the form with an error message if any field is empty
  $_SESSION['error'] = "All fields are required!";
  header("Location: user_contact_form.php");
  exit();
 } else {
  // Insert the form data into the database
  $insert_query = "INSERT INTO letters_table (sender_name, sender_email, subject, text) VALUES ('$name', '$email', '$subject', '$message')";
  $result = mysqli_query($con, $insert_query);

  if ($result) {
   // Redirect back to the form with a success message if data is successfully inserted
   $_SESSION['success'] = "Your message has been sent successfully!";
   header("Location: user_contact_form.php");
   exit();
  } else {
   // Redirect back to the form with an error message if there's an issue with inserting data
   $_SESSION['error'] = "Failed to send your message. Please try again later.";
   header("Location: user_contact_form.php");
   exit();
  }
 }
} else {
 // Redirect back to the form if the form is not submitted
 header("Location: ../about_us.html");
 exit();
}
