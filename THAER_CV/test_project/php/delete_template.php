<?php
include 'connection.php';

$template_id = $_POST['template_id'];

$sql = "DELETE FROM templates_table WHERE template_ID='$template_id'";

if (mysqli_query($con, $sql)) {
 header('Location: ../html/edit_templates.html');
} else {
 echo "Error: " . $sql . "<br>" . mysqli_error($con);
}

mysqli_close($con);
