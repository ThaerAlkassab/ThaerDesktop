// script.js
document.addEventListener("DOMContentLoaded", function () {
    console.log("DOM fully loaded and parsed");
    
    const searchBtn = document.getElementById("searchBtn");
    const searchWord = document.getElementById("searchWord");
    const searchResults = document.getElementById("searchResults");

    searchBtn.addEventListener("click", function (event) {
        event.preventDefault();

        // Get the search word from the input field
        const language = document.getElementById('language').value;
        const searchWordValue = searchWord.value;

        const xhr = new XMLHttpRequest();
        xhr.open("POST", "/api/search_word");
        xhr.setRequestHeader("Content-Type", "application/json");
        xhr.onload = function () {
            if (xhr.status === 200) {
                var data = JSON.parse(xhr.responseText);
                if (data.found) {
                    // Display existing word data
                    searchResults.innerHTML = `
                        <p>Description: ${data.description}</p>
                        <audio controls>
                            <source src="${data.audio}" type="audio/mpeg">
                            Your browser does not support the audio element.
                        </audio>
                        <img src="${data.image}" alt="Word Image">
                    `;
                } else {
                    // Handle case where word was not found
                    searchResults.innerHTML = "<p>Word not found.</p>";
                }
            } else {
                // Error handling
                console.error("Request failed with status:", xhr.status);
            }
        };
        xhr.onerror = function () {
            // Error handling
            console.error("Request failed");
        };
        xhr.send(JSON.stringify({ language: language, searchWord: searchWordValue }));
    });

    const signupForm = document.getElementById("signupForm");

    signupForm.addEventListener("submit", function (event) {
        const password = document.getElementById("password");
        const confirmPassword = document.getElementById("confirmPassword");

        if (password.value !== confirmPassword.value) {
            alert("Passwords do not match");
            event.preventDefault();
        }
    });
});
