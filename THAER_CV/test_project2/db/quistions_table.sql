CREATE TABLE `questions_table` (
  `question_ID` int(11) NOT NULL,
  `template_ID` int(11) NOT NULL,
  `question_text` text NOT NULL,
  `answer_A` varchar(255) NOT NULL,
  `answer_B` varchar(255) NOT NULL,
  `answer_C` varchar(255) NOT NULL,
  `answer_D` varchar(255) NOT NULL,
  `correct_answer` varchar(1) NOT NULL,
  `next_question_ID` int(11) NOT NULL,
  PRIMARY KEY (`question_ID`),
  FOREIGN KEY (`template_ID`) REFERENCES `templates_table`(`template_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

ALTER TABLE `questions_table`
  MODIFY `question_ID` int(11) NOT NULL AUTO_INCREMENT;
