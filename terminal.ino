void setup() {
  Serial.begin(9600);
  Serial.println("### Welcome to Serial Galileo Console ###");
  Serial.println();
}

void loop() {
  if(Serial.available()){
    char comando[2000];
    int i = 0;
    while(Serial.available()){
      comando[i] = Serial.read();
      i += 1;

      if(comando[i-1] == '\r' || comando[i-1] == '\n'){
        i -= 1;
      }
    }

    comando[i] = 0;
    Serial.print("$# > ");
    Serial.println(comando);
    strcpy(&comando[i], " > /dev/ttyGS0 2> /dev/ttyGS0");
    system(comando);
  }
}
