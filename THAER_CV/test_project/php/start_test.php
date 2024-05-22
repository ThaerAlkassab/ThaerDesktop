<?php
include 'connection.php';

$template_id = $_GET['template_id'];

$sql = "SELECT * FROM questions_table WHERE template_ID='$template_id'";
$result = mysqli_query($con, $sql);

$questions = [];
while ($row = mysqli_fetch_assoc($result)) {
 $questions[] = [
  'id' => $row['question_ID'],
  'text' => $row['question_text'],
  'options' => explode("\n", $row['options'])
 ];
}

echo json_encode(['questions' => $questions]);

mysqli_close($con);
