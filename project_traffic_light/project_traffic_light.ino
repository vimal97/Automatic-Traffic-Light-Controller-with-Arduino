
int ir_sensor_1 = 2;
int ir_sensor_2 = 3;
int ir_sensor_3 = 4;
int ir_sensor_4 = 5;
int ir_sensor_5 = 6;
int ir_sensor_6 = 7;
//int ir_sensor_7 = 8;
//int ir_sensor_8 = 9;
//int ir_sensor_9 = 10;

int traffic_light_1 = 22;
int traffic_light_2 = 23;
int traffic_light_3 = 24;
int traffic_light_4 = 25;
int traffic_light_5 = 26;
int traffic_light_6 = 27;
int traffic_light_7 = 28;
int traffic_light_8 = 29;
int traffic_light_9 = 30;


int last_open = 3;
int a[3];
int output[2];
int collision[2];

void setup() {         
  Serial.begin(9600);
  pinMode(ir_sensor_1,INPUT);
  pinMode(ir_sensor_2,INPUT);
  pinMode(ir_sensor_3,INPUT);
  pinMode(ir_sensor_4,INPUT);
  pinMode(ir_sensor_5,INPUT);
  pinMode(ir_sensor_6,INPUT);
  //pinMode(ir_sensor_7,INPUT);
  //pinMode(ir_sensor_8,INPUT);
  //pinMode(ir_sensor_9,INPUT);  
}

void show_density(int side, int density)
{
  if(density){
    switch (density) {
      case 1:    
        Serial.print(side);
        Serial.print(" side Density is : MEDIUM");
        Serial.println();
        break;
      case 2:
        Serial.print(side);    
        Serial.print(" side Density is : HIGH");
        Serial.println();
        break;
      //case 3:    
      //  Serial.print(side);
      //  Serial.print(" side Density is : VERY HIGH");
      //  Serial.println();
      //  break;
    }
  }
  else{
    Serial.print(side);
    Serial.println(" side Density is : LOW");
  }
}

int getStatus(int value){
  if(digitalRead(value)){
    return 0;
  }
  else{
    return 1;
  }
}

void check_collision(){
  int max = 0;
  int count_of_max = 0;
  for(int i = 0;i < 3;i++){
    if(a[i] > max)
      max = a[i];
  }
  for(int i = 0;i < 3;i++){
    if(a[i] == max)
      count_of_max++;
  }
  collision[0] = count_of_max;
  collision[1] = max;
}

void print_array(){
  Serial.print(" Array is now : [ ");
  for(int i=0;i<3;i++){
    Serial.print(a[i]);
    if(i != 2){
      Serial.print(" , ");
    }
  }
  Serial.print(" ] and the last open is : ");
  Serial.print(last_open);
}

int check_side(int sen_1,int sen_2){
  return getStatus(sen_1) + getStatus(sen_2);
  // + getStatus(sen_2)
}

void loop() {
  a[0] = check_side(ir_sensor_1,ir_sensor_2);
  show_density(1,a[0]);
  
  a[1] = check_side(ir_sensor_3,ir_sensor_4);
  show_density(2, a[1]);
  
  a[2] = check_side(ir_sensor_5,ir_sensor_6);
  show_density(3, a[2]);
  delay(1000);
  
  
  check_collision();
  
  if(collision[0] == 3){
    switch(last_open){
      case 1:
        Serial.println();
        Serial.print("Open Second under normal scenario");
        digitalWrite(traffic_light_3,HIGH);
        digitalWrite(traffic_light_4,HIGH);
        digitalWrite(traffic_light_9,HIGH);
        print_array();
        last_open = 2;
        delay(10000);
        digitalWrite(traffic_light_3,LOW);
        digitalWrite(traffic_light_4,LOW);
        digitalWrite(traffic_light_9,LOW);
        break;
      case 2:
        Serial.println();
        Serial.print("Open Third under normal scenario");
        digitalWrite(traffic_light_3,HIGH);
        digitalWrite(traffic_light_6,HIGH);
        digitalWrite(traffic_light_7,HIGH);
        print_array();
        last_open = 3;
        delay(10000);
        digitalWrite(traffic_light_3,LOW);
        digitalWrite(traffic_light_6,LOW);
        digitalWrite(traffic_light_7,LOW);
        break;
      case 3:
        Serial.println();
        Serial.print("Open First under normal scenario");
        digitalWrite(traffic_light_1,HIGH);
        digitalWrite(traffic_light_6,HIGH);
        digitalWrite(traffic_light_9,HIGH);
        print_array();
        last_open = 1;
        delay(10000);
        digitalWrite(traffic_light_1,LOW);
        digitalWrite(traffic_light_6,LOW);
        digitalWrite(traffic_light_9,LOW);
        break;
    }
  }
  else if(collision[0] == 2){
    for(int i = 0,finished = 0; i<3; i++){
      if(finished == 2){
        Serial.print("Breaked of of fucking crap");
        break;
      }
      if(collision[1] == a[i]){
        if(last_open != 2 && i == 1){
          Serial.println();
          Serial.print("Open Second under dual load");
          Serial.print(finished);
          print_array();
          last_open = 2;
          ++finished;
          delay(10000);
          continue;
        }
        if(last_open != 3 && i == 2){
          Serial.println();
          Serial.print("Open Third under dual load");
          Serial.print(finished);
          print_array();
          last_open = 3;
          ++finished;
          delay(10000);
          continue;
        }
        if(last_open != 1 && i == 0){
          Serial.println();
          Serial.print("Open First under dual load");
          Serial.print(finished);
          print_array();
          last_open = 1;
          finished++;
          delay(10000);
          continue;
        }
    }
  }
 }
  else{
    if(a[0] > a[1]){
      if(a[0] > a[2]){
          //leave first
          Serial.println();
          Serial.print("Open First under single load");
          print_array();
          last_open = 1;
          delay(10000);
      }
      else{
          //leave second
          Serial.println();
          Serial.print("Open Second under single load");
          print_array();
          last_open = 2;
          delay(10000);
     }
    }
    else{
      if(a[1] > a[2]){
          //leave second
          Serial.println();
          Serial.print("Open Second under single load");
          print_array();
          last_open = 2;
          delay(10000);
      }
      else{
          //leave third
          Serial.println();
          Serial.print("Open Third under single load");
          print_array();
          last_open = 2;
          delay(10000);
      }
    }
 }
}
