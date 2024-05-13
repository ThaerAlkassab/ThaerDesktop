CREATE TABLE `taken_exams` (
  `exam_ID` int(11) NOT NULL,
  `user_ID` int(11) NOT NULL,
  `template_ID` int(11) NOT NULL,
  `result` float NOT NULL,
  PRIMARY KEY (`exam_ID`),
  FOREIGN KEY (`user_ID`) REFERENCES `usertable`(`id`),
  FOREIGN KEY (`template_ID`) REFERENCES `templates_table`(`template_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

ALTER TABLE `taken_exams`
  MODIFY `exam_ID` int(11) NOT NULL AUTO_INCREMENT;
