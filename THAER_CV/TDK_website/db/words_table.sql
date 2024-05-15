CREATE TABLE `words_table` (
  `word_ID` INT AUTO_INCREMENT PRIMARY KEY,
  `word` VARCHAR(255) NOT NULL,
  `language` VARCHAR(255) NOT NULL,
  `description` TEXT,
  `audio` VARCHAR(1000),
  `image` VARCHAR(255) 
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
