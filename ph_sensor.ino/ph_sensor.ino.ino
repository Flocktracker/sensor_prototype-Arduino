#include <Bridge.h>
#include <Time.h>

String BACKEND_URL = "http://883768b9.ngrok.io/ph_data";
Process process;


int analogPin = 0;     // potentiometer wiper (middle terminal) connected to analog pin 3

                       // outside leads to ground and +5V

int val = 0;           // variable to store the value read


void setup() {
  // put your setup code here, to run once:

  Bridge.begin();
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

    float ph = analogRead(analogPin);
    //float ph = -7 + (analogRead(analogPin)*(14/255));
    long timestamp = timeInEpoch();
    doCurl(ph, timestamp);
 

  /* Response from the request, if needed */
  while (process.available()>0) {
    char c = process.read();
    Serial.print(c);
  }

  delay(3000);
}

unsigned long timeInEpoch() {
  unsigned long millisAtEpoch;  // millis at the time of timestamp
  Process time;                   // process to run on Linuino
  char epochCharArray[12] = "";   // char array to be used for atol

  // Get UNIX timestamp
  time.begin("date");
  time.addParameter("+%s");
  time.run();
  
  // When execution is completed, store in charArray
  while (time.available() > 0) {
    millisAtEpoch = millis();
    time.readString().toCharArray(epochCharArray, 12);
  }
  
  // Return long with timestamp
  return atol(epochCharArray);
}

void doCurl(float value, long time) {
  process.begin("curl");
  // process.addParameter("-k"); // allow insecure (not https)
  process.addParameter("-X"); // use POST instead of default GET
  process.addParameter("POST");
  process.addParameter("-H"); // Any headers go after -H
  process.addParameter("Content-Type: application/json");

  /* Add data */
  process.addParameter("-d");
  process.addParameter("{ \"time_stamp\": " + String(time) + ", \"ph\":" + String(value) + " }");
  process.addParameter(BACKEND_URL);
  
  process.runAsynchronously();
  Serial.println("tried");
}
