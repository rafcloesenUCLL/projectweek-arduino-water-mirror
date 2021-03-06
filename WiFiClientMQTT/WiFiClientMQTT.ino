#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Watson IoT connection details
/* https://cfbru8.internetofthings.ibmcloud.com/dashboard/ */
/* # Node red dashboard: */
/* https://ucll-team1.eu-gb.mybluemix.net/ui/#!/0 */
/* Organization ID: cfbru8
 */
/* Device Type: ESP32
 */
/* Device ID: arduino
 */
/* Authentication Method: use-token-auth
 */
/* Authentication Token: oQx@oa5jVACX35lwF& */

#define MQTT_HOST "cfbru8.messaging.internetofthings.ibmcloud.com"
#define MQTT_PORT 1883
#define MQTT_DEVICEID "d:cfbru8:ESP32:arduino"
#define MQTT_USER "use-token-auth"
#define MQTT_TOKEN "oQx@oa5jVACX35lwF&"
#define MQTT_TOPIC "iot-2/evt/status/fmt/json"
#define MQTT_TOPIC_DISPLAY "iot-2/cmd/phmessage/fmt/json"

// Update these with values suitable for your network.

const char* ssid = "ucll-projectweek-IoT";
const char* password = "Foo4aiHa";
const char* mqtt_server = MQTT_HOST;

#define VALVEPIN 16
int product_release = 1;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  Serial.begin(115200);

  // setup for phmeter
  pinMode(21, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(VALVEPIN, OUTPUT);


  distance_setup();

  setup_wifi();
  client.setServer(mqtt_server, MQTT_PORT);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("Message arrived [");
  //Serial.print(topic);
  //Serial.print("] ");
  String input = "";
  for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    input+=(char)payload[i];
  }
  Serial.println();

  StaticJsonDocument<200> doc;

  DeserializationError error = deserializeJson(doc, input);

  const int valve = doc["d"]["valve"];
  
  Serial.println("Valve: ");
  Serial.print(valve);

  if ((valve == 1 || valve == 2) && product_release > 0) {
    Serial.println("OPENING VALVE 1 or 2");
    //digitalWrite(21, HIGH);
    //delay(1000);            // waits for a second
    //digitalWrite(21, LOW);  // sets the digital pin 13 off

    // open valve
    digitalWrite(VALVEPIN, HIGH);
    delay(5000);
    digitalWrite(VALVEPIN, LOW);

    product_release = -20;
  }
  /* if (valve == 2) { */
  /*   //Serial.println("OPENING VALVE 2"); */
  /*   digitalWrite(18, HIGH); */
  /*   delay(1000); */
  /*   digitalWrite(18, LOW); */
  /* } */
  /* Serial.println(); */
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_DEVICEID, MQTT_USER, MQTT_TOKEN)) {
      Serial.println("connected");
      client.subscribe(MQTT_TOPIC_DISPLAY);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(2000);
    }
  }
}

//float read_product(int product_id)
//{
//	if(product_id == 1) return 0.1;
//	else return 0.9;
//}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

    if(product_release < 1)
    	product_release++; 

    double ph1 = read_ph();
    double product1 = read_product_percentage(0);
    //double product2 = read_product_percentage(1);

//    double ph1 = 10;
//    double product1 = 0.1;
//    double product2 = 0.9;

    String payload = "{ \"d\" : {";

    payload += "\"ph\":";
    payload += String(ph1);

    payload += ",";

    payload += "\"product1\":";
    payload += String(product1);

    payload += ",";

//    payload += "\"product2\":";
//    payload += String(product2);
//
//    payload += ",";

    payload += "\"ip\":\"";
    payload += WiFi.localIP().toString();
    payload += "\"";

    payload += "}}";
    Serial.println(payload);

    if (client.publish(MQTT_TOPIC, (char*) payload.c_str())) {
      Serial.println("Publish ok");
    } else {
      Serial.println("Publish failed");
    }
    
    delay(2000);
}
