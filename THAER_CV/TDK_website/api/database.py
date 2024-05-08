# database.py

from sqlalchemy import create_engine, Column, Integer, String, Text
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker

# Create SQLAlchemy engine
engine = create_engine('mysql://root:@localhost/userform')
Base = declarative_base()

# Define the ORM model for the words_table
class Word(Base):
    __tablename__ = 'words_table'

    word_ID = Column(Integer, primary_key=True)
    word = Column(String(255), nullable=False)
    language = Column(String(255), nullable=False)
    description = Column(Text)
    audio = Column(String(255))
    image = Column(Text)

# Create session maker
Session = sessionmaker(bind=engine)

def save_to_database(word, language, description, audio_link, image_file):
    # Create a new database session
    session = Session()

    # Create a new Word object
    new_word = Word(
        word=word,
        language=language,
        description=description,
        audio=audio_link,
        image=image_file
    )

    # Add the new_word to the session and commit changes
    session.add(new_word)
    session.commit()

    # Close the session
    session.close()
