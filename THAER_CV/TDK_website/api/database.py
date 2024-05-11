# database.py
from sqlalchemy import create_engine, Column, Integer, String, Text
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker

# Read connection details from .info.txt file
info_file = 'path/to/.info.txt'  # Adjust the path as needed
with open(info_file) as f:
    lines = f.readlines()

# Parse connection details
hostname = ''
username = ''
password = ''
database = ''

for line in lines:
    key, value = line.strip().split('=')
    if key == 'hostname':
        hostname = value
    elif key == 'username':
        username = value
    elif key == 'password':
        password = value
    elif key == 'database':
        database = value

# Create SQLAlchemy engine
engine = create_engine(f'mysql://{username}:{password}@{hostname}/{database}')
Base = declarative_base()

# Define the ORM model for the words_table
class Word(Base):
    __tablename__ = 'words_table'

    word_ID = Column(Integer, primary_key=True)
    word = Column(String(255), nullable=False)
    language = Column(String(255), nullable=False)
    description = Column(Text)
    audio = Column(String(255))
    image = Column(String(255))  # Changed to store image path as string

# Create session maker
Session = sessionmaker(bind=engine)

def save_to_database(word, language, description, audio_link, image_path):
    # Create a new database session
    session = Session()

    # Create a new Word object
    new_word = Word(
        word=word,
        language=language,
        description=description,
        audio=audio_link,
        image=image_path  # Store image path
    )

    # Add the new_word to the session and commit changes
    session.add(new_word)
    session.commit()

    # Close the session
    session.close()

def search_word_in_database(word, language):
    # Create a new database session
    session = Session()

    # Query the database for the word
    word_data = session.query(Word).filter_by(word=word, language=language).first()

    # Close the session
    session.close()

    if word_data:
        # Return word data as dictionary
        return {
            'word': word_data.word,
            'language': word_data.language,
            'description': word_data.description,
            'audio': word_data.audio,
            'image': word_data.image
        }
    else:
        return None
