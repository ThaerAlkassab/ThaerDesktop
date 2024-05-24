<?php
session_start();
if (!isset($_SESSION['email'])) {
    header('Location: php/login-user.php');
    exit();
}
?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>User Homepage</title>
    <link rel="stylesheet" href="css/styles3.css">
</head>

<body>
    <header>
        <div class="header-left">
            <a href="about_us.html"><img src="img/TK.png" alt="App Icon"></a>
        </div>
        <div class="header-right">
            <a href="php/new-password.php">Welcome, <?php echo htmlspecialchars($_SESSION['name']); ?></a>
            <a href="php/logout-user.php" class="logout-link">Logout</a>
        </div>
    </header>

    <div class="content">
        <h2>Homepage</h2>
        <div class="language-list">
            <select id="language">
                <option value="english" selected>English</option>
                <option value="german">German</option>
                <option value="french">French</option>
                <option value="spanish">Spanish</option>
                <option value="italian">Italian</option>
                <option value="polish">Polish</option>
                <option value="turkish">Turkish</option>
            </select>
        </div>
        <input type="text" id="searchWord" placeholder="Enter a word">
        <button id="searchBtn">Search</button>

        <!-- Search results will be displayed here -->
        <div id="searchResults">
            <!-- JS will populate this area -->
        </div>
    </div>

    <footer>
        <div class="copyright">
            &copy; 2024 T&K for Languages Learning. All rights reserved.
        </div>
    </footer>

    <script src="js/script2.js"></script>
</body>

</html>