CREATE TABLE `letters_table` (
  `letter_ID` int(11) NOT NULL,
  `sender_name` varchar(255) NOT NULL,
  `sender_email` varchar(255) NOT NULL,
  `subject` varchar(255) NOT NULL,
  `text` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

ALTER TABLE `letters_table`
  ADD PRIMARY KEY (`letter_ID`);

ALTER TABLE `letters_table`
  MODIFY `letter_ID` int(11) NOT NULL AUTO_INCREMENT;
COMMIT;
