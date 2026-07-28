//make a filename using time stamp (limited to 8 characters plus extension)
//name format is MMDDHHNN.CSV (no year or seconds)
//assumes fname is a global variable and rtc is globally defined
void makefname()
{
  DateTime now = rtc.now();  //Get the time
  // uint16_t year = now.year();
  uint8_t month = now.month();
  uint8_t day = now.day();
  uint8_t hour = now.hour();
  uint8_t minute = now.minute();
  // uint8_t second = now.second();

  // char YYYY[5];
  char MM[3];
  char DD[3];
  char HH[3];
  char NN[3];
  // char SS[3];

  // sprintf(YYYY,"%04d",year);
  sprintf(MM,"%02d",month);
  sprintf(DD,"%02d",day);
  sprintf(HH,"%02d",hour);
  sprintf(NN,"%02d",minute);
  // sprintf(SS,"%02d",second);


  strcpy(fname,MM);   //strcpy for first entry
  strcat(fname,DD);
  strcat(fname,HH);
  strcat(fname,NN);
  // strcat(fname,SS);
  strcat(fname,".csv");

  return fname;
}