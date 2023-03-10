void DetectButtons()
{
  int espera = 300;
  if (alimentacion == true) {
    if (p.x > 110 && p.x < 145) //DETECTA LOS BOTONES DEL TECLADO 3X4
    {
      if (p.y > 31 && p.y < 68) ///////////////////////////////////////SI EL BOTON F1 ESTA PRESIONADO
      { delay (espera);
        if (tecladoNumerico == true) {
          key = 1;
        } else {
          funcion = 1 ;
          FN[ActiveAddress] = 1;
          funciones();
        }
      }
      if (p.y > 68 && p.y < 114) ///////////////////////////////////////SI EL BOTON F4 ESTA PRESIONADO
      { delay (espera);
        if (tecladoNumerico == true) {
          key = 4;
        } else {
          funcion = 4;
          FN[ActiveAddress] = 4;
          funciones();
        }
      }

      ////////////////////////////////////////SI EL BOTON F7 ESTA PRESIONADO
      if (p.y > 114 && p.y < 160)
      { delay (espera);
        if (tecladoNumerico == true) {
          key = 7;
        } else {
          funcion = 7;
          FN[ActiveAddress] = 7;
          funciones();
        }
      }
      ///////////////////////////////////////SI EL BOTON * ESTA PRESIONADO
      if (p.y > 160 && p.y < 205)
      { delay(espera);
        Serial.println ("*");
        if (tecladoNumerico == true) {
          key = 11;
        } else {
          tecladoNumerico = true;
          showGrid(ROJO);
          //all2ZeroSpeeed();
          getLocoAddress();
        }
      }
    }
    if (p.x > 145 && p.x < 190) // FILA 2 DETECTA LOS BOTONES DEL TECLADO 3X4
    {
      ///////////////////////////////////////SI EL BOTON F2 ESTA PRESIONADO
      if (p.y > 31 && p.y < 68)
      { delay (espera);
        if (tecladoNumerico == true) {
          key = 2;
        } else {
          funcion = 2;
          FN[ActiveAddress] = 2;
          funciones();
        }
      }
      ///////////////////////////////////////SI EL BOTON F5 ESTA PRESIONADO
      if (p.y > 68 && p.y < 114)
      { delay (espera);
        if (tecladoNumerico == true) {
          key = 5;
        } else {
          funcion = 5;
          FN[ActiveAddress] = 5;
          funciones();
        }
      }
      ///////////////////////////////////////SI EL BOTON F8 ESTA PRESIONADO
      if (p.y > 114 && p.y < 160)
      { delay (espera);
        if (tecladoNumerico == true) {
          key = 8;
        } else {
          funcion = 8;
          FN[ActiveAddress] = 8;
          funciones();
        }
      }
      ///////////////////////////////////////SI EL BOTON F0 ESTA PRESIONADO
      if (p.y > 160 && p.y < 205)
      { delay (espera);
        if (tecladoNumerico == true) {
          key = 0;
        } else {
          funcion = 11;
          FN[ActiveAddress] = 0;
          funciones();
        }
      }
    }

    if (p.x > 190 && p.x < 235) // FILA 3 DETECTA LOS BOTONES DEL TECLADO 3X4
    {
      ///////////////////////////////////////SI EL BOTON F3 ESTA PRESIONADO
      if (p.y > 31 && p.y < 68)
      { delay (espera);
        if (tecladoNumerico == true) {
          key = 3;
        } else {
          funcion = 3;
          FN[ActiveAddress] = 3;
          funciones();
        }
      }
      ///////////////////////////////////////SI EL BOTON F6 ESTA PRESIONADO
      if (p.y > 68 && p.y < 114)
      { delay (espera);
#ifdef DEBUG
        Serial.println (F("F6"));
#endif
        if (tecladoNumerico == true) {
          key = 6;
        } else {
          funcion = 6;
          FN[ActiveAddress] = 6;
          funciones();
        }
      }
      ///////////////////////////////////////SI EL BOTON F9 ESTA PRESIONADO
      if (p.y > 114 && p.y < 160)
      { delay (espera);
        if (tecladoNumerico == true) {
          key = 9;
        } else {
          funcion = 9;
          FN[ActiveAddress] = 9;
          funciones();
        }
      }
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////SI EL BOTON # ESTA PRESIONADO
      if (p.y > 160 && p.y < 205)
      { delay (espera);
        int showPosVel = 2;
        int x;
#ifdef DEBUG
        Serial.println (F("#"));
#endif
        if (tecladoNumerico == true) {
          key = 12;
        } else {
          /*    if (debug == 1)  Serial.print ("Loco anterior: ");
              if (debug == 1)  Serial.print (ActiveAddress);
              if (debug == 1)  Serial.print (" ");
              if (debug == 1)  Serial.print (LocoSpeed[ActiveAddress]);
              if (debug == 1)  Serial.print (" ");
              if (debug == 1)  Serial.println (LocoDireccion[ActiveAddress]);*/
          ActiveAddress++;                                //INCREMENTA EN 1 LA VARIABLE ACTIVE ADDRESS PARA CAMBIAR DE LOCOMOTORA
          /*  if (debug == 1)  Serial.print ("Loco nueva: ");
              if (debug == 1)  Serial.print (ActiveAddress);
              if (debug == 1)  Serial.print (" ");
              if (debug == 1)  Serial.print (LocoSpeed[ActiveAddress]);
              if (debug == 1)  Serial.print (" ");
              if (debug == 1)  Serial.println (LocoDireccion[ActiveAddress]); */


          if (ActiveAddress >= 4) ActiveAddress = 0;
          tft.fillRect(45, 26, 30, 201,  BLANCO);

          newPercent[ActiveAddress] = LocoSpeed[ActiveAddress];
          lblVel (LocoSpeed[ActiveAddress], NEGRO);

          if ((LocoSpeed[ActiveAddress] >= 0) && (LocoSpeed[ActiveAddress] <= 64)) {
            tft.fillRect(45, 127 , 30, 100,  VERDE);
            tft.fillRect(45, 127 , 30, 100 - LastPercent[ActiveAddress],  BLANCO);
          }
          if ((LocoSpeed[ActiveAddress] >= 65) && (LocoSpeed[ActiveAddress] <= 94)) {
            tft.fillRect(45, 127 , 30, 100,  VERDE);
            tft.fillRect(45, 77 , 30, 50, AMARILLO);
            tft.fillRect(45, 77 , 30, 150 - LastPercent[ActiveAddress],  BLANCO);
          }
          if ((LocoSpeed[ActiveAddress] >= 95) && (LocoSpeed[ActiveAddress] <= 127)) {
            tft.fillRect(45, 127 , 30, 100,  VERDE);
            tft.fillRect(45, 77 , 30, 50, AMARILLO);
            tft.fillRect(45, 26 , 30, 50, ROJO);
            tft.fillRect(45, 26 , 30, 201 - LastPercent[ActiveAddress],  BLANCO);
          }
          /////GUARDA LOS DATOS DE VELOCIDAD Y DIRECCION EN showButtonsLocAdd() FILA 3
          for (int xyz = 0; xyz <= maxLocos - 1; xyz++) {
            if (LocoDireccion[xyz] == 0 ) btnInfo1[xyz] = String ("<");
            if (LocoDireccion[xyz] == 1 ) btnInfo1[xyz] = String (">");
            btnInfo2[xyz] = LocoSpeed[xyz], DEC;
            btnInfo[xyz] = btnInfo1[xyz] + btnInfo2[xyz];
            //   Serial.println ("INFO: ");
            //   Serial.println ( btnInfo[xyz]);

            btnTitleLocAdd[showPosVel] = btnInfo[xyz];
            showPosVel = showPosVel + 3 ;
            //  Serial.println (showPosVel);
          }
          showLblLocAdd();  // LABEL LOCOMOTORAS
          /*   if (debug == 1)  Serial.println ("Direccion: ");
             if (debug == 1)  Serial.println (ActiveAddress + 1);
             if (debug == 1) Serial.println (LocoAddress[ActiveAddress]);
             if (debug == 1) Serial.println (LocoSpeed[ActiveAddress]);*/
        }
        showButtonsDir();
        showGrid(NEGRO);
      }
    }
  }

  ///////////////////////////////////DETECTA LOS BOTONES DE DIRECCION
  if (p.y > 280 && p.y < 310)
  {
    if (p.x > 13 && p.x < 83) ///////////////////////////////////////BOTON ATRAS <<
    { delay (espera);
#ifdef DEBUG
      Serial.println (F("<< ATRAS "));
#endif
      LocoDireccion[ActiveAddress] = 0; // ATRAS
      dire[ActiveAddress] = "<";
      showButtonsDir(); //BOTONES DE DIRECCION
      doDCC();  //ENVIA LOS DATOS DCC
    }
    if (p.x > 83 && p.x < 160) ///////////////////////////////////////BOTON STOP
    {
#ifdef DEBUG
      Serial.println (F("STOP"));
#endif
      touchPercent[ActiveAddress] = 0;
      LocoSpeed[ActiveAddress] = 0;
      drawBar(0);
      lblVel(0, NEGRO);
      showButtonsDir(); //BOTONES DE DIRECCION
      doDCC();  //ENVIA LOS DATOS DCC
    }
    if (p.x > 160 && p.x < 235) ///////////////////////////////////////BOTON AVANCE >>
    { delay (espera);
#ifdef DEBUG
      Serial.println (F("AVANCE >>"));
#endif
      dire[ActiveAddress] = ">";
      LocoDireccion[ActiveAddress] = 1;
      showButtonsDir();
      doDCC();  //ENVIA LOS DATOS DCC
    }
  }
  if (alimentacion == true) {
    if (p.y > 35 && p.y < 250) //DETECTA PULSACION EN LA BARRA DE VELOCIDAD
    {
      if (p.x > 38 && p.x < 90) // Barra velocidad
      { int barraMin = 0;
        int barraMax = 200;
        int barra = map(p.y, 240, 40, 0, 200);
        touchPercent[ActiveAddress] = constrain (barra , 0, 201);
#ifdef DEBUG
        Serial.println (barra);
        Serial.println (touchPercent[ActiveAddress]);
#endif
      }
    }
  }
  if (p.x > 5 && p.x < 40) //DETECTA PULSACION EN BOTON POWER
  {
    if (p.y > 40 && p.y < 75) ///////////////////////////////////////BOTON POWER////////
    { delay(espera);
      newAlimentacion = 1;
      if ((newAlimentacion) != (lastAlimentacion)) {
        newAlimentacion = lastAlimentacion;
        alimentacion = !alimentacion;
        if (alimentacion == true) {
          alimentacion = true;
          //    Serie2.print("<1>");// power off to DCC++ unit
          //    delay(espera);
          //    Serial.println("power on");
          drawBorder ();
          if (LocoSpeed[ActiveAddress] == 0) {
            lblVel(0, NEGRO);
          } else {
            newPercent[ActiveAddress] = LocoSpeed[ActiveAddress];
            LastPercent [ActiveAddress] = 0;
          }
          Serial.print("<1>");// ENCIENDE LA UNIDAD DCC++
          //   delay(espera);
#ifdef DEBUG
          Serial.println(F("Encendido"));
#endif
        } else {
          alimentacion = false;
          drawBorder ();
          lblVel(LocoSpeed[ActiveAddress], BLANCO);
          Serial.print("<0>");// APAGA LA UNIDAD DCC++
          //       delay(espera);
#ifdef DEBUG
          Serial.println(F("Apagado"));
#endif
        }
      }
      showHeader();
      showPowerButton();
      showGrid(NEGRO);
      showButtonsDir(); // BOTONES DE DIRECCION
      showLblLocAdd();  // LABEL LOCOMOTORAS
      drawScale();      // DIBUJA LA ESCALA DE VELOCIDADES
    }
    if (p.y > 86 && p.y < 105) ///////////////////////////////////////BOTON INFORMACION////////
    { delay(espera);
#ifdef DEBUG
      Serial.println(F("INFORMACION"));
#endif
      //for (int x = 0; x <= 5; x++){
      //Serie2.print ("<s>");
      // }
    }
  }
}

void funciones() {
  FNActive[funcion][ActiveAddress] = 1;
  if (FNActive[funcion][ActiveAddress] != FNLastActive [funcion][ActiveAddress]) {

    /*    Serial.print(ActiveAddress);
        Serial.print(funcion);
        Serial.print(FNLastActive[funcion][ActiveAddress]);*/
    FNLastActive[funcion][ActiveAddress] = FNActive [funcion][ActiveAddress];
  } else {

    /*  Serial.print(ActiveAddress);
      Serial.print(funcion);
      Serial.print(FNLastActive[funcion][ActiveAddress]);*/
    FNLastActive[funcion][ActiveAddress] = !FNActive[funcion][ActiveAddress];

  }
  showGrid(NULL);
  doFunction(); //COMPRUEBA LA FUNCION
}
