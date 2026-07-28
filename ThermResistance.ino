float ThermResistance (float resistor1){
  float reading = analogRead(A0);
  
  float reading1 = (1023 / reading)  - 1;     // (1023/ADC - 1) 
  float Resistance = resistor1 / reading1;  // 10K / (1023/ADC - 1)
  return Resistance;
  
  }