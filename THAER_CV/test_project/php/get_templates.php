<?php
include 'connection.php';

$sql = "SELECT * FROM templates_table";
$result = mysqli_query($con, $sql);

$templates = [];
while ($row = mysqli_fetch_assoc($result)) {
 $templates[] = [
  'id' => $row['template_ID'],
  'name' => $row['name']
 ];
}

echo json_encode(['templates' => $templates]);

mysqli_close($con);
