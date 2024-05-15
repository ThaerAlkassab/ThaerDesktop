document.addEventListener('DOMContentLoaded', function() {
    document.getElementById('searchBtn').addEventListener('click', function() {
        var word = document.getElementById('searchWord').value;
        var language = document.getElementById('language').value;

        fetch('http://127.0.0.1:5000/api/search_word', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                searchWord: word,
                language: language
            })
        })
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok ' + response.statusText);
            }
            return response.json();
        })
        .then(data => {
            var searchResults = document.getElementById('searchResults');
            searchResults.innerHTML = '';

            if (data.found) {
                var result = `
                    <p><strong>Word:</strong> ${data.word}</p>
                    <p><strong>Language:</strong> ${data.language}</p>
                    <p><strong>Description:</strong> ${data.description}</p>
                    <p><strong>Audio:</strong> <audio controls src="${data.audio}"></audio></p>
                    <p><strong>Image:</strong> <img src="${data.image}" alt="${data.word}"></p>`;
                searchResults.innerHTML = result;
            } else {
                searchResults.innerHTML = '<p>Word not found</p>';
            }
        })
        .catch(error => {
            console.error('Error:', error);
            document.getElementById('searchResults').innerHTML = `<p>Error: ${error.message}</p>`;
        });
    });
});
