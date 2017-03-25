#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6
#define NUMPIXELS      26

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

 // delay for half a second



int ledPin =13;
int state=0;
int flag=0;
int letterIndex=0;
int switchState=0;
int lightUpDelay = 1000;
int lightUpLetterDelay=500;
int lightUpSpaceDelay=1000;
long timer=0;
volatile long lastButtonPush = 0;
boolean idleMode=false;

void setup(){
  randomSeed(millis());
  Serial.begin(9600);
  pixels.begin();
  pinMode(2,INPUT);
  pinMode(ledPin,OUTPUT);
  digitalWrite(2,HIGH);
  attachInterrupt(0,react,FALLING);
  
  TwinkleRandom(13,150,false);
  FadeInOut(5);
  FadeInOut(7);
  FadeInOut(9);
  
  timer=millis();
}

void loop(){
  if(Serial.available()>0){
    char letter = Serial.read();
    if(letter =='1'){
      lightUpDelay = 1000;
      lightUpLetterDelay=500;
      lightUpSpaceDelay=1000;    
    }
    else if(letter =='2'){
      lightUpDelay=500;
      lightUpLetterDelay=250;
      lightUpSpaceDelay=500; 
    }
    else if(letter =='3'){
      lightUpDelay=250;
      lightUpLetterDelay=100;
      lightUpSpaceDelay=400; 
    }
    else if(letter =='4'){
      idleMode=!idleMode;
    }
    else{
      letterIndex=getLetterIndex(letter);
      lightUp(letterIndex,letter);
    }
    timer=millis();
  }
  else if(switchState==1){
    TwinkleRandom(26,10,false);
    FadeInOut(1);
    FadeInOut(1);
    FadeInOut(1);
    switchState=0;
    timer=millis();
  }
  else if(millis()-timer > 10000 && idleMode==true){
    TwinkleRandom(26,random(10,20),true);
  }
}

void react()
{
  long fin = millis();
  
  if(fin - lastButtonPush > 500)
  {  
    while(Serial.available() > 0) {
      char t = Serial.read();
    }
    switchState=1;
  }
  
  lastButtonPush = fin;
}

void FadeInOut(uint8_t wait) {

  uint8_t red [NUMPIXELS];
  uint8_t green [NUMPIXELS];
  uint8_t blue [NUMPIXELS];

  // randomly set each colour
  for (int i = 0; i < NUMPIXELS; i++)
    {
    red [i] = random(256);
    green [i] = random(256);
    blue [i] = random(256);
    }

  for(uint8_t b = 0; b <255; b++) {
     for(uint8_t i=0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i, red [i] * b/255, green [i] * b/255, blue [i] * b/255);
     }

     pixels.show();
     delay(wait);
  }

  for(uint8_t b=255; b > 0; b--) {
     for(uint8_t i = 0; i < pixels.numPixels(); i++) {
        pixels.setPixelColor(i, red [i] * b/255, green [i] * b/255, blue [i] * b/255);
     }
     pixels.show();
     delay(wait);
  }
}

void FadeOutSet(uint8_t wait, uint8_t pixelAmount, uint8_t* pixelNumbers, uint8_t* red,uint8_t* green, uint8_t* blue) {
  for(uint8_t b=255; b > 0; b--) {
     for(uint8_t i = 0; i < pixelAmount; i++) {
        pixels.setPixelColor(pixelNumbers[i], red [i] * b/255, green [i] * b/255, blue [i] * b/255);
     }
     pixels.show();
     delay(wait);
  }
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUMPIXELS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  pixels.show();
}

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  uint8_t pixelNumbers [Count];
  uint8_t red [Count];
  uint8_t green [Count];
  uint8_t blue [Count];
  boolean exit=false;
  for (int i=0; i<Count; i++) {
     pixelNumbers[i]=random(NUMPIXELS);
     red[i]=random(0,255);
     green[i]=random(0,255);
     blue[i]=random(0,255);
     if(OnlyOne) {
       setPixel(pixelNumbers[i],red[i],green[i],blue[i]);
       FadeOutSet(0,1,pixelNumbers,red,green,blue);
       break;
     }
     else{
       setPixel(pixelNumbers[i],red[i],green[i],blue[i]);
       pixels.show();
       delay(SpeedDelay);
       exit=true;
     } 
   }
  
  if(!exit){
    delay(SpeedDelay);
    FadeOutSet(5, Count, pixelNumbers, red, green, blue);
  }
}

