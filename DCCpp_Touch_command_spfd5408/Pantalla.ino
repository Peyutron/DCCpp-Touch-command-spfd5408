////////////////////DIBUJA CABECERA DE TITULO////////////////////////////////////////////
void showHeader() {
  if (alimentacion == false) {
    tft.fillRect(0, 0, tft.width(), 20, ROJO);
    tft.setCursor (45, 7);
    tft.setTextColor(VERDE);
  } else {
    tft.fillRect(0, 0, tft.width(), 20, VERDE);
    tft.setCursor (45, 7);
    tft.setTextColor(NEGRO);
  }
  tft.setTextSize(1);
  tft.println("<<< DCC Touch Command >>>");
}
////////////////////DIBUJA BOTON DE POWER HELP Y PARADA DE EMERGENCIA////////////////////////////////////////////
void showPowerButton() {
  ///////////////////////////////////////////BOTON HELP
  tft.fillRoundRect(5, 65, 25, 25, 5, GRIS);
  tft.setTextSize(1);
  tft.setCursor (6, 74);
  tft.setTextColor(NEGRO);
  tft.println("Help");
  if (alimentacion == true) {
    ///////////////////////////////////////////BOTON PARADA DE EMERGENCIA
    tft.fillRoundRect(5, 200, 25, 25, 5, ROJO);
    tft.setTextColor(NEGRO);
  } else {
    tft.fillRoundRect(5, 200, 25, 25, 5, BLANCO);
    tft.setTextColor(BLANCO);
  }
  tft.setTextSize(1);
  tft.setCursor (6, 209);
  tft.println("STOP");
  ///////////////////////////////////////////BOTON ON/OFF
  tft.setTextSize(2);
  if (alimentacion == false) {
    tft.fillRoundRect(5, 30, 25, 25, 5, ROJO);
    tft.setCursor (12, 36);
    tft.setTextColor(VERDE);
    tft.println("I");

  } else {
    tft.fillRoundRect(5, 30, 25, 25, 5, VERDE);
    tft.setCursor (12, 36);
    tft.setTextColor(ROJO);
    tft.println("O");
  }
}
///////////////////////////////TECLADO DE FUNCIONES///////////////////////
void showGrid(int color)
{
  tft.setTextSize(2);
  uint16_t width = tft.width() - 1;
  uint16_t height = tft.height() - 1;
  int left, top;
  int l = 105;   //  ANCHO EMPIEZA A DIBUJAR LOS BOTONES
  int t = 24;   //  ALTO  EMPIEZA A DIBUJAR LOS BOTONES
  int w = 40;   //  ANCHO DEL BOTON
  int h = 40;   //  LARGO DEL BOTON
  int hgap = 5;//  ALTO SEPARACION ENTRE BOTONES
  int vgap = 5; //  ANCHO SEPARACION ENTRE BOTONES
  int idColor[4] = {0};
  int id = 0;
  //  funcion[ActiveAddress] = 1;
  funcion = 1;
  for (int j = 0; j < row; j++) {
    for (int i = 0; i < col; i++) {
      left = l + i * (w + vgap);
      top = t + j * (h + hgap);
      tft.setTextColor (color);
    /*  Serial.print("direccion activa:");
      Serial.print(ActiveAddress);
      Serial.print(funcion);
      Serial.println(FNLastActive[funcion][ActiveAddress]);*/
      tft.setTextColor(color);
      if ( tecladoNumerico == false ) {
        if  ((FNLastActive[funcion][ActiveAddress] == 1) && ( tecladoNumerico == false )) {
          tft.setTextColor(VERDE);
        } else {
          tft.setTextColor(color);
        }
      }
      tft.fillRoundRect( left, top, w, h, 10, GRIS);  //BOTONES CON BORDE ROJOONDEADO
      tft.setCursor(left + 5, top + 10);  //  POSICION DE LOS NUMEROS EN LOS BOTONES
      tft.setCursor(left + (w / 2) - 10, top + (h / 2) - 8); //  POSICION DE LOS NUMEROS EN LOS BOTONES
      tft.print(btnTitle[id]);  //  IMPRIME LOS NUMEROS EN LOS BOTONES
      tft.setTextColor (color);
      //funcion[ActiveAddress]++;
      funcion++;
      id++;

    }
  }
}
//////////////////////////////LABEL DE LOCOMOTORAS//////////////////////
void showLblLocAdd()
{
  int locPos;// 
  int infoPos; //
  locPos = ActiveAddress;// +1; // ActiveAddress;
  infoPos = ActiveAddress;// +1; // ActiveAddress;
  tft.setTextSize(1);
  uint16_t width = tft.width() - 1;
  uint16_t height = tft.height() - 1;
  int left, top;
  int l = 105;   //  ANCHO EMPIEZA A DIBUJAR LOS BOTONES
  int t = 202;   //  ALTO  EMPIEZA A DIBUJAR LOS BOTONES
  int w = 40;   //  ANCHO DEL BOTON
  int h = 15;   //  LARGO DEL BOTON
  int vgap = 1; //  ANCHO SEPARACION ENTRE BOTONES
  int hgap = 1; //  ALTO SEPARACION ENTRE BOTONES
  int id2 = 0;
  switch (locPos) {
    case 0:
      if (alimentacion == true) {
        tft.fillRoundRect( l, t, w + 90, h, 2, VERDE);  //BOTONES CUDRADOS
      } else {
        tft.fillRoundRect( l, t, w + 90, h, 2, ROJO);  //BOTONES CUDRADOS
      }
      tft.fillRoundRect( l, t + 48, w + 90, h, 2, BLANCO);  //BOTONES CUDRADOS
      break;
    case 1:
      if (alimentacion == true) {
        tft.fillRoundRect( l, t + 16, w + 90, h, 2, VERDE);  //BOTONES CUDRADOS
      } else {
        tft.fillRoundRect( l, t + 16, w + 90, h, 2, ROJO);  //BOTONES CUDRADOS
      }
      tft.fillRoundRect( l, t, w + 90, h, 2, BLANCO);  //BOTONES CUDRADOS
      break;
    case 2:
      if (alimentacion == true) {
        tft.fillRoundRect( l, t + 32, w + 90, h, 2, VERDE);  //BOTONES CUDRADOS
      } else {
        tft.fillRoundRect( l, t + 32, w + 90, h, 2, ROJO);
      }
      tft.fillRoundRect( l, t + 16, w + 90, h, 2, BLANCO);  //BOTONES CUDRADOS
      break;
    case 3:      if (alimentacion == true) {
        tft.fillRoundRect( l, t + 48, w + 90, h, 2, VERDE);  //BOTONES CUDRADOS
      } else {
        tft.fillRoundRect( l, t + 48, w + 90, h, 2, ROJO);
      }
      tft.fillRoundRect( l, t + 32, w + 90, h, 2, BLANCO);  //BOTONES CUDRADOS
      break;
    default:
      if (alimentacion == true) {
        tft.fillRoundRect( l, t, w + 90, h, 2, VERDE);  //BOTONES CUDRADOS
      } else {
        tft.fillRoundRect( l, t, w + 90, h, 2, ROJO);  //BOTONES CUDRADOS
      }
      tft.fillRoundRect( l, t + 48, w + 90, h, 2, BLANCO);  //BOTONES CUDRADOS
      break;
  }
  for (int j = 0; j < rowLocAdd; j++) {
    for (int i = 0; i < colLocAdd; i++) {
      left = l + i * (w + vgap);
      top = t + j * (h + hgap);
      tft.setTextColor(NEGRO);
      //tft.fillRect( left, top, w, h, BLANCO);  //BOTONES CUDRADOS
      tft.setCursor(left, top + 5);  //  POSICION DE LOS NUMEROS EN LOS BOTONES
      tft.setCursor(left + (w / 2) - 12, top + (h / 2) - 3); //  POSICION DE LOS NUMEROS EN LOS BOTONES
      tft.print(btnTitleLocAdd[id2]);  //  IMPRIME LOS NUMEROS EN LOS BOTONES
      id2++;
    }
  }
}
void paradaEmer() {

}
////////////////////BOTONES DE DIRECCION Y STOP/////////////////////////
void showButtonsDir()
{
  tft.setTextSize(2);
  uint16_t width = tft.width() - 1;
  uint16_t height = tft.height() - 1;
  int left;
  int top = 268; //  ALTO  EMPIEZA A DIBUJAR LOS BOTONES
  int l = 10;   //  ANCHO EMPIEZA A DIBUJAR LOS BOTONES
  int w = 70;   //  ANCHO DEL BOTON
  int h = 45;   //  LARGO DEL BOTON
  int vgap = 5; //  ANCHO SEPARACION ENTRE BOTONES
  int id1 = 0;
  for (int i = 0; i < colDir; i++) {
    left = l + i * (w + vgap);
    tft.setTextColor(NEGRO);
    tft.fillRoundRect( left, top, w, h, 15, GRIS);  //BOTONES CON BORDE ROJOONDEADO
    tft.setCursor(left, top + 10);  //  POSICION DE LOS NUMEROS EN LOS BOTONES
    tft.setCursor(left + (w / 2) - 22, top + (h / 2) - 5); //  POSICION DE LOS NUMEROS EN LOS BOTONES
    if  (alimentacion == 1) {
      if ((LocoDireccion[ActiveAddress] == 1) && (i == 2)) {
        tft.setTextColor(VERDE);
      }
      if ((LocoDireccion[ActiveAddress] == 0) && (i == 0)) {
        tft.setTextColor(VERDE);
      }
    }
    tft.print(btnTitleDir[id1]);  //  IMPRIME LOS NUMEROS EN LOS BOTONES
    tft.setTextColor(NEGRO);
    id1++;
  }
}

