#define MAX_COMMAND_SIZE 5000
#define PS1 "$# > "

void setup() {
  Serial.begin(9600);
  Serial.println("### Welcome to Serial Galileo Console ###");
  Serial.println();
}

void loop() {
  if(Serial.available()){
    char comando[MAX_COMMAND_SIZE];
    int i = 0;
    
    while(Serial.available() && i < MAX_COMMAND_SIZE){
      comando[i] = Serial.read();

      if(comando[i] != '\r' && comando[i] != '\n'){
        i += 1;
      }
    }

    if(i != MAX_COMMAND_SIZE){
      comando[i] = 0;
      Serial.print(PS1);
      Serial.println(comando);
      strcpy(&comando[i], " > /dev/ttyGS0 2> /dev/ttyGS0");
      system(comando);
    }
    else{
      Serial.println("[ERROR] The command entered is too long!\n" PS1);
    }
  }
}
