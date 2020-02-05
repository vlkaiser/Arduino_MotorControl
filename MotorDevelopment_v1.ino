/**************** Motor Controller Test ******************
 *  24V Power Supply
 *  CVD215-K Motor Driver
 *  LIN LE11LS032PS01-18E0100-LNE-03500-E01 Motor with
 *  US Digital E2-256-315-IE-D-D-B Encoder
 *  Pushbutton with 10K pulldown and 3.3ms RC (Pressed = HIGH)
 *  Indicator LED (GPIO HIGH = LED ON)
 *  
 *  Serial Monitor @ 115200 (USB)
 *  
 *  Feb-05-2020 VK
 *********************************************************/

/************** Signal Descriptions **********************
 *  Motor Driver:
 *  When the PLS Input is turned from OFF to ON while DIR is ON
 *    Motor will rotate by one step CW
 *    DIR = HIGH, PLS = LOW, PLS = HIGH -> CW : 1 STEP
 *  When the PLS Input is turnned from OFF to ON while DIR is OFF
 *    Motor will rotate by one step CCW
 *    DIR = LOW, PLS = LOW, PLS = HIGH -> CCW : 1 STEP
 *    
 *  MAX Input Pulse Frequency 50% duty cycle
 */

/* TypeDef */
#define ACTIVE    HIGH       // Pushbutton Pressed (Normally Low), GPIO HIGH LED On
#define INACTIVE  LOW    


/* Arduino Pin Definitions */
#define StatusLED   13
#define pushBTN     7
#define encCHA      2     // Channel A Encoder
#define encCHB      3     // Channel B Encoder
#define PLS         8     // Motor Driver Pulse+ Pin (PLS- = GND)
#define DIR         9     // Motor Driver Direction+ Pin (DIR- = GND)

int i = 0;

/* Prototypes */
void motorCW(void);
void motorCCW(int NumStep);

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(StatusLED, OUTPUT);
  pinMode(pushBTN, INPUT);

  pinMode(PLS, OUTPUT);
  pinMode(DIR, OUTPUT);

  pinMode(encCHA, INPUT_PULLUP);
  pinMode(encCHB, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(CHA), attach_interrupt0, CHANGE); // AttachInterrupt 0 is DigitalPin 2
  //attachInterrupt(digitalPinToInterrupt(CHB), attach_interrupt1, CHANGE); // AttachInterrupt 1 is DigitalPin 3
  
  Serial.begin(115200);
  while(!Serial) {}
  
  Serial.println("Initializing...");
  digitalWrite( DIR, LOW );
  digitalWrite( PLS, LOW );
}

void motorCW()
{
  //See Signal Descriptions Note
  digitalWrite( DIR, HIGH );
  delay(5);
  digitalWrite( PLS, LOW );
  delay(5);
  digitalWrite( PLS, HIGH );
}

void motorCCW(int NumStep)
{
  //See Signal Descriptions Note
  for (int x = 0; x < NumStep; x++)
  {
    digitalWrite( DIR, LOW );
    delay(5);
    digitalWrite( PLS, LOW );
    delay(5);
    digitalWrite( PLS, HIGH );
  }
}

void loop() 
{
   digitalWrite( LED_BUILTIN, digitalRead(pushBTN) );
  
   if( digitalRead(pushBTN) == ACTIVE )
   {
      digitalWrite( StatusLED, ACTIVE );
      //motorCW();    
      //Serial.print("Motor Step ");
      //Serial.println(i);
      //i++;
      motorCCW(500);
      
   }
   else
   {
      i = 0;
      digitalWrite( StatusLED, INACTIVE );
      digitalWrite( PLS, LOW ); 
      digitalWrite( DIR, LOW);
      
   }
}
