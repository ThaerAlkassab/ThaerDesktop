<?php
// Include the database connection file
require_once 'connection.php';

// Fetch data from the 'usertable'
$query1 = "SELECT * FROM usertable";
$result1 = mysqli_query($con, $query1);
$users = [];
while ($row = mysqli_fetch_assoc($result1)) {
 $users[] = $row;
}

// Fetch data from the 'letters_table'
$query2 = "SELECT * FROM letters_table";
$result2 = mysqli_query($con, $query2);
$letters = [];
while ($row = mysqli_fetch_assoc($result2)) {
 $letters[] = $row;
}

// Combine both data sets into one array
$data = [
 'users' => $users,
 'letters' => $letters
];

// Encode the data as JSON and print it
echo json_encode($data);
