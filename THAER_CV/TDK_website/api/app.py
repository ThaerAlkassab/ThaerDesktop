# app.py
from flask import Flask, request, jsonify
from flask_cors import CORS
from database import save_to_database, search_word_in_database
from tdk_project import t_k

app = Flask(__name__)
CORS(app)  # Enable CORS for all routes

@app.route('/api/save_word', methods=['POST'])
def save_word():
    data = request.get_json()
    word = data['word']
    language = data['language']

    if search_word_in_database(word, language):
        return jsonify({'message': 'Word already exists in the database'})

    description, audio_link, image_path = t_k(word, language)
    save_to_database(word, language, description, audio_link, image_path)

    return jsonify({'message': 'Data saved successfully'})

@app.route('/api/search_word', methods=['POST'])
def search_word():
    data = request.get_json()
    language = data.get('language')
    search_word = data.get('searchWord')

    word_data = search_word_in_database(search_word, language)
    if word_data:
        return jsonify({'found': True, **word_data})
    else:
        description, audio_link, image_path = t_k(search_word, language)
        if description:
            save_to_database(search_word, language, description, audio_link, image_path)
            return jsonify({'found': True, 'word': search_word, 'language': language, 'description': description, 'audio': audio_link, 'image': image_path})
        else:
            return jsonify({'found': False})

if __name__ == '__main__':
    app.run(debug=True)
