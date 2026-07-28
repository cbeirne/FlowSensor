void SerialPrint(DateTime now, float Flow, float T36C, float photo, float PVoltage){
  //Serial print time
  Serial.print(now.year(), DEC);
  Serial.print(',');
  Serial.print(now.month(), DEC);
  Serial.print(',');
  Serial.print(now.day(), DEC);
  Serial.print(',');
  Serial.print(now.hour(), DEC);
  Serial.print(',');
  Serial.print(now.minute(), DEC);
  Serial.print(',');
  Serial.print(now.second(), DEC);
  Serial.print(',');
 //Temperature
  // Serial.print("TResistance: ");
  // Serial.print(Resistance);
  // Serial.print(",");
  Serial.print(T36C); 
  Serial.print(',');
 //myFile.print(TK);   //Calibrated temperature (in kelvin)
  //Serial.print(',');
  //Flow
  Serial.print(Flow);
  Serial.print(',');
  // //Serial.print(Flow)  //Calibrated flow (L/s)
  // //Serial.print(',');
  // //Photoresistor
  // Serial.print(Photo);
  Serial.print(photo);
  Serial.print(',');
  // Serial.print(PC);
  // Serial.print(',');
  Serial.print(PVoltage);
  // Serial.print(',');
  // Serial.print(Resistance);
  Serial.print("\n");
}