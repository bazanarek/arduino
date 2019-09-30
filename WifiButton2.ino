#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

int sendRequest() {
        StaticJsonBuffer<200> JSONBuffer;
        JsonObject& JSONencoder = JSONBuffer.createObject();
          
        JSONencoder["startDate"] = "1970-01-01T00:00";
        JSONencoder["endDate"] = "1970-01-01T00:01";
        JSONencoder["gameName"] = "fifa19";
        JSONencoder["playerId"] = "yuDWWXcgk4dYw1kub1ERg3ihvHe2";

        char JSONmessageBuffer[300];
        JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
          
        HTTPClient http;
        http.begin("http://15.188.50.142/matches?isQuickBooking=true");   //Specify request destination
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Auth-Id", "yuDWWXcgk4dYw1kub1ERg3ihvHe2");
        
        int httpCode = http.POST(JSONmessageBuffer);
        if (httpCode > 0 ) {
        String payload = http.getString(); 
        Serial.println(httpCode);   //Print HTTP return code
        Serial.println(payload);    //Print request response payload
        }
        http.end();  //Close connection
        
        return httpCode;
}
 
void setup() {
  pinMode(2, INPUT);
  pinMode(0, OUTPUT);
  Serial.begin(115200); 
  Serial.println("waiting");              //Serial connection
  WiFi.begin("Redmi", "wifirifi1234");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(1000);
    Serial.println("Waiting for connection");
  }
 
}

void loop() {
    int code = 0;
    int sensorVal = digitalRead(2);
    if (sensorVal == LOW ) {
        code = sendRequest();
        delay(100);
        if(code == 200){
            tone(0, 1000);
            delay(100);
            tone(0,2000);
            delay(100);
            noTone(0);
            Serial.println("bzzyt ok");
        }
        else if(code == 400) {
            tone(0, 800);
            delay(100);
            tone(0,300);
            delay(100);
            noTone(0);
            Serial.println("bzzyt not ok");
        }
        else {
            tone(0,300);
            delay(500);
            noTone(0);  
            Serial.println("bzzyt WTF");
        }
        code = 0;
        sensorVal= HIGH;
    }
}
