# app.py
from flask import Flask, request, jsonify
from database import save_to_database, search_word_in_database
from tdk_project import t_k

app = Flask(__name__)

@app.route('/api/save_word', methods=['POST'])
def save_word():
    # Get data from request
    data = request.get_json()
    word = data['word']
    language = data['language']

    # Check if the word exists in the database
    if search_word_in_database(word, language):
        return jsonify({'message': 'Word already exists in the database'})

    # Call the t_k function to get description, audio link, and image
    description, audio_link, image_path = t_k(word, language)

    # Save data to database
    save_to_database(word, language, description, audio_link, image_path)

    return jsonify({'message': 'Data saved successfully'})

@app.route('/api/search_word', methods=['POST'])
def search_word():
    data = request.get_json()
    language = data.get('language')
    search_word = data.get('searchWord')
    
    # Check if the word exists in the database
    word_data = search_word_in_database(search_word, language)
    if word_data:
        # Word found in the database, return its information
        return jsonify({'found': True, **word_data})
    else:
        # Word not found in the database, call t_k function
        description, audio_link, image_path = t_k(search_word, language)
        if description:
            # Word found using t_k, save it to the database
            save_to_database(search_word, language, description, audio_link, image_path)
            return jsonify({'found': True, 'description': description, 'audio': audio_link, 'image': image_path})
        else:
            # Word not found using t_k
            return jsonify({'found': False})

if __name__ == '__main__':
    app.run(debug=True)
