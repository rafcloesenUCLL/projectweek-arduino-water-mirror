unsigned int TRIG_PIN[2];
unsigned int ECHO_PIN[2];

double MAX_DISTANCE = 35;

void distance_setup() {
  TRIG_PIN[0] = 13;
ECHO_PIN[0] = 12;
TRIG_PIN[1] = 27;
ECHO_PIN[1] = 26;

  pinMode(TRIG_PIN[0], OUTPUT);
  pinMode(ECHO_PIN[0], INPUT);
  pinMode(TRIG_PIN[1], OUTPUT);
  pinMode(ECHO_PIN[1], INPUT);
}

double read_product_percentage(int sensor_id) {
  if(sensor_id < 0 || sensor_id > 1)
  	return -1;

  digitalWrite(TRIG_PIN[sensor_id], LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN[sensor_id], HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN[sensor_id], LOW);

  const unsigned long duration = pulseIn(ECHO_PIN[sensor_id], HIGH);
  double distance = (double)duration;
  distance = distance/29/2;

  if(distance > MAX_DISTANCE)
  	return -1;

  return distance / MAX_DISTANCE;
}
