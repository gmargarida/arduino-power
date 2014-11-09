
const int controlPin = 3;
boolean pstailStatus = true;


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
  memset(buf, 0, sizeof(buf));
  ret = Serial.readBytesUntil('\n', buf, sizeof(buf));
  if (ret != 0) {
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
