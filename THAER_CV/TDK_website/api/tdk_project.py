import os
import torch
from diffusers import StableDiffusionPipeline
from PIL import Image
from googletrans import Translator
import requests
import inflect
from PyMultiDictionary import MultiDictionary
from urllib.request import urlretrieve

# Download stable diffusion model from Hugging Face
modelid = "CompVis/stable-diffusion-v1-4"
device = "cuda" if torch.cuda.is_available() else "cpu"
stable_diffusion_model = StableDiffusionPipeline.from_pretrained(modelid)
stable_diffusion_model.to(device)

# Generate image from text
def generate(text):
    """ This function generates an image from text with stable diffusion """
    output = stable_diffusion_model(text, guidance_scale=8.5)
    print("Output keys:", output.keys())  # Print keys of the output dictionary
    # Access the appropriate key based on the actual structure of the output dictionary
    images = output["images"]  # Adjust this line based on the actual structure of the output
    # Select the first image from the list of images
    #image = images[0]
    return images

# Define language options and initialize dictionaries and translator
dictionary = MultiDictionary()
translator = Translator()

# Define variables to store language code and entered word
code = None
word = None

def extract_language_code(option):
    lang = {'english': 'en', 'german': 'de', 'french': 'fr', 'spanish': 'es', 'italian': 'it', 'polish': 'pl', 'turkish': 'tr'}
    option = option.lower()

    while option not in lang:
        option = input("Choose a supported language: ").lower()

    code = lang[option]
    return code

# Function to fetch pronunciations from Forvo API
def get_pronunciations(word, language='en', sex='m', limit=1, group_in_languages=None):
    url = 'https://apifree.forvo.com/key/09a059a0f3086d3ab04454f0dc199531/format/json/action/word-pronunciations/word/'
    params = {
        'word': word,
        'language': language,
        'sex': sex,
        'limit': limit,
        'group-in-languages': group_in_languages
    }
    response = requests.get(url + word + '/language/' + language + '/sex/' + str(sex) + '/limit/1/')
    if response.status_code == 200:
        return response.json()
    else:
        print("Error occurred:", response.text)
        return None

# Function to find singular form of a word
def find_singular(word, language='en'):
    p = inflect.engine()
    return p.singular_noun(word) or word

# Function to translate and identify singular form of a word
def translate_and_identify_singular(word, src_lang='fr', dest_lang='en'):
    if (src_lang == 'en'):
        return find_singular(word)
    translation = translator.translate(word, src=src_lang, dest=dest_lang)
    translated_word = translation.text
    singular_word = find_singular(translated_word)
    translation = translator.translate(singular_word, src=dest_lang, dest=src_lang)
    word = translation.text
    return word

# Function to translate a word to English and return its text
def text_to_image(word, code):
    translation = translator.translate(word, src=code, dest='en')
    return translation.text

# T_K Function
def t_k(word, language):
    language_code = extract_language_code(language)
    
    # Get pronunciations
    pronunciations = get_pronunciations(word, language=language_code)
    pronunciation_link = ""  # Initialize pronunciation link
    if pronunciations:
        # Store the last pronunciation link
        pronunciation_link = pronunciations['items'][-1].get('pathmp3', '')
        audio_path = os.path.join('audio', f"{word}+{language}.mp3")
        urlretrieve(pronunciation_link, audio_path)
    else:
        audio_path = ""

    # Check if the word exists in the dictionary
    meaning = dictionary.meaning(language_code, word)
    if not meaning[0]:  # If word not found
        word = translate_and_identify_singular(word, src_lang=language_code)
        meaning = dictionary.meaning(language_code, word)

    # Get text input for generating images
    text_input = meaning[1]
    
    # Generate and save image
    generated_images = generate(text_input)
    image = generated_images[0]
    image_path = os.path.join('img', f"{word}+{language}.png")
    image.save(image_path)
    
    return meaning, audio_path, image_path
