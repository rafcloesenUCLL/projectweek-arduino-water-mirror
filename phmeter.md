# Gebruik van de PH-meter

### Introductie
Deze manual beschrijft de werking van een ph-meter, en hoe de aansluiting aan een arduino moet gebeuren.

### Werking
Een ph-meter meet de zuurtegraad van een vloeistof. Aan het uiteinde van de ph-meter wordt het electrische potentieelverschil gemeten tussen twee glazen electroden. Door de speciale structuur van een ph-meter is dit verschil recht evenredig met de ph van de vloeistof. De exacte details van de werking zijn een bedrijfsgeheim van de makers. 
Eén van de aansluitingen van de ph-meter geeft een waarde door die recht evenredig is met de ph. Deze kan worden ingelezen en worden omgezet naar de ph.

### Gebruik
Om een ph te meten moet het uiteinde van de meter in de vloeistof gestoken worden. Beweeg de ph-meter rustig doorheen de vloeistof, tot de meting gestabiliseerd is. 
De electroden van de ph-meter mogen niet uitdrogen. Op het uiteinde van de meter is een kleine container om het uiteinde altijd vochtig te houden als de meter niet gebruikt wordt. Dit zou gevuld moeten zijn met een buffervloeistof. De meter moet uiteraard uit de container worden gehaald om metingen te doen.
Spoel de meter na elke meting af. Dat gebeurt best met gedeïoniseerd water.

### Aansluiting
De ph-meter bestaat uit twee onderdelen: de feitelijke ph-meter, die met een kabel bevestigd kan worden aan een printplaatje. Deze printplaat heeft drie gekleurde aansluitingen voor drie jumper kabels. Sluit de rode kabel aan op een pin van 5 volt, de zwarte op de aarding en de gele op pin 34 van de Arduino.

### Code om het gelezen potentieelverschil te printen

Onderstaande code print het ingelezen voltage op het scherm. Dit hebben we nodig voor de eiking (zie hieronder). Het voltage wordt * 5 / 1024 gedaan; dit is nodig om de analogRead om te zetten naar de nodige waarde.

```
#define In 34

#define ArrayLenth  40 
int pHArray[ArrayLenth];
int pHArrayIndex=0; 

void setup() {  
  Serial.begin(115200);
  Serial.print("ph meter start");
}

void loop() {
    static double pHValue,voltage;
  
    pHArray[pHArrayIndex++]=analogRead(In);
    if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
    voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      
    Serial.print("Voltage:");
    Serial.print(voltage,2);
}

```

De ph-meter is niet erg accuraat, en geeft vaak foute waarden. Daarom nemen we frequent metingen om daar het lopende gemiddelde van te berekenen. Onderstaande code berekend dat gemiddelde. 

```
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
```

### Eiken van de ph-meter

Het voltage dat we momenteel krijgen, moet echter nog worden omgezet naar de ph. Daarom gaan we de ph-meter eiken. Dit betekend dat we twee vloeistoffen met een gekende ph gaan meten, om  de vergelijking op te stellen die we nodig hebben.  
Neem twee producten (bv. Frisdrank, drinkwater), zoek de ph ervan op, en neem een meting.
Stel de vergelijking op die door de twee punten van de meting gaat (of gebruik wolfram alpha). We maken een methode die de vergelijking gebruikt om de ph te berekenen. Onderstaande vergelijking zal waarschijnlijk niet juist zijn voor uw ph-meter.

```
double convertVoltageToPh(double volt) {
  double ph = 0.00557 * volt - 1.672;
  return ph;
}
```

### Code om de ph te printen

Wijzig de loop functie naar 
```
  static double pHValue,voltage;
  
  pHArray[pHArrayIndex++]=analogRead(In);
  if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
  voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
  pHValue = convertVoltageToPh(voltage);
      
  Serial.print("Voltage:");
  Serial.print(voltage,2);
  Serial.print("pH value: ");
  Serial.println(pHValue,2);
```

Test nu opnieuw de vloeistoffen. De juiste ph zou nu geprint moeten worden.




### Gebruik in het zwembadproject

Om deze code te gebruiken, moet de loopfunctie wijzigen. Deze functie moet opgeroepen worden vanuit de main loopfunctie, en de ph teruggeven. 

```
double read_ph() {  
  static double pHValue,voltage;
  
  pHArray[pHArrayIndex++]=analogRead(In);
  if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
  voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
  pHValue = convertVoltageToPh(voltage);
  
  return pHValue;  
}
```





















