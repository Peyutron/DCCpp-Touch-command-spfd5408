
void Recepcion() {
   char c;
  while (Serial.available() > 0) {  // while there is data on the serial line
    c = Serial.read();
        Serial.println ("datos <Recibidos: " + c);

    if (c == '<')                    // start of new command
      commandString[0] = 0;
    else if (c == '>'){               // end of new command
      TextParse(commandString);
              Serial.print ("datos Recibidos: ");
              Serial.println (commandString);
    }
    else if (strlen(commandString) < MAX_COMMAND_LENGTH)  // if commandString still has space, append character just read from serial line
      sprintf(commandString, "%s%c", commandString, c); // otherwise, character is ignored (but continue to look for '<' or '>')
  
  }
}
void TextParse(char *com) {

    Serial.print(com[0]);
    Serial.println(F(" command"));


  switch (com[0]) {

    case 't':
      // Locomotoras();
      break;
    case 'f':
      //ejemFunciones();
      break;
      }
}
void Locomotoras(int nReg, int cab, int tSpeed, int tDirection)
{
  byte b[5];                      // save space for checksum byte
  byte nB = 0;

  if (cab>127)
    b[nB++] = highByte(cab) | 0xC0;      // convert train number into a two-byte address

  b[nB++] = lowByte(cab);
  b[nB++] = 0x3F;                        // 128-step speed control byte
  if (tSpeed >= 0)
    b[nB++] = tSpeed + (tSpeed>0) + tDirection * 128;   // max speed is 126, but speed codes range from 2-127 (0=stop, 1=emergency stop)
  else {
    b[nB++] = 1;
    tSpeed = 0;
  }
//datos_obtenidos( cab ,tSpeed, tDirection);
}
