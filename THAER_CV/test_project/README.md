### README.md

````markdown
# Exam Website Project

## Overview

This project is an exam website where users can sign up, log in, take tests, and view results. Admins can manage users, templates, and questions.

## Setup Instructions

### Prerequisites

- PHP 7.4 or higher
- MySQL 5.7 or higher
- Apache or Nginx web server
- Composer (optional, for dependency management)

### Steps

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

   ```bash
   mysql -u your_username -p your_database < db/initial_setup.sql
   mysql -u your_username -p your_database < db/javascript_test_template.sql
   mysql -u your_username -p your_database < db/nodejs_test_template.sql
   mysql -u your_username -p your_database < db/create_admin_user.sql
   ```

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

### Folder Structure

- `html/`: Contains all HTML files.
  - `signup.html`: User registration page.
  - `login.html`: User login page.
  - `user_home.html`: User dashboard.
  - `select_template.html`: Page to select an exam template.
  - `take_test.html`: Page to take the exam.
  - `result.html`: Page to view exam results.
  - `admin_home.html`: Admin dashboard.
  - `edit_templates.html`: Page to manage exam templates.
  - `add_template.html`: Page to add a new exam template.
  - `edit_template_question.html`: Page to edit questions in a template.
  - `header_login.html`: Header for unlogged users.
  - `header_logout.html`: Header for logged users.
  - `footer.html`: Footer for all pages.
- `css/`: Contains all CSS files.
  - `styles.css`: Main stylesheet for the project.
- `js/`: Contains all JavaScript files.
  - `scripts.js`: Main JavaScript file for handling front-end logic.
- `db/`: Contains SQL files for setting up the database.
  - `initial_setup.sql`: Creates the necessary tables.
  - `javascript_test_template.sql`: Populates the JavaScript test template.
  - `nodejs_test_template.sql`: Populates the Node.js test template.
  - `create_admin_user.sql`: Creates the first admin user.
- `img/`: Contains images used in the project.
- `php/`: Contains PHP backend scripts.
  - `connection.php`: Handles the database connection.
  - `signup.php`: Handles user registration.
  - `login.php`: Handles user login.
  - `update_profile.php`: Handles user profile updates.
  - `get_templates.php`: Retrieves available exam templates.
  - `start_test.php`: Retrieves questions for the selected exam template.
  - `submit_test.php`: Handles test submission and calculates the score.
  - `admin_dashboard.php`: Retrieves user and exam data for the admin dashboard.
  - `add_template.php`: Handles adding new exam templates.
  - `edit_template.php`: Handles editing existing exam templates.
  - `delete_template.php`: Handles deleting exam templates.
  - `add_question.php`: Handles adding new questions to a template.
  - `edit_question.php`: Handles editing existing questions.
  - `delete_question.php`: Handles deleting questions.
- `README.md`: Project documentation and setup instructions.
- `.info.txt`: Contains database connection information.

### Features

#### User Features

- **Sign Up**: Users can register with a unique username, email, and password.
- **Login**: Users can log in using their email and password.
- **Modify Profile**: Users can modify their username, email, or password.
- **Take Tests**: Users can select an exam template and take the test.
- **View Results**: Users can view their exam results.

#### Admin Features

- **View Users**: Admins can view user information.
- **Manage Templates**: Admins can add, edit, and delete exam templates.
- **Manage Questions**: Admins can add, edit, and delete questions for each template.

## Contact

For any inquiries or issues, please contact `backend1@siciliamia.com`.

```

This README file provides a comprehensive overview of the project, including setup instructions, folder structure, and feature descriptions. Be sure to replace placeholders like `your_username`, `your_password`, `your_database`, and `your_hostname` with actual values before running the project.
```
