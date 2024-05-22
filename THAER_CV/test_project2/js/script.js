document.addEventListener("DOMContentLoaded", function () {
    console.log("DOM fully loaded and parsed");

    const signupForm = document.getElementById("signupForm");

    signupForm.addEventListener("submit", function (event) {
        const password = document.getElementById("password");
        const confirmPassword = document.getElementById("confirmPassword");

        if (password.value !== confirmPassword.value) {
            alert("Passwords do not match");
            event.preventDefault();
        }
    });

    const modifyTemplateForm = document.getElementById("modifyTemplateForm");

    modifyTemplateForm.addEventListener("submit", function (event) {
        event.preventDefault();

        // Get form data
        const templateName = document.getElementById("templateName").value;
        const firstQuestionID = document.getElementById("firstQuestionID").value;
        const questionsCounter = document.getElementById("questionsCounter").value;
        const templateTimer = document.getElementById("templateTimer").value;

        // Create form data object
        const formData = {
            templateName: templateName,
            firstQuestionID: firstQuestionID,
            questionsCounter: questionsCounter,
            templateTimer: templateTimer
        };

        // Send POST request to modify_template.php
        fetch("modify_template.php", {
            method: "POST",
            body: JSON.stringify(formData),
            headers: {
                "Content-Type": "application/json"
            }
        })
        .then(response => response.text())
        .then(data => {
            console.log(data); // Log server response
            // Handle success or display error message
            // For example, show success message to user
            alert("Template modified successfully!");
        })
        .catch(error => {
            console.error("Error:", error);
            // Handle error or display error message to user
        });
    });

    const addQuestionForm = document.getElementById("addQuestionForm");

    addQuestionForm.addEventListener("submit", function (event) {
        event.preventDefault();

        // Get form data
        const questionText = document.getElementById("questionText").value;
        const answerA = document.getElementById("answerA").value;
        const answerB = document.getElementById("answerB").value;
        const answerC = document.getElementById("answerC").value;
        const answerD = document.getElementById("answerD").value;
        const correctAnswer = document.getElementById("correctAnswer").value;
        const nextQuestionID = document.getElementById("nextQuestionID").value;

        // Create form data object
        const formData = {
            questionText: questionText,
            answerA: answerA,
            answerB: answerB,
            answerC: answerC,
            answerD: answerD,
            correctAnswer: correctAnswer,
            nextQuestionID: nextQuestionID
        };

        // Send POST request to add_question.php
        fetch("add_question.php", {
            method: "POST",
            body: JSON.stringify(formData),
            headers: {
                "Content-Type": "application/json"
            }
        })
        .then(response => response.text())
        .then(data => {
            console.log(data); // Log server response
            // Handle success or display error message
            // For example, show success message to user
            alert("Question added successfully!");
        })
        .catch(error => {
            console.error("Error:", error);
            // Handle error or display error message to user
        });
    });
});
