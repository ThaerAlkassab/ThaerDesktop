<?php
session_start();
if (!isset($_SESSION['username']) || !isset($_SESSION['email'])) {
    header('Location: login.html');
    exit();
}
?>
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="../css/styles.css">
    <title>User Home</title>
</head>

<body>
    <!-- Include header -->
    <?php include 'header_logout.html'; ?>

    <div class="container">
        <h2>Welcome,
            <?php echo $_SESSION['username']; ?>
        </h2>
        <form action="../php/update_profile.php" method="POST">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username" value="<?php echo $_SESSION['username']; ?>" required>

            <label for="email">Email:</label>
            <input type="email" id="email" name="email" value="<?php echo $_SESSION['email']; ?>" required>

            <label for="password">Password:</label>
            <input type="password" id="password" name="password">

            <button type="submit">Update Profile</button>
        </form>

        <a href="select_template.html">Take an Exam</a>
    </div>

    <!-- Include footer -->
    <?php include 'footer.html'; ?>
</body>

</html>