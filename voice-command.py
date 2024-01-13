import speech_recognition as sr
import serial
import time

# Setup the serial connection
try:
    arduino = serial.Serial('COM5', 9600)  # Replace 'COM5' with your actual COM port
    time.sleep(2)  # Wait for the connection to be established
except serial.SerialException:
    print("Failed to connect to Arduino. Check your COM port.")
    exit(1)

def listen_for_commands():
    recognizer = sr.Recognizer()
    with sr.Microphone() as source:
        print("Listening for command...")
        audio_data = recognizer.listen(source)
        try:
            command = recognizer.recognize_google(audio_data).lower()
            print("You said: " + command)
            return command
        except sr.UnknownValueError:
            print("Sorry, I did not understand that.")
        except sr.RequestError:
            print("Sorry, my speech service is down.")

def process_command(command):
    if 'wave' in command:
        try:
            arduino.write(b'wave\n')  # Sending the wave command
            print("Sent wave command to Arduino")
        except:
            print("Failed to send command to Arduino")


while True:
    command = listen_for_commands()
    if command:
        process_command(command)
