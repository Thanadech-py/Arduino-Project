#include <ATX2.h>	// ATX2 Board
#include <PS2X_lib.h>  //for v1.6
#define PS2_DAT        15     
#define PS2_CMD        14  
#define PS2_SEL        13  
#define PS2_CLK        18  
//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false

PS2X ps2x; // create PS2 Controller Class
int x = 0;
int y = 0;
int speed = 75;
int speedml = 0;
int speedmr = 0;
int error = 0;
byte type = 0;
byte vibrate = 0;

void setup(){
  XIO();
  Serial.begin(115200);
  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it
  ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
	case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
   }
  glcdMode(1);
  setTextSize(3);
  setTextColor(GLCD_ORANGE);
  glcd(1,1,"C");
  setTextColor(GLCD_YELLOW);
  glcd(1,2,"H");
  setTextColor(GLCD_WHITE);
  glcd(1,3,"I");
  setTextColor(GLCD_VIOLET);
  glcd(1,4,"F");
  setTextColor(GLCD_PINK);
  glcd(1,5,"U");
  setTextColor(GLCD_LIME);
  glcd(1,6,"U");
  setTextSize(2);
  setTextColor(GLCD_RED);
  glcd(2,11,"X");
  setTextColor(GLCD_DOLLAR);
  glcd(3,2,"----------");
  setTextColor(GLCD_DOLLAR);
  while(true){
    glcd(4,2,"Push Start");
    delay(25);
    glcd(4,2,"          ");
    delay(25);
    ps2x.read_gamepad(false, vibrate); 
    if(ps2x.Button(PSB_START))         {
      beep(1);
      glcd(4,1,"Robot Active");
      delay(250);
      glcd(4,1,"move ");
      glcd(5,1,"Weapon :");
      setTextColor(GLCD_RED);
      glcd(5,9,"OFF");
      break;
    }
  }
}
void loop() {
    ps2x.read_gamepad(false, vibrate);
    setTextColor(GLCD_GREEN);
    int stx = map(ps2x.Analog(PSS_LX),128,255,0,100); 
    int sty = map(ps2x.Analog(PSS_LY),128,0,0,100); 
    if(ps2x.ButtonPressed(PSB_CIRCLE)) {
      motor(3,100);
      setTextColor(GLCD_RED);
      glcd(5,9,"CCW");
    }
    if(ps2x.ButtonPressed(PSB_SQUARE)) {
      motor(3,-100);
      setTextColor(GLCD_RED);
      glcd(5,9,"CW ");
    }
    if(ps2x.ButtonPressed(PSB_CROSS)) {
      motor(3,0);
      setTextColor(GLCD_RED);
      glcd(5,9,"OFF");
    }
    if(ps2x.Button(PSB_R1)){
      if(speed==50){speed=75;}
      else if(speed==75){speed=100;}
    }
    if(ps2x.Button(PSB_L1)){
      if(speed==100){speed=75;}
      else if(speed==75){speed=50;}
    }
    if(ps2x.Button(PSB_PAD_UP)) {      //will be TRUE as long as button is pressed
      glcd(4,5,"Forward");
      fd(speed);    
    }
    else if(ps2x.Button(PSB_PAD_RIGHT)){
      glcd(4,5,"SpRight");
      rd(speed);
    }
    else if(ps2x.Button(PSB_PAD_LEFT)){
      glcd(4,5,"SpLEFT"); 
      ld(speed);
    }
    else if(ps2x.Button(PSB_PAD_DOWN)){
      glcd(4,5,"Backward");
      bd(speed);   
    }
    else{
      motorst(speedml,speedmr);
      glcd(4,5," Control      ");
      br(); 
    }  
    speedml = sty+stx;
    speedmr = sty-stx;
    Serial.print(",");
    Serial.print(speedml);
    Serial.print(",");
    Serial.println(speedmr);
    
}
