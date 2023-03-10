/////////////////FUNCIONES DE LOS BOTONES/////////////////////////////////
int doFunction() {
#ifdef DEBUG
  Serial.print("Funcion pulsada: F");
  Serial.println(FN[ActiveAddress]);
#endif  
  if (FN[ActiveAddress] <= 4) {

    if (bitRead(LocoFN0to4[ActiveAddress], FN[ActiveAddress]) == 0 ) {
      bitWrite(LocoFN0to4[ActiveAddress], FN[ActiveAddress], 1);
      LocoFN0to4[ActiveAddress] = LocoFN0to4[ActiveAddress] + 16;
    }    else {
      if (bitRead(LocoFN0to4[ActiveAddress], FN[ActiveAddress]) == 1 ) {
        bitWrite(LocoFN0to4[ActiveAddress], FN[ActiveAddress], 0);
        LocoFN0to4[ActiveAddress] = LocoFN0to4[ActiveAddress] - 16;
      }
    }
    doDCCfunction04();
#ifdef DEBUG    
    Serial.print(LocoFN0to4[ActiveAddress], BIN);
    Serial.println(" LocoFN0to4[ActiveAddress] d ");
    Serial.print(LocoFN0to4[ActiveAddress], DEC);
    Serial.println(" LocoFN0to4[ActiveAddress]");
#endif    
  }
  if (FN[ActiveAddress] >= 5 && FN[ActiveAddress] <= 8) {
    FN[ActiveAddress] = FN[ActiveAddress] - 5;
    if (bitRead(LocoFN5to8[ActiveAddress], FN[ActiveAddress]) == 0 ) {
      bitWrite(LocoFN5to8[ActiveAddress], FN[ActiveAddress], 1);
    } else {
      if (bitRead(LocoFN5to8[ActiveAddress], FN[ActiveAddress]) == 1 ) {
        bitWrite(LocoFN5to8[ActiveAddress], FN[ActiveAddress], 0);
      }
    }
    doDCCfunction58();
#ifdef DEBUG    
    Serial.print(LocoFN5to8[ActiveAddress], BIN);
    Serial.println(" LocoFN5to8[ActiveAddress] d ");
    Serial.print(LocoFN5to8[ActiveAddress], DEC);
    Serial.println(" LocoFN5to8[ActiveAddress]");
#endif    
  }
  if (FN[ActiveAddress] == 10)
  {
    FN[ActiveAddress] = 0;
    LocoFN0to4[ActiveAddress] = B00000000; //clear variables for which functions are set
    LocoFN5to8[ActiveAddress] = B00000000;
    doDCCfunction04();
    doDCCfunction58();
    delay(500);
    FN[ActiveAddress] = 0;
  }
  Serial.println();
}
///////////////////////INTRODUCIR DIRECCION DE LOCOMOTORA//////////////////
void getLocoAddress() {
  Serial.print("<0>");// power off to DCC++ unit
  int total = 0;
  lblVel(total, ROJO);
  int  counter = 0;

  //if (debug == 1) Serial.println(" @ top");
  do {
    tecladoNumerico = true;
    pulsacion();
    DetectButtons();

    if (key ==  12) {
      ActiveAddress = ActiveAddress - 1;
      tecladoNumerico = false;
      showGrid(NEGRO);
      break;
    }
    if (total == 0) {
      for (int tempx = 1; tempx <= counter; tempx++) {
        lblVel (nVel = 0000, ROJO);
      }
    }
    if (key >= 0 && key <= 9) {
#ifdef DEBUG
      Serial.print("Key ");
      Serial.println(key);
#endif
      counter++;
      int number =  key; //- 48;
      total = total * 10 + number;
#ifdef DEBUG
      Serial.print("TOTAL= ");
      Serial.println(total);
      //lblVel(total, ROJO);

      Serial.print("Counter= ");
      Serial.print(counter);
      Serial.print("  key= ");
      Serial.print(key);
      Serial.print("   val= ");
      Serial.println(number);
#endif      
    } lblVel(total, ROJO);
  }
  while (counter <= 3); // COGEMOS 4 DIGITOS
  LocoAddress[ActiveAddress] = total;

  saveAddresses();
  getAddresses();
  showLblLocAdd();  // LABEL LOCOMOTORAS
  lblVel(nVel, NEGRO);
  showGrid(NEGRO);
}
///////////////////////ENVIA LOS DATOS DCC LOCOMOTORAS//////////////////
void doDCC() {
  Serial.print("d = ");
#ifdef DEBUG
  Serial.println(LocoDireccion[ActiveAddress] );
  Serial.print("<1>");
#endif
  Serial.print("<t 1 ");
  Serial.print(LocoAddress[ActiveAddress] );//locoID);
  Serial.print(" ");
  Serial.print(LocoSpeed[ActiveAddress] );
  Serial.print(" ");
  Serial.print(LocoDireccion[ActiveAddress] );
  Serial.write(">");
  Serial.println();

}
///////////////////////ENVIA LOS DATOS DCC FN0 A FN4//////////////////
void doDCCfunction04() {
  Serial.write("<f ");
  Serial.print(LocoAddress[ActiveAddress] );
  Serial.print(" ");
  int fx = LocoFN0to4[ActiveAddress] + 128;
  Serial.print(fx);
  Serial.print(">");

  /*  Serial.write("<f ");
    Serial.print(LocoAddress[ActiveAddress] );
    Serial.print(" ");
    fx = LocoFN0to4[ActiveAddress] + 128;
    Serial.print(fx);
    Serial.print(">");*/
}
///////////////////////ENVIA LOS DATOS DCC FN5 A FN8//////////////////
void doDCCfunction58() {
  Serial.write("<f ");
  Serial.print(LocoAddress[ActiveAddress] );
  Serial.print(" ");
  int fx = LocoFN5to8[ActiveAddress] + 176;
  Serial.print(fx);
  Serial.print(">");
}
/*/////////////////////////////REVISAR PARA LOS CAMBIOS DE DIRECCION///////////////////
  void all2ZeroSpeeed() {  // set flag to 1 to stop, set to 0 to restore
  for (int tempx = 0; tempx <= maxLocos; tempx++) {
    Serial.print("<t1 ");
    Serial.print(LocoAddress[tempx] );//locoID);
    Serial.print(" ");
    if (ZeroSpeedFlag == 1) {
      Serial.print(0);//LocoSpeed[0] );
    }
    else Serial.print(LocoSpeed[0] );
    Serial.print(" ");
    Serial.print(LocoDireccion[1] );
    Serial.write(">");
  }
  }*/
