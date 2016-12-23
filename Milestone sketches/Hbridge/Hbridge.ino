int M1_Left = 5; //Direccion
int M1_Right = 4; //Direccion
int M1_Fwd = 7; //Direccion
int M1_Bck = 6; //Direccion

void setup()
{
  pinMode(M1_Left, OUTPUT);
  pinMode(M1_Right , OUTPUT);
  pinMode(M1_Fwd, OUTPUT);
  pinMode(M1_Bck , OUTPUT);  
}

void loop(){
  turn (1); 
  delay(1000); //1 sg 
  
  stop();
  delay(1000); //1 sg 

  turn(2); 
  delay(1000); //1 sg 
  
  stop();
  delay(250); //250ms
  
   go (1); 
  delay(3000); //1 sg 
  
  stop();
  delay(250); //250ms

  go(2); 
  delay(3000); //1 sg 
  
  stop();
  delay(250); //250ms
}

void go(int direction)
{
  boolean inPin1 = HIGH;
  boolean inPin2 = LOW;

  if(direction== 1){
    inPin1 = LOW;
    inPin2 = HIGH;
  }
    digitalWrite(M1_Fwd, inPin1);
    digitalWrite(M1_Bck , inPin2);
}

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

void stop(){
    digitalWrite(M1_Left, LOW);
    digitalWrite(M1_Right , LOW);
    digitalWrite(M1_Fwd, LOW);
    digitalWrite(M1_Bck , LOW);
}
