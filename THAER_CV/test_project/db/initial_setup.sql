CREATE TABLE users_table (
    user_ID INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL,
    email VARCHAR(255) NOT NULL,
    password VARCHAR(255) NOT NULL,
    role ENUM('user', 'admin') DEFAULT 'user'
);

CREATE TABLE templates_table (
    template_ID INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    question_count INT NOT NULL,
    time_limit INT NOT NULL
);

CREATE TABLE questions_table (
    question_ID INT AUTO_INCREMENT PRIMARY KEY,
    template_ID INT NOT NULL,
    question_text TEXT NOT NULL,
    options TEXT NOT NULL,
    answer VARCHAR(255) NOT NULL,
    FOREIGN KEY (template_ID) REFERENCES templates_table(template_ID)
);

CREATE TABLE taken_exams (
    exam_ID INT AUTO_INCREMENT PRIMARY KEY,
    user_ID INT NOT NULL,
    template_ID INT NOT NULL,
    score INT NOT NULL,
    taken_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_ID) REFERENCES users_table(user_ID),
    FOREIGN KEY (template_ID) REFERENCES templates_table(template_ID)
);