void lightUp(int charIndex,char letter)
{
  if(charIndex > -1){
    pixels.setPixelColor(charIndex, getColor(letter));
    pixels.show();
    delay(lightUpDelay);
    pixels.setPixelColor(charIndex, pixels.Color(0,0,0));
    pixels.show();
    delay(lightUpLetterDelay);
  }
  else{
    delay(lightUpSpaceDelay);
  }
  
}

int getLetterIndex(char letter){
  switch(letter)
    {
      case 'a':
      case 'A':
        return 0;
        break;
        
      case 'b':
      case 'B':
        return 1;
        break;
      case 'c':
      case 'C':
        return 2;
        break;
      case 'd':
      case 'D':
        return 3;
        break;
      case 'e':
      case 'E':
        return 4;
        break;
      case 'f':
      case 'F':
        return 5;
        break;
      case 'g':
      case 'G':
        return 6;
        break;
      case 'h':
      case 'H':
        return 7;
        break;
      case 'i':
      case 'I':
        return 16;
        break;
      case 'j':
      case 'J':
        return 15;
        break;
      case 'k':
      case 'K':
        return 14;
        break;
      case 'l':
      case 'L':
        return 13;
        break;
      case 'm':
      case 'M':
        return 12;
        break;
      case 'n':
      case 'N':
        return 11;
        break;
      case 'o':
      case 'O':
        return 10;
        break;
      case 'p':
      case 'P':
        return 9;
        break;
      case 'q':
      case 'Q':
        return 8;
        break;
      case 'r':
      case 'R':
        return 17;
        break;
      case 's':
      case 'S':
        return 18;
        break;
      case 't':
      case 'T':
        return 19;
        break;
      case 'u':
      case 'U':
        return 20;
        break;
      case 'v':
      case 'V':
        return 21;
        break;
      case 'w':
      case 'W':
        return 22;
        break;
      case 'x':
      case 'X':
        return 23;
        break;
      case 'y':
      case 'Y':
        return 24;
        break;
      case 'z':
      case 'Z':
        return 25;
        break;
      default:
        return (-1);
        break;
    }
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
   pixels.setPixelColor(Pixel, pixels.Color(red, green, blue));
}

uint32_t getColor(char letter) {
  switch (letter) {
    // WHITE
    case 'a':
    case 'A':
    case 'l':
    case 'L':
    case 's':
    case 'S':
      return pixels.Color(255, 255, 255);
    // BLUE
    case 'b':
    case 'B':
    case 'e':
    case 'E':
    case 'H':
    case 'h':
    case 'i':
    case 'I':
    case 'k':
    case 'K':
    case 'u':
    case 'U':
    case 'w':
    case 'W':
      return pixels.Color(0,0,255);
    // RED
    case 'g':
    case 'G':
    case 'n':
    case 'N':
    case 'y':
    case 'Y':
      return pixels.Color(0, 80, 0);
    // YELLOW
    case 'f':
    case 'F':
    case 'm':
    case 'M':
    case 't':
    case 'T':
    case 'x':
    case 'X':
      return pixels.Color(80,255,0);
    // Aqua:
    case 'd':
    case 'D':
    case 'p':
    case 'P':
    case 'r':
    case 'R':
      return pixels.Color(255,0,255);
    // Violet
      case 'c':
      case 'C':
      case 'j':
      case 'J':
      case 'o':
      case 'O':
      case 'q':
      case 'Q':
      case 'v':
      case 'V':
      case 'z':
      case 'Z':
      return pixels.Color(0, 255, 255);
      
    default:
      return pixels.Color(255,255,255);
  }
}

