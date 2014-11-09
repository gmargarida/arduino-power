
const int controlPin = 3;
boolean pstailStatus = true;
boolean isLoggedIn = false;
byte loginFSM = 0;
char username[] = "admin";
char password[] = "admin";
boolean promptPrinted = false;


void setup () {
  Serial.begin(115200);
  Serial.println("arduino-power starting up");
  pinMode(controlPin, OUTPUT);
  if (pstailStatus == true)
    turnOnPstail();
  else
    turnOffPstail();
}

void loop () {
  char buf[12];
  byte ret;
  
  if (!promptPrinted && loginFSM == 0) {
    Serial.print("username: ");
    promptPrinted = true;
  } else if (!promptPrinted && loginFSM == 1) {
    Serial.print("password: ");
    promptPrinted = true;
  } else if (!promptPrinted) {
    Serial.print("$ ");
    promptPrinted = true;
  }
    
  memset(buf, 0, sizeof(buf));
  ret = Serial.readBytesUntil('\n', buf, sizeof(buf));
  if (ret != 0) {
     promptPrinted = false;
    if (loginFSM == 0) {
      if (strcmp(buf, username) == 0) {
        loginFSM = 1;
        Serial.println("");
      } else
        Serial.println("\nInvalid username");
      return;
    } 
    
    if (loginFSM == 1) {
      if (strcmp(buf, password) == 0) {
        loginFSM = 2;
        Serial.println("");
       } else {
         loginFSM = 0;
         Serial.println("\nInvalid password");
      }
      return;
    }
    Serial.println(buf);
    if (strcmp(buf, "enable") == 0) 
      turnOnPstail();
    else if (strcmp(buf, "disable") == 0)
      turnOffPstail();
    else if (strcmp(buf, "status") == 0)
      statusPstail();
    else if (strcmp(buf, "reset") == 0)
      resetPstail();
    else 
      Serial.println("Unknown command");  
  }
   
}

void turnOnPstail () {
   digitalWrite(controlPin, HIGH);
   pstailStatus = true;
}

void turnOffPstail () {
   digitalWrite(controlPin, LOW); 
   pstailStatus = false;
}

void statusPstail () {
    if (pstailStatus == false)
       Serial.println("Powerswitch tail is off");
     else
       Serial.println("Powerswitch tail is on"); 
}

void resetPstail () {
   turnOffPstail();
   delay(2000);
   turnOnPstail();
}
