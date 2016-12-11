/*
  Baseado no exemplo Web Server - Galileo
  Problema 2 - LAB II
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:

//169.254.191.15
byte mac[] = { 0x98, 0x4F, 0xEE, 0x01, 0xDA, 0xB9}; //Informado pela placa
byte ip[] = { 169, 254, 191, 16 };                  //Varia, utilizar sketch comando para descorir IP

// (port 80 é a padrao para HTTP, mas na rede da UFBA é melhor usar 8080):
EthernetServer server(8080); 
String readString;
int led  = 13;
int LM35 = 5;

void setup() {
  // Open serial communications and wait for port to open:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Servidor esta no IP ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Novo cliente");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // add a meta refresh tag, so the browser pulls again every 5 seconds:
          client.println("<meta http-equiv=\"refresh\" content=\"5\">");
          client.println("<title>LAB II</title>");
          // output the value of each analog input pin
          client.println("<h2>Valores portas analogicas</h2>");
          client.println("<br />");
          for (int analogChannel = 0; analogChannel < 5; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("Entrada analogica ");
            client.print(analogChannel);
            client.print(": ");
            client.print(sensorReading);
            client.println("<br />");       
          }
          int temperatura = (float(analogRead(LM35))*5/(1023))/0.01;
          client.print("Temperatura 5: ");
          client.print(temperatura);
          client.println("<br />");   
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
   
    Serial.println("Cliente desconectado");
  }
}
