// Update Lamps

void updateLamps() {

  Lamp L = L1;
  
  // Lamp A
  for(int i=0; i<lampsA; i++) {
    if(i==0) L = L1;
    else if(i==1) L = L2;
    else if(i==2) L = L3;
    else if(i==3) L = L4;
    
    for(int p=L.start; p <=L.last; p++) {
      //Serial.println(p);
      P1.setPixelColor(p, P1.Color(L.r, L.g, L.b, L.w));
      P1.setPixelColor(L.len-1-p, P1.Color(L.r, L.g, L.b, L.w));
    }
  }

  // Lamp B
  for(int i=0; i<lampsB; i++) {
    if(i==0) L = L5;
    else if(i==1) L = L6;
    else if(i==2) L = L7;
    else if(i==3) L = L8;
    
    for(int p=L.start; p <=L.last; p++) {
      //Serial.println(p);
      P2.setPixelColor(p, P2.Color(L.r, L.g, L.b, L.w));
      P2.setPixelColor(L.len-1-p, P2.Color(L.r, L.g, L.b, L.w));
    }
  }

  // Lamp C
  for(int i=0; i<lampsC; i++) {
    if(i==0) L = L9;
    else if (i==1) L = L10;

    for(int p=L.start; p <=L.last; p++) {
      //Serial.println(p);
      P3.setPixelColor(p, P3.Color(L.r, L.g, L.b, L.w));
      P3.setPixelColor(L.len-1-p, P3.Color(L.r, L.g, L.b, L.w));
    }
  }

  P1.show();
  P2.show();
  P3.show();
  
}

// change colors for lamps
void updateColors(const String mode) {
  Lamp L = L1;
  if(mode.equals("static")) {
    L1.updateCol(r.val, g.val, b.val, w.val);
    L2.updateCol(r.val, g.val, b.val, w.val);
    L3.updateCol(r.val, g.val, b.val, w.val);
    L4.updateCol(r.val, g.val, b.val, w.val);
    L5.updateCol(r.val, g.val, b.val, w.val);
    L6.updateCol(r.val, g.val, b.val, w.val);
    L7.updateCol(r.val, g.val, b.val, w.val);
    L8.updateCol(r.val, g.val, b.val, w.val);
    L9.updateCol(r.val, g.val, b.val, w.val);
    L10.updateCol(r.val, g.val, b.val, w.val);
  }
}
