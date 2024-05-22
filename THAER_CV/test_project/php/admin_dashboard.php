<?php
include 'connection.php';

$sql = "SELECT * FROM users_table";
$users_result = mysqli_query($con, $sql);

$users = [];
while ($row = mysqli_fetch_assoc($users_result)) {
 $users[] = $row;
}

$sql = "SELECT * FROM taken_exams";
$exams_result = mysqli_query($con, $sql);

$exams = [];
while ($row = mysqli_fetch_assoc($exams_result)) {
 $exams[] = $row;
}

echo json_encode(['users' => $users, 'exams' => $exams]);

mysqli_close($con);
