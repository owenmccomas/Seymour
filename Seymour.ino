#include <xArmServoController.h>

#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
xArmServoController xarm(xArm, mySerial);



void setup() {
  mySerial.begin(9600);
  // Initialize other settings, like the hardware serial for debugging
  Serial.begin(9600);
  Serial.println("SoftwareSerial Test Started");
}


void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n'); // Read the command
    command.trim(); // Remove any whitespace

    if (command == "wave") {
      waveGesture(); // Execute the wave gesture
      Serial.println("Executing wave gesture");
    }
  }
}




void waveGesture() {
  // Define the start positions for each servo in the wave gesture
  xArmServo startPositions[] = {
    {1, 500},
    {2, 500},
    {3, 500},
    {4, 500},
    {5, 500},
    {6, 500}
  };

  // Move servos to start positions
  xarm.setPosition(startPositions, 6, 1000, true);

  // Define the waving positions for each servo
  xArmServo wavePositions[] = {
    {1, 500},
    {2, 700}, // Lift arm
    {3, 300}, // Move arm forward
    {4, 700}, // Adjust for waving
    {5, 500},
    {6, 500}
  };

  // Perform the wave gesture
  for (int i = 0; i < 3; i++) { // Repeat waving motion 3 times
    xarm.setPosition(wavePositions, 6, 500, true);
    xarm.setPosition(startPositions, 6, 500, true);
  }
}
