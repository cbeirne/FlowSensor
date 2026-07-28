float PhotoResistance (float resistor1){
 
  float reading2 = analogRead(A2);
  
  float reading3 = (1023 / reading2)  - 1;     // (1023/ADC - 1) 
  float photo = resistor1 / reading3;  // 10K / (1023/ADC - 1)
  return photo;
}