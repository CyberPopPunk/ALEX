/*
    THIS FILE CONTAINS ALL OF THE FUNCTIONS FOR THE BEHAVIOR OF ALEX.
    There are some building block functions like "lookStraight" or "turnLeft"
    and more complex behaviors are built by sequencing these basic functions.

*/


void manualPan(int degree){
  pan.startEaseTo(degree);
}

void manualTilt(int degree){
  tilt.startEaseTo(degree);
}

void panCenter() {
  pan.easeTo((panMax / 2) + 10);
}

void tiltCenter() {
  tilt.easeTo((2 * tiltMax / 3) + 10);
}

void turnLeft() {
  Serial.println("panning left!");
  pan.startEaseTo(panMin);
}

void turnRight() {
  Serial.println("panning right!");
  pan.startEaseTo(panMax);
}

void headBack(int moveSpeed) {
  int prevTiltSpeed = tilt.getSpeed();
  tilt.setSpeed(moveSpeed);
  Serial.println("head back!");
  tilt.startEaseTo(tiltMin);
  tilt.setSpeed(prevTiltSpeed);
}

void lookDown() {
  Serial.println("look down!");
  tilt.startEaseTo(tiltMax);
}

void shakeHead() {
  Serial.println("Shakes head");
  tilt.startEaseTo((tiltMax + tiltMin) / 2);
  pan.startEaseTo(panMin);
  for (int i = 0; i < 3; i++) {
    pan.easeTo(panMax * 2 / 3);
    pan.easeTo(panMax / 3);
  }
}

void sadFace() {
  lookDown();
  turnRight();
}

void lookStraight() {
  panCenter();
  tiltCenter();
}

void nod(int nodSpeed) {
  int prevTiltSpeed = tilt.getSpeed();
  lookStraight();
  tilt.setSpeed(nodSpeed);
  for (int i = 0; i < 3; i++) {
    tilt.easeTo(tiltMax / 2);
    tilt.easeTo(tiltMin * 2);
  }
  tilt.setSpeed(prevTiltSpeed);
}

void eat(int startDegree, int stopDegree, int wiggleSpeed) {
  tilt.easeTo(startDegree);
  for (int i = 0; i < 3; i++) {
    tilt.easeTo(stopDegree);
    delay(200);
    tilt.easeTo(startDegree);
    delay(200);
  }
}

void bow() {
  lookStraight();
  tilt.easeTo(tiltMax, 20);
}

void scared(){
  for (int i = 0; i < 4; i++){
    for (int i = 0; i < 8; i++){
      increaseSpeed();
    }
    shakeHead();
    for (int i =0; i < 7; i++){
      decreaseSpeed();
    }
  }
}

void increaseSpeed(){
  int currPanSpeed = pan.getSpeed();
  int currTiltSpeed = tilt.getSpeed();

  pan.setSpeed(currPanSpeed*1.1);
  tilt.setSpeed(currTiltSpeed*1.1);
}

void decreaseSpeed(){
  int currPanSpeed = pan.getSpeed();
  int currTiltSpeed = tilt.getSpeed();

  pan.setSpeed(currPanSpeed*.9);
  tilt.setSpeed(currTiltSpeed*.9);
}