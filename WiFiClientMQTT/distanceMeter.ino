const unsigned int TRIG_PIN1 = 13;
const unsigned int ECHO_PIN1 = 12;
const unsigned int TRIG_PIN2 = 27;
const unsigned int ECHO_PIN2 = 26;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);
  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIG_PIN1, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN1, LOW);

  const unsigned long duration1= pulseIn(ECHO_PIN1, HIGH);
  double distance1 = duration1/29/2;


  digitalWrite(TRIG_PIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);



  const unsigned long duration2= pulseIn(ECHO_PIN2, HIGH);
  double distance2 = duration2/29/2;

  Serial.print("distance 1: ");
  Serial.print(distance1);
  Serial.print(" - distance 2: ");
  Serial.println(distance2);
}
