
int ir_sensor_1 = 2;
int ir_sensor_2 = 3;
int ir_sensor_3 = 4;
int ir_sensor_4 = 5;
int ir_sensor_5 = 6;
int ir_sensor_6 = 7;
int ir_sensor_7 = 8;
int ir_sensor_8 = 9;
int ir_sensor_9 = 10;



void setup() {         
  Serial.begin(9600);
  pinMode(ir_sensor_1,INPUT);
  pinMode(ir_sensor_2,INPUT);
  pinMode(ir_sensor_3,INPUT);
  pinMode(ir_sensor_4,INPUT);
  pinMode(ir_sensor_5,INPUT);
  pinMode(ir_sensor_6,INPUT);
  pinMode(ir_sensor_7,INPUT);
  pinMode(ir_sensor_8,INPUT);
  pinMode(ir_sensor_9,INPUT);  
}

int getStatus(int value){
  if(digitalRead(value)){
    return 0;
  }
  else{
    return 1;
  }
}

int check_side(int sen_1,int sen_2,int sen_3){
  return getStatus(sen_1) + getStatus(sen_2) + getStatus(sen_3);
}

void loop() {
  int first = check_side(ir_sensor_1,ir_sensor_2,ir_sensor_3);
  if(first){
    Serial.print("First Side Density is : ");
    switch (first) {
      case 1:    
        Serial.print("MEDIUM");
        Serial.println();
        break;
      case 2:    
        Serial.print("HIGH");
        Serial.println();
        break;
      case 3:    
        Serial.print("VERY HIGH");
        Serial.println();
        break;
    }
  }
  else{
    Serial.println("First Side Density is : LOW");
  }
  
  int second = check_side(ir_sensor_4,ir_sensor_5,ir_sensor_6);
  if(second){
    Serial.print("Second Side Density is : ");
    switch (second) {
      case 1:    
        Serial.print("MEDIUM");
        Serial.println();
        break;
      case 2:    
        Serial.print("HIGH");
        Serial.println();
        break;
      case 3:    
        Serial.print("VERY HIGH");
        Serial.println();
        break;
    }
  }
  else{
    Serial.println("Second Side Density is : LOW");
  }
  
  int third = check_side(ir_sensor_7,ir_sensor_8,ir_sensor_9);
  if(third){
    Serial.print("Third Side Density is : ");
    switch (third) {
      case 1:    
        Serial.print("MEDIUM");
        Serial.println();
        break;
      case 2:    
        Serial.print("HIGH");
        Serial.println();
        break;
      case 3:    
        Serial.print("VERY HIGH");
        Serial.println();
        break;
    }
  }
  else{
    Serial.println("Third Side Density is : LOW");
  }
  delay(10000);
}
