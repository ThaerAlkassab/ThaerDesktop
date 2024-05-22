````markdown
# Exam Website Project

## Overview

This project is an exam website where users can sign up, log in, take tests, and view results. Admins can manage users, templates, and questions.

## Setup Instructions

1. **Clone the Repository**
   ```bash
   git clone https://github.com/yourusername/exam-website.git
   cd exam-website
   ```
````

2. **Set Up Database**

   - Create a new MySQL database.
   - Import the SQL files in the following order:
     1. `initial_setup.sql`
     2. `javascript_test_template.sql`
     3. `nodejs_test_template.sql`
     4. `create_admin_user.sql`

3. **Configure Database Connection**

   - Edit the `.info.txt` file with your database connection details:
     ```
     hostname=your_hostname
     username=your_username
     password=your_password
     database=your_database
     ```

4. **Run the Project**
   - Ensure your PHP server is running and navigate to the project directory in your browser.

## Folder Structure

- `html/`: Contains all HTML files.
- `css/`: Contains all CSS files.
- `js/`: Contains all JavaScript files.
- `db/`: Contains SQL files for setting up the database.
- `php/`: Contains PHP backend scripts.
- `img/`: Contains images used in the project.

## Features

- **User Features**:

  - Sign up
  - Log in
  - Modify profile
  - Take tests
  - View results

- **Admin Features**:
  - View user information
  - Manage templates and questions
  - Add new templates
  - Modify existing templates and questions

## Contact

For any inquiries or issues, please contact `backend1@siciliamia.com`.

````

### .info.txt
```txt
hostname=your_hostname
username=your_username
password=your_password
database=your_database
````

This should provide a comprehensive setup for the exam website project. Ensure that you replace placeholders like `your_hostname`, `your_username`, `your_password`, and `your_database` with actual values before running the project.
