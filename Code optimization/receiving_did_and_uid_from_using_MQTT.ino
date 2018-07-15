#include <WiFi.h>
#include <PubSubClient.h>

char* ssid="DataSoft_WiFi";
char* password="support123";
const char* mqtt_server = "182.163.112.207";
const int mqttPort = 1883;


WiFiClient espClient;
PubSubClient client(espClient);


//----------------User did & uid spliting variables------------------------------------//

char Data[30];
const int numberOfPieces = 2;
String configData[numberOfPieces];
String did_uid="";
// Keep track of current position in time array
int counter = 0;

// Keep track of the last comma so we know where to start the substring
int lastIndex;

char did[24];
char uid[24];



//---------------Main Set up-----------------------------------------------------------//


void setup() {
  // put your setup code here, to run once:


  Serial.begin(115200);


  setup_wifi();
  client.setServer(mqtt_server,mqttPort);
  client.setCallback(callback);

}

void loop() {
  // put your main code here, to run repeatedly:

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}

//------------------------WiFi Setup-------------------------------------//

void setup_wifi() {
    
    delay(100);
  // We start by connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}


//---------------------------While client not conncected---------------------------------//

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //if your MQTT broker has clientID,username and password
    //please change following line to    if (client.connect(clientId,userName,passWord))
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      
      
     
     //once connected to MQTT broker, subscribe command if any
     //----------------------Subscribing to required topics-----------------------//

     
      client.subscribe("mushroom/configData");
      Serial.println("Subsribed to topic: mushroom/configData");
      
      } else {
      
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 6 seconds before retrying
      delay(5000);
    }
  }
}



//-----------------------Callback function-------------------------------------//


void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  
//-----------------------Publishing hardware status upon request-------------//


if(strcmp(topic, "mushroom/configData") == 0){


  Serial.print("Message:");
  memset(Data, 0, sizeof(Data)/sizeof(char));//Resetting the array with all zeros
  Serial.print("Data array size:");
  Serial.println(sizeof(Data)/sizeof(char));
  Serial.print("Data before getting msg:");
  Serial.println(Data);

  
    did[24]={'0'};
    uid[24]={'0'};



    for (int i = 0; i < length; i++) {
    //Serial.print((char)payload[i]);
    //input=input+payload[i];
    Data[i]=payload[i];
    }
      Serial.print("Data:");
      Serial.println(Data);
      did_uid=did_uid+Data;
      Serial.print("Device id,User id:");
      Serial.print(did_uid);
      Serial.println();
      // Loop through each character and check if it's a comma
      Serial.print("configData length:");
      Serial.println(did_uid.length());
      lastIndex =0;
      for (int i = 0;i < did_uid.length(); i++){  
        
        if (did_uid.substring(i, i+1) == ",") //input.substring: This method extracts the characters in a string 
                                            //between "start" and "end", not including "end" itself
        {
          // Grab the piece from the last index up to the current position and store it
          Serial.print("lastIndex:");
          Serial.println(lastIndex);
          configData[counter] = did_uid.substring(lastIndex, i);
          Serial.println(configData[counter]);
          // Update the last position and add 1, so it starts from the next character
          lastIndex = i + 1;
          // Increase the position in the array that we store into
          counter++;
        }

        // If we're at the end of the string (no more commas to stop us)
        Serial.print("last string start at:");
        Serial.println(i);
        if (i == did_uid.length()-1) {
          // Grab the last part of the string from the lastIndex to the end
          configData[counter] = did_uid.substring(lastIndex, i+1);
          Serial.println(configData[counter]);
        }}
         
      // Clear out string and counters to get ready for the next incoming string
      did_uid ="";
      counter = 0;
      lastIndex = 0;
      }
    
  
  }
 
