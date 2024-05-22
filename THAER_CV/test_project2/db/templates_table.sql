CREATE TABLE `templates_table` (
  `template_ID` int(11) NOT NULL AUTO_INCREMENT,
  `template_name` varchar(255) NOT NULL,
  `first_question_ID` int(11) NOT NULL,
  `questions_counter` int(11) NOT NULL,
  `template_timer` int(11) NOT NULL,
  PRIMARY KEY (`template_ID`),
  FOREIGN KEY (`first_question_ID`) REFERENCES `questions_table`(`question_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
