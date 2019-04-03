const unsigned int TRIG_PIN1=13;
const unsigned int ECHO_PIN1=12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIG_PIN1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN1, LOW);

  const unsigned long duration= pulseIn(ECHO_PIN1, HIGH);
  int distance= duration/29/2;

  Serial.println(distance);
}
