#define MLa 8
#define MLb 9
#define MRa 10
#define MRb 11
#define L_sensor 3
#define R_sensor 4 

byte receivedData;

void setup() {
  pinMode(MLa, OUTPUT);
  pinMode(MLb, OUTPUT);
  pinMode(MRa, OUTPUT);
  pinMode(MRb, OUTPUT);
  pinMode(L_sensor, INPUT);
  pinMode(R_sensor, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    receivedData = Serial.read();
    // 76 -> Line Follower 77 -> Manual Control
    if (receivedData == 76) {
      Serial.println("Changed to Line Follower mode!");
      followLine();
    } else if (receivedData == 77) {
      Serial.println("Changed to manual control mode!");
      manualControl();
    }
  }
  delay(200);
}

void followLine() {
  while (true) {
    if (Serial.available() > 0) {
      receivedData = Serial.read();
      if (receivedData == 77) {
        stopBuggy();
        break;
      }
    }
    if ((digitalRead(L_sensor) == LOW) && (digitalRead(R_sensor) == LOW)) {
    Serial.println("Left and Right sensors are detecting");
    forward();
    }
    else if ((digitalRead(L_sensor) == LOW) && (digitalRead(R_sensor) == HIGH)) {
//      digitalWrite(MLa, HIGH);
//      digitalWrite(MLb, LOW);
//      digitalWrite(MRa, LOW);
//      digitalWrite(MRb, LOW);
    }
    else if ((digitalRead(L_sensor) == HIGH) && (digitalRead(R_sensor) == LOW)) {
      Serial.println("Left not detecting");
      Serial.println("Right detecting");
//      digitalWrite(MLa, LOW);
//      digitalWrite(MLb, LOW);
//      digitalWrite(MRa, HIGH);
//      digitalWrite(MRb, LOW);
    }
    else {
      stopBuggy();
      delay(500);
    }
  }
}

void manualControl() {
  while (true) {
      if (Serial.available() > 0) {
      receivedData = Serial.read();
      if (receivedData == 48) {
        forward();
        delay(500);
      } else if (receivedData == 49) {
        backward();
        delay(500);
      } else if (receivedData == 50) {
        left();
        delay(500);
      } else if (receivedData == 51) {
        right();
        delay(500);
      } else if (receivedData == 52) {
        stopBuggy();
      } else if (receivedData == 76) {
        stopBuggy();
        delay(500);
        break;
      }
      delay(200);
    }
  }
}

void forward() {
  Serial.println("Buggy is moving in forward direction!");
  digitalWrite(MLa, HIGH);
  digitalWrite(MLb, LOW);
  digitalWrite(MRa, HIGH);
  digitalWrite(MRb, LOW);
}

void backward() {
  Serial.println("Buggy is moving in reverse direction!");
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, HIGH);
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, HIGH);
}

void left() {
  Serial.println("Buggy is turning in left direction!");
  digitalWrite(MLa, HIGH);
  digitalWrite(MLb, LOW);
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, HIGH);
}

void right() {
  Serial.println("Buggy is turning in right direction!");
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, HIGH);
  digitalWrite(MRa, HIGH);
  digitalWrite(MRb, LOW);
}

void stopBuggy() {
  Serial.println("Buggy is stopped!");
  digitalWrite(MLa, LOW);
  digitalWrite(MLb, LOW);
  digitalWrite(MRa, LOW);
  digitalWrite(MRb, LOW);
}
