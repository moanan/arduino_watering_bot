// Vacation water dispensor for Cai's plants

// const
const unsigned long NEXT_H = 48;
const unsigned long NEXT_M = 0;
const unsigned long NEXT_S = 0;
const unsigned long WATERTIME_S = 30;

// motor A
const byte dir1PinA = 13;
const byte dir2PinA = 12;
const byte speedPinA = 10;

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
//  interval = (unsigned long)(3600*NEXT_H + 60*NEXT_M + NEXT_S)*1000;
  interval = 172800000; // every two days

  waterTime = WATERTIME_S*1000;
  time_1 = millis();
  time_2 = millis();
  // pump water for one time when power on
  pump_water(waterTime, speed, dir);
}

void loop() 
{

  if(millis() >= time_1 + interval)
  {
    time_1 += interval;
    print_time(time_1);
    pump_water(waterTime, speed, dir);
  }


  if(millis() >= time_2 + 1000) // print every 1 s
  {
    time_2 += 1000;
    unsigned long next = (time_1+interval-millis())/1000;
    unsigned long h = next/3600;
    unsigned long m = (next-3600*h)/60;
    unsigned long s = next-3600*h-60*m;
    Serial.print("Next water time in: ");
    Serial.print(h);
    Serial.print("h ");
    Serial.print(m);
    Serial.print("m ");
    Serial.print(s);
    Serial.print("s,\t next in s: ");    
    Serial.println(next);
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
