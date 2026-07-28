void FilePrint(DateTime now, float Flow, float T36C, float photo, float PVoltage){
  myFile = SD.open(fname, FILE_WRITE);
  myFile.print(now.year(), DEC);
  myFile.print(", ");
 myFile.print(now.month(), DEC);
  myFile.print(',');
 myFile.print(now.day(), DEC);
  myFile.print(',');
 myFile.print(now.hour(), DEC);
  myFile.print(',');
  myFile.print(now.minute(), DEC);
  myFile.print(',');
 myFile.print(now.second(), DEC);
  myFile.print(',');
  //Temperature
  myFile.print(T36C); 
  myFile.print(',');
  //myFile.print(TK);   //Calibrated temperature (in kelvin)
  //myFile.print(',');
  //Flow
  myFile.print(Flow);
  myFile.print(',');
  //Photoresistor
  // myFile.print(Photo);
  myFile.print(photo);
  myFile.print(',');
  // myFile.print(PC);
  // myFile.print(',');
  myFile.print(PVoltage);
  myFile.print("\n");
  myFile.close();
}