////////////////////DIBUJA LA ESCALA LATERAL IZQUIERDA//////////////////////////////////////////
void drawScale()
{

  tft.drawFastHLine(34, 26, 10, ROJO); // Major Division
  tft.drawFastHLine(33, 76, 7, ROJO); // Minor Division
  tft.drawFastHLine(34, 126, 10, AMARILLO); // Major Division
  tft.drawFastHLine(33, 176, 7, VERDE); // Minor Division
  tft.drawFastHLine(33, 225, 10, VERDE); // Division grande

  tft.drawFastVLine(33, 26, 76, ROJO ); // Vertical Scale Line ANCHO/ALTO/LARGO
  tft.drawFastVLine(33, 77, 126, AMARILLO ); // Vertical Scale Line ANCHO/ALTO/LARGO
  tft.drawFastVLine(33, 127, 98, VERDE); // Vertical Scale Line ANCHO/ALTO/LARGO
}
////////////////////DIBUJA LA BARRA DE VELOCIDAD////////////////////////////////////////////
void drawBar (int nPer)
{
  //  if

  if (nPer < LastPercent[ActiveAddress]) {

    tft.fillRect(45, 27 + (200 - LastPercent[ActiveAddress]), 30, LastPercent[ActiveAddress] - nPer,  BLANCO); //ANCHO, BLANCO
  }
  else {
    barColor = VERDE; //  VERDE
    if (nPer > 100) {
      barColor = AMARILLO; //  AMARILLO
    }
    if (nPer > 150) {
      barColor = ROJO; //  ROJO
    }
    tft.fillRect(45, 27 + (200 - nPer), 30, nPer - LastPercent[ActiveAddress], barColor); //VERDE
  }
  LastPercent[ActiveAddress] = nPer;
  // return;
}
/////////////////////////////////LABEL DE VELOCIDAD////////////////////////
void lblVel(int nVel, int color)
{

  int left = 32;
  int top = 230;
  int t = 24;   //  ALTO  EMPIEZA A DIBUJAR LOS BOTONES
  int w = 80;   //  ANCHO DEL BOTON
  int h = 30;   //  LARGO DEL BOTON
  // if (alimentacion == true) {
  tft.fillRect(t, top, w, h, BLANCO);
  //  } else {
  //    tft.fillRect(t, top, w, h, GRIS);
  //  }
  tft.setCursor(left + (w / 2) - 40, top + (h / 2) - 8); //  POSICION DE LOS NUMEROS EN LOS BOTONES
  tft.setTextColor(color);
  tft.setTextSize(3);
  tft.print(nVel);
}
/////////////////////////////////////DIBUJA EL BORDE////////////////////////////////////////////
void drawBorder () {

  uint16_t width = tft.width() - 1;
  uint16_t height = tft.height() - 1;
  uint8_t border = 2;
  if (alimentacion == false) {
    tft.fillScreen(ROJO);
    tft.fillRect(border, border, (width - border * 2), (height - border * 2), BLANCO);
  } else {
    tft.fillScreen(VERDE);
    tft.fillRect(border, border, (width - border * 2), (height - border * 2), BLANCO);
  }
}
