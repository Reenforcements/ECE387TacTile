int8_t *bytesIn;
uint8_t numByteIn = 0;
uint8_t arrayIn = 0;

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        bytesIn = (int8_t*)malloc(sizeof(int8_t) * 25);
}

void loop() {
  if(arrayIn){
    Serial.print("Array In :D!");
    for(int i = 0; i < 25; i++){
      Serial.print(*(bytesIn + i));
    }
    arrayIn = 0;
  }
}

void serialEvent() {
  while(Serial.available()){
    *(bytesIn + numByteIn) = Serial.read();
     numByteIn++;   
  }
  if(numByteIn == 25){
    numByteIn = 0;
    arrayIn = 1;
  }
}

