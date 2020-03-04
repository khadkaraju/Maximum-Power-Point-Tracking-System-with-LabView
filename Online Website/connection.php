<?php 
$conn = new mysqli('localhost', 'root', '', 'db1');
if ($conn->connect_error) {
	die("Connection error: ". $conn->connect_error);
}
?>