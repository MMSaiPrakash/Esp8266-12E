#include <DHT.h> 
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>
#include <ThingSpeak.h>
#define DHTPIN D5  
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);  
const char* ssid = "MM";  
const char* password = "nopassword";  
WiFiClient client;  
unsigned long ChannelNumber = 974145;  
const char * WriteAPIKey = "WNTI5PLFI5DEAI2G";  
uint8_t temperature, humidity;
void setup(){  
  Serial.begin(115200);  
  dht.begin();  
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
}  
void loop(){  
  static boolean data_state = false;  
  temperature = dht.readTemperature();  
  humidity = dht.readHumidity();  
  Serial.print("Temperature=");  
  Serial.print(temperature);  
  Serial.println("C");  
  Serial.print("Humidity=");  
  Serial.print(humidity);
  Serial.println("%");  
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different  
  // pieces of information in a channel.  
  if( data_state ){  
   ThingSpeak.writeField(ChannelNumber, 1, temperature, WriteAPIKey);  
   data_state = false;  
  }  
  else  
  {  
   ThingSpeak.writeField(ChannelNumber, 2, humidity, WriteAPIKey);  
   data_state = true;  
  }  
  delay(5000); // ThingSpeak will only accept updates every 15 seconds.  
}
