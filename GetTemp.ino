float GetTemp (float Resistance){
  //Beta parameter equation, measured in kelvin
  // float T36 = B/(ln(R/r_infinity))    Where B = 3950K (from product data sheet), R = measured resistance, and r_infinity = R_0e^(-B/T_0)
  //where R_0 = resistance at room temperature (10kohm) and T_0 = 298.15K
  float T36K = (3950)/(log(Resistance/0.0176));
  float T36 = T36K - 273.15;
  return T36;
}