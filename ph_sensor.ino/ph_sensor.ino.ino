#include <Bridge.h>

String BACKEND_URL = "http://883768b9.ngrok.io/ph_data";
Process process;

void setup() {
  // put your setup code here, to run once:

  Bridge.begin();
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

    doCurl(15);
 

  /* Response from the request, if needed */
  while (process.available()>0) {
    char c = process.read();
    Serial.print(c);
  }
}

void doCurl(int _value) {
  Serial.println(_value);

  process.begin("curl");
  // process.addParameter("-k"); // allow insecure (not https)
  process.addParameter("-X"); // use POST instead of default GET
  process.addParameter("POST");
  process.addParameter("-H"); // Any headers go after -H
  process.addParameter("Content-Type: application/json");

  /* Add data */
  process.addParameter("-d");
  process.addParameter("{ \"time_stamp\": \"2025-04-18 04:05:06\", \"ph\": 7 }");
  process.addParameter(BACKEND_URL);
  
  process.runAsynchronously();
  Serial.println("tried");

  delay(5000);
}
