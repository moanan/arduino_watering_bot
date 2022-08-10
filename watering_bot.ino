// Vacation water dispensor for Cai's plants

// const
const unsigned long NEXT_H = 1;
const unsigned long NEXT_M = 1;
const unsigned long NEXT_S = 0;
const unsigned long WATERTIME_S = 20;

// motor A
int dir1PinA = 13;
int dir2PinA = 12;
int speedPinA = 10;


int speed = 200;
bool dir = 1;

unsigned long interval;
unsigned long waterTime;
unsigned long time_1;
unsigned long time_2;
 
void setup()
{
  Serial.begin(115200);
  pinMode(dir1PinA, OUTPUT);
  pinMode(speedPinA, OUTPUT);
  interval = (unsigned long)(1440*NEXT_H + 60*NEXT_M + NEXT_S)*1000;
//  interval = (unsigned long)(60*NEXT_M + NEXT_S)*1000;
  waterTime = WATERTIME_S*1000;
  time_1 = millis();
  time_2 = millis();
}

void loop() 
{

  if(millis() >= time_1 + interval)
  {
    time_1 += interval;
    print_time(time_1);
    pump_water(waterTime, speed, dir);
  }


  if(millis() >= time_2 + 1000) // excute every 1 s
  {
    time_2 += 1000;
    int next = (time_1+interval-millis())/1000;
    int h = next/1440;
    int m = (next-1440*h)/60;
    int s = next-1440*h-60*m;
    Serial.print("Next water time in: ");
    Serial.print(h);
    Serial.print("h ");
    Serial.print(m);
    Serial.print("m ");
    Serial.print(s);
    Serial.println("s");    
  }

}


void print_time(unsigned long time_millis){
  Serial.print("Time: ");
  Serial.print(time_millis/1000);
  Serial.println("s, watering now!");
}

void pump_water(int time_millis, int speed, bool direction)
{  
  if (direction == 1) 
  {
    digitalWrite(dir1PinA, LOW); 
    digitalWrite(dir2PinA, HIGH); 
  } 
  else 
  { 
    digitalWrite(dir1PinA, HIGH); 
    digitalWrite(dir2PinA, LOW);    
  }
  analogWrite(speedPinA, speed);
  delay(time_millis);
  analogWrite(speedPinA, 0);
  Serial.println("Finish!");
}
