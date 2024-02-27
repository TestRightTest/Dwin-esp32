
#define TEMPERATURE_SDA_PIN         33
#define TEMPERATURE_SCL_PIN         32

#define ADS1115_I2C_ADDR            0x48

#define Rt0                         100000   // O

const float t0 = 298.15;  //Temperature   t0 from datasheet, conversion from Celsius to kelvin


Adafruit_ADS1115 adsTemp; // 0X48
TwoWire I2Ctwo = TwoWire(1);

void temperatureInit()
{
  I2Ctwo.begin(TEMPERATURE_SDA_PIN, TEMPERATURE_SCL_PIN, 100000);

  // Initialize each ADS1115 on the main I2C bus
  if (!adsTemp.begin(ADS1115_I2C_ADDR, &I2Ctwo)) {
    fatal("Failed to begin temperature module");
  }

  adsTemp.setGain(GAIN_ONE);
}

float rawValueToCelsius(double VRT) {

#define VCC         3.29        // Supply   voltage
#define ADCmax      26287       // TempADC maxvalue at VCC input

  VRT   = (VRT / ADCmax) * VCC;      // Conversion to voltage 26255
  float VR = VCC - VRT;
  float RT = VRT / (VR / R);               // Resistance of RT
  float ln = log(RT / Rt0);
  double Temp = (1 / ((ln / B) + (1 / t0))); // Temperature from thermistor
  Temp = Temp - 273.15;
  
  return static_cast<float>(Temp);
}

float temperatureReadValue() {
  uint16_t rawValue = adsTemp.readADC_SingleEnded(0); // Raw Value
  return rawValueToCelsius(static_cast<double>(rawValue)); //adc to Celcius
}
