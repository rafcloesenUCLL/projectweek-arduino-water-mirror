int measurements, counter;

#define In 34

#define Offset 0.00            //deviation compensate
#define LED 13
#define samplingInterval 20
#define testInterval 2000
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0; 


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200); //?
  Serial.print("ph meter start");
  pinMode(21, OUTPUT);
  pinMode(18, OUTPUT);
}

void loop() {
  
  //Serial.print(analogRead(In));

  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,voltage;
  //Serial.println(analogRead(In));
  
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(In);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = convertVoltageToPh(analogRead(In));//3.5*voltage+Offset;
      samplingTime=millis();
  }
  if(millis() - printTime > testInterval)   //Every 1000 milliseconds, interpret the ph
  {
    /*if (pHValue > 7.6) {
    Serial.println("verlaag");
    digitalWrite(21, HIGH);
    delay(1000);            // waits for a second
    digitalWrite(21, LOW);  // sets the digital pin 13 off
    delay(1000);
  } else if (pHValue < 7.2) {
    Serial.println("verhoog");
    digitalWrite(21, HIGH);
    delay(1000);
    digitalWrite(21, LOW); 
    delay(1000);
  }*/
    
    adjustPhLevel(pHValue);
    Serial.print("Voltage:");
    Serial.print(voltage,2);
    Serial.print(", pH value: ");
    Serial.println(pHValue,2);
    printTime=millis();
  }
}

void adjustPhLevel(double ph) {
  if (ph > 7.6) {
    lowerPh();
  } else if (ph < 7.2) {
    raisePh();
  }
}

void lowerPh() {
  Serial.println("verlaag");
  digitalWrite(21, HIGH);
  delay(500);            // waits for a second
  digitalWrite(21, LOW);  // sets the digital pin 13 off
  delay(500);
}

void raisePh() {
  Serial.println("verhoog");
  digitalWrite(18, HIGH);
  delay(500);            // waits for a second
  digitalWrite(18, LOW);  // sets the digital pin 13 off
  delay(500);
}

double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}


double convertVoltageToPh(double volt) {
  double ph = 0.00557 * volt - 1.672;
  return ph;
}
