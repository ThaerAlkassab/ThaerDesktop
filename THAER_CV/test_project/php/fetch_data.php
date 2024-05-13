<?php
// Include the database connection file
require_once 'connection.php';

// Fetch data from the 'templates_table'
$query1 = "SELECT * FROM templates_table";
$result1 = mysqli_query($con, $query1);
$templates = [];
while ($row = mysqli_fetch_assoc($result1)) {
 $templates[] = $row;
}

// Fetch data from the 'letters_table'
$query2 = "SELECT * FROM letters_table";
$result2 = mysqli_query($con, $query2);
$letters = [];
while ($row = mysqli_fetch_assoc($result2)) {
 $letters[] = $row;
}

// Fetch data from the 'taken_exams' with user and template details
$query3 = "SELECT usertable.name AS username, templates_table.template_name, taken_exams.result 
           FROM taken_exams 
           INNER JOIN usertable ON taken_exams.user_ID = usertable.id 
           INNER JOIN templates_table ON taken_exams.template_ID = templates_table.template_ID";
$result3 = mysqli_query($con, $query3);
$exams = [];
while ($row = mysqli_fetch_assoc($result3)) {
 $exams[] = $row;
}

// Combine all data sets into one array
$data = [
 'templates' => $templates,
 'letters' => $letters,
 'exams' => $exams
];

// Encode the data as JSON and print it
echo json_encode($data);
