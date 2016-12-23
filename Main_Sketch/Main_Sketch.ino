/* The input pins of the Ultrasonic sensor */
#define trigPin 3
#define echoPin 2
/* The input pins of the H-bridge and the 2 motors */
#define M1_Left  5 
#define M1_Right 4
#define M2_Fwd 7
#define M2_Bck 6
/* This is your car's velocity in m/sec , Please modify it to your own car velcity */
#define Car_Speed 0.55 /*  */ 

String message; //string that stores the incoming message
long duration, distance, desired_distance = 0;
bool Flag=0;
unsigned long StartTime, CurrentTime ,ElapsedTime ;

void setup()
{
  Serial.begin(9600); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(M1_Left, OUTPUT);
  pinMode(M1_Right , OUTPUT);
  pinMode(M2_Fwd, OUTPUT);
  pinMode(M2_Bck , OUTPUT);  
}

void Read_Values(){
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
}
/* This function to detect if there is an obstacle in range of 20 cm or not and set the flad to high if there was an obstacle in the mentioned range */
void Is_Obstacle(){
  Read_Values();
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);
  if (distance < 20) { 
  Serial.println("Obstacle");
  Flag=1;
  }
  else if (distance >= 200 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
      Flag=0;
  }
}
/*
  go(1)   ->      Car goes forward
  go(2)   ->      Car goes backward
*/ 
void go(int direction)
{
  boolean inPin1 = HIGH;
  boolean inPin2 = LOW;

  if(direction== 1){
    inPin1 = LOW;
    inPin2 = HIGH;
  }
    digitalWrite(M2_Fwd, inPin1);
    digitalWrite(M2_Bck , inPin2);
}

/* Car goes straight */
void straight(){
    digitalWrite(M1_Left, LOW);
    digitalWrite(M1_Right , LOW);
}

/*
  turn(1)   ->      Car tuns right
  turn(2)   ->      Car turns left
*/ 
void turn(int direction)
{
  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction== 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }
    digitalWrite(M1_Left, inPin1);
    digitalWrite(M1_Right , inPin2);
}

/* Car Stops */
void stop(){
    digitalWrite(M1_Left, LOW);
    digitalWrite(M1_Right , LOW);
    digitalWrite(M2_Fwd, LOW);
    digitalWrite(M2_Bck , LOW);
}

void loop()
{
  while(Serial.available())
  {
   //while there is data available on the serial monitor
    message=char(Serial.read());//store string from serial command
    /* if there is no obstacle */
    if ( Flag == 0)
    { 
      /* Checking on which charachter i recieved from the bluetooth serial */ 
      if (message == "3")     {      
            desired_distance=3000;
            go(1); /* */ 
            StartTime = millis();
            Serial.println(" I got 3 "); //show the data 
      }
      else if (message == "5"){   
            desired_distance=5000;
            go(1); /* */    
            StartTime = millis();
            Serial.println(" I got 5 "); //show the data 
      }
      else if (message == "r"){  
          go(1); /* */ 
          turn (1);   
          delay(1000);
          straight();             
          Serial.println(" I got r "); //show the data 
      }
      else if (message == "l"){ 
          go(1); /* */ 
          turn (2); 
          delay(1000);
          straight();     
          Serial.println(" I got l "); //show the data 
      }
      else if (message == "s"){      
          stop(); /* */ 
          Serial.println(" I got s "); //show the data 
      }
      else if (message == "b"){      
          go(2); /* */ 
          Serial.println(" I got b "); //show the data 
      }
      else if (message == "f"){      
          go(1); /* */ 
          Serial.println(" I got f "); //show the data 
      }  
       else if ( ((millis()-StartTime)/(1000*60))*Car_Speed == desired_distance ) {
          stop(); 
          Serial.println("Catch your Pokemon ! ");
      }
      
    }    else if ( Flag == 1) { /* When there is obstacle the car stops and goes back to the  manual mode , where the user fully controls the movment*/
          stop();}
  }
  if(!Serial.available())
  {
    if(message!="")
    {//if data is available
          Serial.println(message); //show the data
          message=""; //clear the data
    }
  }
  delay(500); //delay
}
