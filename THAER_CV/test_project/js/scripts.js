document.addEventListener('DOMContentLoaded', function() {
    // Populate exam templates
    fetch('../php/get_templates.php')
        .then(response => response.json())
        .then(data => {
            let templateList = document.getElementById('template-list');
            data.templates.forEach(template => {
                let li = document.createElement('li');
                li.innerText = template.name;
                li.setAttribute('data-template-id', template.id);
                li.addEventListener('click', function() {
                    window.location.href = `take_test.html?template_id=${template.id}`;
                });
                templateList.appendChild(li);
            });
        });

    // Populate questions for the selected template
    if (document.getElementById('question-container')) {
        let urlParams = new URLSearchParams(window.location.search);
        let templateId = urlParams.get('template_id');

        fetch(`../php/get_questions.php?template_id=${templateId}`)
            .then(response => response.json())
            .then(data => {
                let questionContainer = document.getElementById('question-container');
                data.questions.forEach((question, index) => {
                    let div = document.createElement('div');
                    div.classList.add('question');
                    div.innerHTML = `
                        <p>${index + 1}. ${question.text}</p>
                        ${question.options.map((option, i) => `
                            <label>
                                <input type="radio" name="question${index}" value="${option}">
                                ${option}
                            </label>
                        `).join('')}
                    `;
                    questionContainer.appendChild(div);
                });
            });
    }
});

function submitTest() {
    // Collect answers and submit them
    let answers = [];
    document.querySelectorAll('.question').forEach((question, index) => {
        let selectedOption = question.querySelector('input[type="radio"]:checked');
        if (selectedOption) {
            answers.push({
                question_id: index + 1,
                answer: selectedOption.value
            });
        }
    });

    fetch('../php/submit_test.php', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ answers: answers })
    })
    .then(response => response.json())
    .then(data => {
        if (data.success) {
            window.location.href = `result.html?score=${data.score}`;
        } else {
            alert('There was an error submitting the test.');
        }
    });
}
