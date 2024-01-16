import openai
from dotenv import load_dotenv
import os

load_dotenv()

api_key = os.getenv('OPENAI_API_KEY')

client = openai.OpenAI(api_key=api_key)

speech_file_path = 'speech.mp3'

response = client.audio.speech.create(
    model='tts-1',
    voice='echo',
    input="Hi Everyone this is Seymour's test"
)
response.stream_to_file(speech_file_path)
