#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// include the following  "PubSubClient by Nick O'Leary"  sershe for pusub
//This program will send the status of my Doorbell button to MQTT server 
//My MQTT server will send message to node red witch will send event to my mobile phone by adding a image from my camera looking at the Gate button.
//WIFI
const char* wifi_ssid = "wifi";
const char* wifi_password = "password";

//MQTT
const char* mqtt_server = "192.168.10.114";//"mqtt.giga.co.za";
const char* mqtt_user = "mqtt";
const char* mqtt_password = "password";
const char* clientID = "Doorbell";

//VARS
const char* doorbell_topic = "bassonia/outdoors/doorbell";
const int doorbellPin = 0;
int doorbellState = 0;

WiFiClient espClient;
PubSubClient client(espClient);

//connect D0 via doorbell switch to ground.
void setup() {
  Serial.begin(115200);
  pinMode(doorbellPin, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void blink_now(){
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
}

void setup_wifi() {
  //Turn off Access Point
  WiFi.mode(WIFI_STA);
  delay(10);
  
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    blink_now();
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    blink_now();
    // Attempt to connect
    if (client.connect(clientID, mqtt_user, mqtt_password)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(doorbell_topic, "Doorbell connected to MQTT");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  doorbellState = digitalRead(doorbellPin);

  if ( doorbellState == LOW ) {
    // Put your code here.  e.g. connect, send, disconnect.
    Serial.println("Doorbell is pressed!");
    client.publish(doorbell_topic, "on", true);
    blink_now();

    delay( 5000 );
  }
}
