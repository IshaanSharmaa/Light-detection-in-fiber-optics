#include<SPI.h>
#define input_fg 5

char buff[]="Hello Slave\n";
int n_start = 0;
int n_step = 0;
int le = 16;

int c1 = 0; 
int c2 = 0;
int c_temp;
int c1_max = 150;
int temp = 0;
int t1,t2;
int x, y;
int c_1 = 0;
int i = 0;

void reset()
{
 i = 0;
 SPI.transfer(0x01);
 c2 = 0;
 c1 = 0;

 Serial.println("Enter number of pulses to be sampled: ");
 while(Serial.available() == 0)
 {}
 c1_max = Serial.readString().toInt();
 Serial.print(c1_max);

 Serial.println();

 Serial.println("Enter starting interval value (in nano-sec): ");
 while(Serial.available() == 0)
 {}
 n_start = Serial.readString().toInt();
 Serial.print(n_start);

 Serial.println();

 Serial.println("Enter step intervalvalue (in nano-sec): ");
 while(Serial.available() == 0)
 {}
 n_step = Serial.readString().toInt();
 Serial.print(n_step);  

 Serial.println();
}

void setup() {
 Serial.begin(9600); /* begin serial with 9600 baud */
 Serial.println();
 SPI.begin();  /* begin SPI */
 SPI.setBitOrder(MSBFIRST);
 pinMode(le, OUTPUT);
 pinMode(input_fg, INPUT);
 
 while(Serial.available() == 0)
 {}
 int trig = Serial.readString().toInt();
 
 reset();
}

void loop(){

  int c_2 = digitalRead(input_fg);
  float pw = pulseIn(input_fg, HIGH) ;
  
  if(c_2 == 1 && c_1 == 0)
  {
    c1 = c1 + 1;  
    t1 = millis();      
  }
  if(c1 == c1_max)
    {
      c1 = 0;
      c2 = c2 + 1;
      float out = n_start*0.2;
      digitalWrite(le, LOW);
      byte c;
      digitalWrite(le, HIGH);
      c = out;
      int ans = SPI.transfer(c);
      digitalWrite(le, LOW);
      // Serial.println(ans);
      n_start = n_start + n_step;
      if(n_start > 1200 )  
      {
        n_start = 0;
      }
    }

  if(c2 != c_temp)
  {
    
    Serial.print("Counter 2 : ");
    Serial.println(c2);
  }

  c_temp = c2;
  c_1 = c_2;

  if(Serial.available() > 0)
  {
    int trig2 = Serial.readString().toInt();
    reset();
  }

}
