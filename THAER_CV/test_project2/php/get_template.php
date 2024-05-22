<?php
// Include the database connection file
require_once 'connection.php';

// Check if template ID is provided via GET request
if (isset($_GET['templateID'])) {
 // Sanitize the template ID
 $templateID = mysqli_real_escape_string($con, $_GET['templateID']);

 // Fetch template data from the database
 $query = "SELECT * FROM templates_table WHERE template_ID = $templateID";
 $result = mysqli_query($con, $query);

 if ($result && mysqli_num_rows($result) > 0) {
  $templateData = mysqli_fetch_assoc($result);

  // Return template data as JSON response
  echo json_encode($templateData);
 } else {
  echo "Template not found";
 }
} else {
 echo "Invalid request";
}
