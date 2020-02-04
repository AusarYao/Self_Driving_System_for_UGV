#define motor0Pow 9
#define motor1Pow 10
#define motor2Pow 5
#define motor3Pow 6
#define motor00 2
#define motor01 3
#define motor10 4
#define motor11 7
#define motor20 8
#define motor21 11
#define motor30 12
#define motor31 14
#define startMarker 128
#define motorInstruction 0
#define motorParamCount 3
#define bufferSize 64
#define dcMortorNum 4

typedef struct DCMotorInfo {
  int pin1;
  int pin2;
  int powCtrl;
  int power;
} DCMotorInfo;

byte commBuffer[bufferSize];
int messageLength = 0,
    commBufferIdx = 0;
DCMotorInfo dcMotors[dcMortorNum];
boolean commComplete = false,
        commInProgress = false,
        commLenReveived = false;

void setup() {
  Serial.begin(57600);
  Serial.print("Arduino is ready\n");
  dcMotorInitialize();
}

void loop() {
  recvInstructionsBytes();
  parseMessage();
}

//Initialize all DC motors
void dcMotorInitialize() {
  dcMotors[0] = {.pin1 = motor00, .pin2 = motor01, .powCtrl = motor0Pow, .power = 0};
  dcMotors[1] = {.pin1 = motor10, .pin2 = motor11, .powCtrl = motor1Pow, .power = 0};
  dcMotors[2] = {.pin1 = motor20, .pin2 = motor21, .powCtrl = motor2Pow, .power = 0};
  dcMotors[3] = {.pin1 = motor30, .pin2 = motor31, .powCtrl = motor3Pow, .power = 0};
  for (int i = 0; i < dcMortorNum; i++) { //Setting up pins to control motor
    pinMode(dcMotors[i].pin1, OUTPUT);
    pinMode(dcMotors[i].pin2, OUTPUT);
    pinMode(dcMotors[i].powCtrl, OUTPUT);
    digitalWrite(dcMotors[i].pin1, HIGH);
    digitalWrite(dcMotors[i].pin2, LOW);
    analogWrite(dcMotors[i].powCtrl, 255);//dcMotors[i].power);
  }
}

//receive one byte each cycle
void recvInstructionsBytes() {
  int rb;
  //  Serial.println("Before Receiving message");  //Debug
  if (Serial.available() > 0) {
    rb = Serial.read();

    if (rb == startMarker && !commInProgress) { //check comm start mark
      commInProgress = true;
    } else if (!commLenReveived && commInProgress) { //get message length
      messageLength = rb;
      commLenReveived = true;
    } else if (commLenReveived && commInProgress) { //receive actual message
      commBuffer[commBufferIdx++] = rb;
      if (commBufferIdx == messageLength)
        commComplete = true;
    }
  }
}

//execute instructions after receiving full message
void parseMessage() {
  if (commComplete) {
    commComplete = false;
    commInProgress = false;
    commLenReveived = false;
    //    printCommBuffer();  //debugging
    executeInstructions();
    commBufferIdx = 0;
  }
}

void executeInstructions() {
  int idx = 0;
  while (idx < commBufferIdx) {
    switch (commBuffer[idx]) {
      case motorInstruction:
        dcMotorControl(commBuffer[idx + 1], commBuffer[idx + 2], commBuffer[idx + 3]);
        idx += motorParamCount + 1;
        break;
      default:
        Serial.println("Error: invalid instruction ID");
        printCommBuffer();
        commBufferIdx = 0;
        return;
    }
  }
//  Serial.println("Instructions executed");
}

void dcMotorControl(int motorId, int direction, int power) {
  //  Serial.println("Motor control in progress");  //Debug
  if (motorId < 0 || motorId > dcMortorNum - 1) {
    Serial.println("Error: Invalid DC motor ID");
    return;
  }
  if (power == 0) {
    digitalWrite(dcMotors[motorId].pin1, LOW);
    digitalWrite(dcMotors[motorId].pin2, LOW);
    analogWrite(dcMotors[motorId].powCtrl, power);
    return;
  }
  int pin1State = LOW, pin2State = HIGH;
  if (direction > 0) {
    pin1State = HIGH;
    pin2State = LOW;
  }
  digitalWrite(dcMotors[motorId].pin1, pin1State);
  digitalWrite(dcMotors[motorId].pin2, pin2State);
  analogWrite(dcMotors[motorId].powCtrl, power);
}

void serialFlush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
}

//For debugging
void printCommBuffer() {
  Serial.println(commBufferIdx);
  int idx = 0;
  while (idx < commBufferIdx)
    Serial.println(commBuffer[idx++]);
}
