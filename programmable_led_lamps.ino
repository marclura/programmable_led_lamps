/*
 * SUPSI AI - Programmable lights tubes
 * 
 * Marco Lurati 2018
 * 
 */

#include <Adafruit_NeoPixel.h>

class Pot {

  public:
  
  byte pin, val, old;
  char id;

  Pot(const char id_in, const byte pin_in) {
    id = id_in;
    pin = pin_in;
    val = 0;
    old = 0;
  }

  void readPot(const String mode) {
    unsigned int temp = 0;
    byte rounding, read_times, del;
    
    if(mode.equals("static")) {
      rounding = 200;
      read_times = 62;
      del = 200;
    } else if (mode.equals("fast")) {
      rounding = 50;
      read_times = 10;
      del = 10;
    }
    
    for(int i=0; i<read_times; i++) { // multiple reading
      temp += analogRead(pin);
      delayMicroseconds(del);
    }

    //Serial.println(temp);
    
    //temp = ((temp + rounding) / rounding) * rounding / read_times;    // rounding to full val
    temp = ((temp/rounding + (temp%rounding>2)) * rounding) / read_times;

    //Serial.println(temp);

    if(temp < 200) {
      val = 0;
    } else if (temp >= 200 && temp < 1000) {
      // (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
      val = map(temp, 200, 1020, 0, 255);
      //val = ((temp - 200) * (255 - 0)) / (1020 - 200) + 0;      
    } else val = 255;
    
  }

  bool changed(const String mode) {

    readPot(mode);

    if(val != old) {
      old = val;
      return true;
    } else {
      return false;
    }
  }

  void debug() {
    Serial.print(id);
    Serial.print(F(", val:"));
    Serial.print(val);
    Serial.print(F(", old:"));
    Serial.println(old);
  }
  
};

class Lamp {

  public:
  
  unsigned int start, last;
  byte id, len, P_id, r, g, b, w;

  Lamp(const byte id_in, const byte P_in, const unsigned int start_in, const byte length_in) {
    id = id_in;
    P_id = P_in;
    start = start_in;
    len = length_in;
    last = start + len - 1;
  }

  void updateCol(byte const r_in, byte const g_in, byte const b_in, byte const w_in) {
    r = r_in;
    g = g_in;
    b = b_in;
    w = w_in;
  }

  void setColors() {

  }

  void debug() {
    Serial.print(F("L"));
    Serial.print(id);
    Serial.print(F(",\tstart: "));
    Serial.print(start);
    Serial.print(F(",\tend: "));
    Serial.println(last);    
  }
  
};


// Neopixels Data pins
const int pin_data_A = 5;
const int pin_data_B = 6;
const int pin_data_C = 7;

// number of led bars per channel
const int lampsA = 4;
const int lampsB = 4;
const int lampsC = 2;

// number of pixel for lamp
const int n = 52;

// number of neopixels
const int numA = n * lampsA;
const int numB = n * lampsB;
const int numC = n * lampsC;

// number of lamps
const byte lamps = 10;


// neopixel strips
Adafruit_NeoPixel P1 = Adafruit_NeoPixel(numA, pin_data_A, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel P2 = Adafruit_NeoPixel(numB, pin_data_B, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel P3 = Adafruit_NeoPixel(numC, pin_data_C, NEO_GRBW + NEO_KHZ800);


// Potentiometers
Pot r = Pot('r', A0);
Pot g = Pot('g', A1);
Pot b = Pot('b', A2);
Pot w = Pot('w', A3);
Pot in = Pot('i', A4);
Pot out = Pot('o', A6);   /// TO CHANGE!!!!!!! A6 -> A5
Pot s = Pot('s', A5);   /// TO CHANGE!!!!!!!  A5 -> A6

// Lamps
Lamp L1 = Lamp(1, 1, 0*n, n);
Lamp L2 = Lamp(2, 1, 1*n, n);
Lamp L3 = Lamp(3, 1, 2*n, n);
Lamp L4 = Lamp(4, 1, 3*n, n);
Lamp L5 = Lamp(5, 2, 0*n, n);
Lamp L6 = Lamp(6, 2, 1*n, n);
Lamp L7 = Lamp(7, 2, 2*n, n);
Lamp L8 = Lamp(8, 2, 3*n, n);
Lamp L9 = Lamp(9, 3, 0*n, n);
Lamp L10 = Lamp(10, 3, 1*n, n);


void setup() {
  Serial.begin(115200);

  P1.begin();
  P2.begin();
  P3.begin();

  P1.show();
  P2.show();
  P3.show();

}

void loop() {

  in.readPot("fast");

  if(in.val < 126) { // static colors
    if(updatePots("static")) {  // change only when pots changes
      updateColors("static");
      updateLamps();
    }
  } else {  // wheel mode
    if(updatePots("fast")) {  // change only when pots changes
      //updateColors("wheel");
      //updateLamps();
    }
  }
    
}


boolean updatePots(const String mode) {
  if(r.changed(mode)||g.changed(mode)||b.changed(mode)||w.changed(mode)) {
    return true;
  } else return false;
}

void debug(const char what) {

  if(what == 'L') {
    L1.debug();
    L2.debug();
    L3.debug();
    L4.debug();
    L5.debug();
    L6.debug();
    L7.debug();
    L8.debug();
    L9.debug();
    L10.debug();
  }
}

