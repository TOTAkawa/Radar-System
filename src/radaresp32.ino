
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// HC-SR04
const int TRIG_PIN = 18;
const int ECHO_PIN = 5;

// Motor de passo (28BYJ-48) com ULN2003
const int IN1 = 25;
const int IN2 = 26;
const int IN3 = 27;
const int IN4 = 33;

// Sequência de meia etapa para suavidade
const int HALFSTEP_SEQ[8][4] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};

int angle = 0;
int dir = 1; // 1 indo para 180°, -1 voltando para 0°
const int STEPS_PER_REV = 2048; // passos por volta completa
const float STEPS_PER_DEG = STEPS_PER_REV / 360.0;

void setCoils(int a, int b, int c, int d) {
  digitalWrite(IN1, a);
  digitalWrite(IN2, b);
  digitalWrite(IN3, c);
  digitalWrite(IN4, d);
}

void halfStepOnce(int stepIndex) {
  setCoils(HALFSTEP_SEQ[stepIndex][0],
           HALFSTEP_SEQ[stepIndex][1],
           HALFSTEP_SEQ[stepIndex][2],
           HALFSTEP_SEQ[stepIndex][3]);
  delay(3); // ajuste da velocidade
}

void stepDegrees(float deg, bool forward) {
  int totalHalfSteps = (int)(deg * STEPS_PER_DEG * 2.0);
  static int seqIdx = 0;
  for (int i = 0; i < totalHalfSteps; i++) {
    seqIdx = forward ? (seqIdx + 1) % 8 : (seqIdx - 1 + 8) % 8;
    halfStepOnce(seqIdx);
  }
}

float measureDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);
  if (duration == 0) return NAN;
  return (duration / 2.0) / 29.1;
}

void showOnLCD(int ang, float dist) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ang: ");
  lcd.print(ang);
  lcd.print((char)223); // símbolo de grau
  lcd.setCursor(0, 1);
  lcd.print("Dist: ");
  if (isnan(dist)) {
    lcd.print("---");
  } else {
    lcd.print(dist, 1);
    lcd.print(" cm");
  }
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Radar ULN2003");
  delay(1000);
  lcd.clear();
}

void loop() {
  float d = measureDistanceCM();
  showOnLCD(angle, d);
  delay(80);

  angle += dir;
  if (angle >= 180) { angle = 180; dir = -1; }
  if (angle <= 0)   { angle = 0;   dir = 1; }

  stepDegrees(1.0, dir == 1);
}