///////////////////////COGE LA DIRECCION DE LA LOCOMOTORA////////////////
void getAddresses() {
  int xxx = 0;
  int showPos = 1;

  for (int xyz = 0; xyz <= maxLocos - 1; xyz++) {
    LocoAddress[xyz] = EEPROM.read(xyz * 2) * 256;
    LocoAddress[xyz] = LocoAddress[xyz] + EEPROM.read(xyz * 2 + 1);
    if (LocoAddress[xyz] >= 10000) LocoAddress[xyz] = 3;
    btnTitleLocAdd[showPos] = LocoAddress[xyz];

    /*  if (debug == 1) Serial.println(" ");
      if (debug == 1) Serial.print("loco = ");
      if (debug == 1) Serial.print(LocoAddress[xyz]);
      if (debug == 1) Serial.print("  address# = ");
      if (debug == 1) Serial.print(xyz + 1);
      if (debug == 1) Serial.print(" showPos: ");
      if (debug == 1) Serial.print(showPos);*/

    showPos = showPos + 3 ;
  }
#ifdef DEBUG
  Serial.println(F(" "));
#endif
}
//////////////////////GUARDA LOS DATOS EN LA MEMORIA EEPROM////////////
void saveAddresses() {
  int xxx = 0;
  for (int xyz = 0; xyz <= maxLocos - 1; xyz++) {
    xxx = LocoAddress[xyz] / 256;
    /* if (debug == 1) Serial.println(" ");
      if (debug == 1) Serial.print("loco = ");
      if (debug == 1) Serial.print(LocoAddress[xyz]);
      if (debug == 1) Serial.print("  address# = ");
      if (debug == 1) Serial.print(xyz);
      if (debug == 1) Serial.print(" msb ");
      if (debug == 1) Serial.print(xxx);
      if (debug == 1) Serial.print(" writing to ");
      if (debug == 1) Serial.print(xyz * 2);
      if (debug == 1) Serial.print(" and ");
      if (debug == 1) Serial.print(xyz * 2 + 1);*/
    EEPROM.write(xyz * 2, xxx);
    xxx = LocoAddress[xyz] - (xxx * 256);
#ifdef DEBUG
    Serial.print(" lsb ");
    Serial.print(xxx);
#endif
    EEPROM.write(xyz * 2 + 1, xxx);
  }
  tecladoNumerico = false;
}
///////////////////////ESTABLECER VELOCIDAD DE LA LOCOMOTORA//////////////////
void BarraVelocidad() {
  if (touchPercent[ActiveAddress] != LastPercent[ActiveAddress]) {

    while (touchPercent[ActiveAddress] < LastPercent[ActiveAddress]) { //BAJAR VELOCIDAD
      unsigned long currentMillis = millis();
      if (currentMillis -  MillisBajada > 20) {
        MillisBajada = currentMillis;

        newPercent[ActiveAddress] = LastPercent[ActiveAddress];
        newPercent[ActiveAddress] = newPercent[ActiveAddress] - 1;
        nVel = map ( newPercent[ActiveAddress], 0, 200, 0, 127);

        drawBar(newPercent[ActiveAddress]);
        lblVel(nVel, NEGRO);

        if (nVel <= 3) nVel = 0; // PONE A 0 CUANDO SE ACERCA A CERO
        // LocoSpeed[ActiveAddress] =  nVel;
        // doDCC();  //ENVIA LOS DATOS DCC
      }
    }
    
    while (touchPercent[ActiveAddress] > LastPercent[ActiveAddress]) {  //SUBIR VELOCIDAD
      unsigned long currentMillis = millis();
      if (currentMillis -  MillisSubida > 20) {
        MillisSubida = currentMillis;

        newPercent[ActiveAddress] = LastPercent[ActiveAddress];
        newPercent[ActiveAddress] = newPercent[ActiveAddress] + 1;
        nVel = map ( newPercent[ActiveAddress], 0, 200, 0, 127);

        drawBar(newPercent[ActiveAddress]);
        lblVel(nVel, NEGRO);

        if (nVel >= 127) nVel = 127; // SI EL VALOR SUPERA LA VARIABLE 127
        // LocoSpeed[ActiveAddress] =  nVel;
        // doDCC();  //ENVIA LOS DATOS DCC
      }
    }
        LocoSpeed[ActiveAddress] =  nVel;
        Serial.println(nVel);
        doDCC();  //ENVIA LOS DATOS DCC
  }
}
