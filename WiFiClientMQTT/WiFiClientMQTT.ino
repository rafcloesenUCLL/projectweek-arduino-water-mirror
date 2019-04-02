/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

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
#define MQTT_TOPIC_DISPLAY "iot-2/cmd/update/fmt/json"

// Update these with values suitable for your network.

const char* ssid = "ucll-projectweek-IoT";
const char* password = "Foo4aiHa";
const char* mqtt_server = MQTT_HOST;
const int button = 0;
int buttonState = 0;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  Serial.begin(115200);
  pinMode(21, OUTPUT);
  pinMode(18, OUTPUT);
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
  
  //Serial.println("Valve: ");
  //Serial.print(valve);

  if (valve == 1) {
    //Serial.println("OPENING VALVE 1");
    digitalWrite(21, HIGH);
    delay(1000);            // waits for a second
    digitalWrite(21, LOW);  // sets the digital pin 13 off
  }
  if (valve == 2) {
    //Serial.println("OPENING VALVE 2");
    digitalWrite(18, HIGH);
    delay(1000);
    digitalWrite(18, LOW);
  }
  Serial.println();
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

int i = 0;
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

    i++;
    
    String payload = "{ \"d\" : {";
    payload += "\"ph-sensor-1\":";
    String buf = String(i);
    payload += buf; 
    payload += ",";
    payload += "\"Local IP\":\""; payload += WiFi.localIP().toString(); payload += "\"";
    payload += "}}";
    Serial.println(payload);

    if (client.publish(MQTT_TOPIC, (char*) payload.c_str())) {
      Serial.println("Publish ok");
    } else {
      Serial.println("Publish failed");
    }
    
    delay(2000);

    if(i == 14)
    {
      i = 0;
    }

  /* buttonState = digitalRead(button); */ 
  /* if (buttonState == HIGH) { */
  /*   delay(500); */
  /* } */
  /* else { */
  /*  } */
}
