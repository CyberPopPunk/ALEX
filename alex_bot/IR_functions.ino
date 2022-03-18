// Major thanks to Jeff_Hass for decoding these signals for this remote. 
//See their post on the Arduino forum here: https://forum.arduino.cc/t/radio-shack-make-it-robot-remote-control/931260

//This file contains the functions for interacting with Infrared using the RadioShack Make:It Robot Remote Control

void translateIR() // takes action based on IR code received
{
  switch (IrReceiver.decodedIRData.decodedRawData)  // Uses .decodedRawData to interpret hash values
  {
    case 0x962814CA:
      Serial.println("Up"); 
      lookStraight();
      break;
    case 0x5990708A:  Serial.println("Down"); bow(); break;
    case 0xB2CC429A:  Serial.println("Left"); turnRight(); break;
    case 0xB012615A:  Serial.println("Right"); turnLeft(); break;
    case 0x8D2A4BAF:  Serial.println("Forward"); nod(200); break;
    case 0x1C22DE05:  Serial.println("Reverse"); sadFace(); break;
    case 0x7A6E10BA:  Serial.println("SW 7"); scared(); break;
    case 0x97123E8A:  Serial.println("SW 8"); headBack(200); break;

    default: Serial.println("Other button");  // Some buttons trigger this - bad reads?  Who knows.
  }
  delay(100);
}

void IRpolling(){
  if (IrReceiver.decode()) // have we received an IR signal?
  {
    translateIR();

    for (int z = 0; z < 2; z++) // ignore 2nd and 3rd signal repeat
    {
      IrReceiver.resume(); // receive the next value
    }
  }
  else {
    // FOR FUTURE UPDATE:
    //check timer
    ////if 10 sec passed since timer started
    //////start random behavior mode
  }
}