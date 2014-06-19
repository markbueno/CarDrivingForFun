/////RC Car Controls/////
// Mark Bonneaux
// V2 as on 6/19/2014

//  Equipment:
//    Futaba R617FS reciever
//    Futaba T6EX Remote
//    double H-bridge for steering and throttle
//    Arduino UnoR3
//  Pinouts:
//    Forward is pin 8 on Arduino and pin 1 on H-bridge
//    Reverse is pin 9 on Arduino and pin 2 on H-bridge
//    Left is pin 10 on Arduino and pin 3 on H-bridge
//    Right is pin 11 on Arduino and pin 4 on H-bridge
//    Steering signal is pin 12 on Arduino and signal pin on Ch 2 on reciever
//    Throttle signal is pin 13 on Arduino and signal pin on Ch 1 on reciever
//    Reciever is powered by 5V and Ground to inner and outer pins on Ch 7/8 on reciever
//    Make sure to run a ground line from the H-Bridge to the Arduino or nothing's going to run (I did this at least 3 times)


//  Globals
const int go = 8;
const int back = 9;
const int left = 10;  // proto car 1 does not support partial turning; these must be digitalWrites
const int right = 11; // ""

int throttle = 0;
int steer = 0;


void setup()
{
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);

  //Debugging via Terminal
  //  Serial.begin(9600);
}

void loop()
{
  throttle = pulseIn(12, LOW) / 10;  //these lines are the incoming signal from the reciever
  steer = pulseIn(13, HIGH) / 10;

  //Debugging via Terminal
  //  Serial.print(throttle);
  //  Serial.print("   ");
  //  Serial.print(steer);
  //  Serial.print("\n\n");

  // In my testing, steering at neutral read at either 150 or 151 and, on a full charge, throttle usually ran between 1440 and 1445.
  // I gave an additional buffer in the zone since, at least with this setup, as the controller's power goes down, so does the incoming signal

  if (throttle < 1425 )
  {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
  }
  if (throttle > 1460)
  {
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
  }
  else if (throttle >= 1425 && throttle <= 1460)  //This gives you a dead zone when the control is neutral
  {
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }

  if (steer < 150)
  {
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW) ;
  }
  if (steer > 151)
  {
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
  }
  else if (steer == 150 || steer == 151)
  {
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }

  //  delay();  // this is for debugging purposes if you don't want to have the terminal run as fast as it can
}
