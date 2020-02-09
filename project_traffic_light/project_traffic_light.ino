
int ir_sensor_1 = 2;
int ir_sensor_2 = 3;
int ir_sensor_3 = 4;
int ir_sensor_4 = 5;
int ir_sensor_5 = 6;
int ir_sensor_6 = 7;
int ir_sensor_7 = 8;
int ir_sensor_8 = 9;
int ir_sensor_9 = 10;
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
  pinMode(ir_sensor_7,INPUT);
  pinMode(ir_sensor_8,INPUT);
  pinMode(ir_sensor_9,INPUT);  
}

void show_density(int side, int density)
{
  if(density){
    switch (side) {
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
      case 3:    
        Serial.print(side);
        Serial.print(" side Density is : VERY HIGH");
        Serial.println();
        break;
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
  Serial.print("Array is now : [ ");
  for(int i=0;i<3;i++){
    Serial.print(a[i]);
    if(i != 2){
      Serial.print(" , ");
    }
  }
  Serial.print(" ] and the last open is : ");
  Serial.print(last_open);
}

int check_side(int sen_1,int sen_2,int sen_3){
  return getStatus(sen_1) + getStatus(sen_2) + getStatus(sen_3);
}

void loop() {
  a[0] = check_side(ir_sensor_1,ir_sensor_2,ir_sensor_3);
  show_density(1,a[0]);
  
  a[1] = check_side(ir_sensor_4,ir_sensor_5,ir_sensor_6);
  show_density(2, a[1]);
  
  a[2] = check_side(ir_sensor_7,ir_sensor_8,ir_sensor_9);
  show_density(3, a[2]);
  
  check_collision();
  
  if(collision[0] == 3){
    switch(last_open){
      case 1:
        Serial.println();
        Serial.print("Open Second under normal scenario");
        print_array();
        last_open = 2;
        delay(10000);
        break;
      case 2:
        Serial.println();
        Serial.print("Open Third under normal scenario");
        print_array();
        last_open = 3;
        delay(10000);
        break;
      case 3:
        Serial.println();
        Serial.print("Open First under normal scenario");
        print_array();
        last_open = 1;
        delay(10000);
        break;
    }
  }
  else if(collision[0] == 2){
    for(int i = 0;i<3;i++){
      if(collision[1] == a[i])
        if(last_open != 2 && i == 1){
          Serial.println();
          Serial.print("Open Second under dual load");
          print_array();
          last_open = 2;
          delay(10000);
          break;
        }
        if(last_open != 3 && i == 2){
          Serial.println();
          Serial.print("Open Third under dual load");
          print_array();
          last_open = 3;
          delay(10000);
          break;
        }
        if(last_open != 1 && i == 0){
          Serial.println();
          Serial.print("Open Third under dual load");
          print_array();
          last_open = 1;
          delay(10000);
          break;
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
