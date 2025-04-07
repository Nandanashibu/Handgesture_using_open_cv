#include <Servo.h>

#define numOfValsRec 5  // Number of values to receive (one for each finger)
#define digitsPerValRec 1  // Number of digits per value

Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;

int valsRec[numOfValsRec];  // Array to store received values
int stringLength = numOfValsRec * digitsPerValRec + 1;  // Length of the received string
int counter = 0;  // Counter for received characters
bool counterStart = false;  // Flag to indicate the start of data
String receivedString;  // String to store incoming data

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 baud rate

  // Attach servos to their respective pins
  servoThumb.attach(7);
  servoIndex.attach(9);
  servoMiddle.attach(11);
  servoRing.attach(8);
  servoPinky.attach(10);

  // Initialize servos to their default positions
  servoThumb.write(0);
  servoIndex.write(0);
  servoMiddle.write(0);
  servoRing.write(0);
  servoPinky.write(0);
}

void receiveData() {
  while (Serial.available()) {
    char c = Serial.read();  // Read the incoming character

    if (c == '$') {  // Start of data
      counterStart = true;
    }

    if (counterStart) {
      if (counter < stringLength) {  // Collect data until the string is complete
        receivedString = String(receivedString + c);
        counter++;
      }

      if (counter >= stringLength) {  // Process the received string
        for (int i = 0; i < numOfValsRec; i++) {
          int num = (i * digitsPerValRec) + 1;  // Extract each value from the string
          valsRec[i] = receivedString.substring(num, num + digitsPerValRec).toInt();
        }

        // Reset for the next data packet
        receivedString = "";
        counter = 0;
        counterStart = false;
      }
    }
  }
}

void loop() {
  receiveData();  // Receive data from the serial port

  // Print the received values for debugging
  Serial.print("Values: ");
  for (int i = 0; i < numOfValsRec; i++) {
    Serial.print(valsRec[i]);
    Serial.print(" ");
  }
  Serial.println();

  // Control servos based on received values
  if (valsRec[0] == 0) {  // Thumb fully down
    servoThumb.write(0);
  } else if (valsRec[0] == 1) {  // Thumb half bent
    servoThumb.write(90);
  } else if (valsRec[0] == 2) {  // Thumb fully up
    servoThumb.write(180);
  }

  if (valsRec[1] == 0) {  // Index fully down
    servoIndex.write(0);
  } else if (valsRec[1] == 1) {  // Index half bent
    servoIndex.write(90);
  } else if (valsRec[1] == 2) {  // Index fully up
    servoIndex.write(180);
  }

  if (valsRec[2] == 0) {  // Middle fully down
    servoMiddle.write(0);
  } else if (valsRec[2] == 1) {  // Middle half bent
    servoMiddle.write(90);
  } else if (valsRec[2] == 2) {  // Middle fully up
    servoMiddle.write(180);
  }

  if (valsRec[3] == 0) {  // Ring fully down
    servoRing.write(0);
  } else if (valsRec[3] == 1) {  // Ring half bent
    servoRing.write(90);
  } else if (valsRec[3] == 2) {  // Ring fully up
    servoRing.write(180);
  }

  if (valsRec[4] == 0) {  // Pinky fully down
    servoPinky.write(0);
  } else if (valsRec[4] == 1) {  // Pinky half bent
    servoPinky.write(90);
  } else if (valsRec[4] == 2) {  // Pinky fully up
    servoPinky.write(180);
  }
}
