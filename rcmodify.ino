// Define motor control commands
#define FORWARD 'F'
#define BACKWARD 'B'
#define LEFT 'L'
#define RIGHT 'R'
#define CIRCLE 'C'
#define CROSS 'X'
#define TRIANGLE 'T'
#define SQUARE 'S'
#define START 'A'
#define PAUSE 'P'

// Define motor driver pins
#define MOTOR_A_EN 3 // PWM pin for motor A speed control
#define MOTOR_A_IN1 4 // Motor A control pin 1
#define MOTOR_A_IN2 5 // Motor A control pin 2

#define MOTOR_B_EN 6 // PWM pin for motor B speed control
#define MOTOR_B_IN1 7 // Motor B control pin 1
#define MOTOR_B_IN2 8 // Motor B control pin 2

bool motorsRunning = false;

void setup() {
  Serial.begin(9600);  // Set the baud rate for serial communication
  // Initialize motor control pins as outputs
  pinMode(MOTOR_A_EN, OUTPUT);
  pinMode(MOTOR_A_IN1, OUTPUT);
  pinMode(MOTOR_A_IN2, OUTPUT);
  
  pinMode(MOTOR_B_EN, OUTPUT);
  pinMode(MOTOR_B_IN1, OUTPUT);
  pinMode(MOTOR_B_IN2, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    executeCommand(command);
  }
  // Continue with other tasks in your main loop
}

void executeCommand(char command) {
  switch (command) {
    case FORWARD:
      if(motorsRunning) {
        motorControl(MOTOR_A_EN, MOTOR_A_IN1, MOTOR_A_IN2, 255); // Motor A full speed forward
        motorControl(MOTOR_B_EN, MOTOR_B_IN1, MOTOR_B_IN2, 255); // Motor B full speed forward
      }
      break;
    case BACKWARD:
      if(motorsRunning) {
        motorControl(MOTOR_A_EN, MOTOR_A_IN1, MOTOR_A_IN2, -255); // Motor A full speed backward
        motorControl(MOTOR_B_EN, MOTOR_B_IN1, MOTOR_B_IN2, -255); // Motor B full speed backward
      }
      break;
    case LEFT:
      motorControl(MOTOR_A_EN, MOTOR_A_IN1, MOTOR_A_IN2, 255); // Motor A full speed forward
      motorControl(MOTOR_B_EN, MOTOR_B_IN1, MOTOR_B_IN2, 0); // Stop motor B
      break;
    case RIGHT:
      motorControl(MOTOR_A_EN, MOTOR_A_IN1, MOTOR_A_IN2, 0); // Stop motor A
      motorControl(MOTOR_B_EN, MOTOR_B_IN1, MOTOR_B_IN2, 255); // Motor B full speed forward
      break;
    case CIRCLE:
      motorControl(MOTOR_A_EN, MOTOR_A_IN1, MOTOR_A_IN2, -255); // Motor A full speed backward
      motorControl(MOTOR_B_EN, MOTOR_B_IN1, MOTOR_B_IN2, 255); // Motor B full speed forward// Perform action for circle
      break;
    case CROSS:
      motorControl(MOTOR_A_EN, MOTOR_A_IN1, MOTOR_A_IN2, 255); // Stop motor A
      motorControl(MOTOR_B_EN, MOTOR_B_IN1, MOTOR_B_IN2, 205); // Stop motor B
      break;
    case TRIANGLE:
      motorControl(MOTOR_A_EN, MOTOR_A_IN1, MOTOR_A_IN2, 125); // Stop motor A
      motorControl(MOTOR_B_EN, MOTOR_B_IN1, MOTOR_B_IN2, 255); // Stop motor B
      // Perform action for toggling a state (e.g., LED on/off)
      break;
    case SQUARE:
      motorControl(MOTOR_A_EN, MOTOR_A_IN1, MOTOR_A_IN2, 255); // Motor A full speed backward
      motorControl(MOTOR_B_EN, MOTOR_B_IN1, MOTOR_B_IN2, -255); // Motor B full speed forward// Perform action for circle
    
.      // Perform action for retrieving and sending status information
      break;
    case START:
      motorsRunning = true;
      break;
    case PAUSE:
      motorsRunning = false;
      motorControl(MOTOR_A_EN, MOTOR_A_IN1, MOTOR_A_IN2, 0); // Stop motor A
      motorControl(MOTOR_B_EN, MOTOR_B_IN1, MOTOR_B_IN2, 0); // Stop motor B
      break;
    default:
      // Invalid command received
      break;
  }
}

// Function to control the motor speed and direction
void motorControl(int enPin, int in1Pin, int in2Pin, int speed) {
  // Set the direction of the motor based on the speed
  if (speed > 0) {
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
  } else if (speed < 0) {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
  } else {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
  }
  
  // Set the speed of the motor
  analogWrite(enPin, abs(speed));
}
