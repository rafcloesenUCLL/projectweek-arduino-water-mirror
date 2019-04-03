
#define In 34

#define Offset 0.00            //deviation compensate
#define LED 13
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0; 

double read_ph() {  
  //Serial.print(analogRead(In));

  static double pHValue,voltage;
  //Serial.println(analogRead(In));
  
      pHArray[pHArrayIndex++]=analogRead(In);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = convertVoltageToPh(voltage);
      
 
    Serial.print("Voltage:");
    Serial.print(voltage,2);
    Serial.print("pH value: ");
    Serial.println(pHValue,2);

    return pHValue;
    
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
