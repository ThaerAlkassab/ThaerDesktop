# E-learning Dictionary

This project is an E-learning Dictionary developed by Thaer Alkassab and Kusai Almahamid for a Web Class Project.

## Technologies Used
- **Frontend**: HTML, CSS, JavaScript
- **Backend**: PHP and databases

## Installation Instructions

In order for this website to work properly, you need to run it locally. Follow these steps:

1. **Prepare User Data:**
   - After getting the Project Files, create a `.info.txt` file inside the project directory.
   - Add your personal data in this format:

     ```
     hostname=****
     username=****
     password=****
     database=****
     ```

     Replace `****` with your user data, and save the file.

2. **Install PHP Software:**
   - Install software that will run the PHP code. We propose using **WAMP** or **XAMPP**.

3. **Configure PHP:**
   - Go to `C:\Xampp\php\php.ini`.
   - Search for `[mail function]` and change `sendmail_from` to your personal email.
   - Modify `smtp_port` to `587` and save the file.

4. **Run WAMP or XAMPP:**
   - Start the WAMP or XAMPP server.

5. **Setup Database:**
   - Click on **admin** for MySQL.
   - Go to Database and create your database with the same name as in the `.info.txt` file.
   - Go to the import page and import the files from the `db` folder in the project folder one by one, clicking **Go** for each.

6. **Move Project Folder:**
   - Move the project folder to `C:\xampp\htdocs`.

7. **Install Python Requirements:**
   - Open the project with a code editor (we suggest **VSCode**).
   - In the terminal section, run this command:

     ```bash
     pip install -r requirements.txt
     ```

   - After it finishes, run this command:

     ```bash
     flask run
     ```

8. **Open the Project in Browser:**
   - Open your browser (recommended: **Chrome** or **Opera**).
   - Go to `localhost/"projectfolder"/index.html` (Replace `"projectfolder"` with your actual project folder name on your device).

## Contributors
- Thaer Alkassab
- Kusai Almahamid
