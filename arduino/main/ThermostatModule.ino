
float tempShift = 37.6;                         // temperature shift value
float set_temp = 37.6 - (tempShift - 37.6);     //deg C

#define SetTemp set_temp // [degC] set temperature in DegC


float MinTemp = set_temp - 5;   // [degC] minimum expected temperature (needed for rescaling inputs)
float MaxTemp = set_temp;       // [degC] maximum allowed temperature, over which heater is turned off (needed for rescaling inputs)


#define PID_KP      10     // proportional gain
#define PID_KI      0      // integral gain (set to lower values i.e. 10^-3)
#define PID_KD      0      // derivative gain
const int dt = 500;         // [ms] time constant in milliseconds(controller clock rate = 1/(dt/1000) [Hz])


float previous_error = 0, s_integral = 0;

void thermostatInit() {
  temperatureInit();
  heaterInit();
}

void thermostatLoop() {
  float temperature = temperatureReadValue();
  int heaterValue = controller(temperature);
  heaterWrite(heaterValue);
}

int controller(float value) {
  // Overheat protection
  if (value > MaxTemp) {
    return 0;
  }

  // In range? If in range, maybe turn on LED?
//  bInRange = value >= SetTemp;

  float err = SetTemp - value;

  s_integral += err * dt;

  float s_derivative = (err - previous_error) / dt;
  int heaterNewValue = ((PID_KP * err) + (PID_KI * s_integral) + (PID_KD * s_derivative)) / (MaxTemp - MinTemp) * 1023;

  previous_error = err;
  return constrain(heaterNewValue, 1, 1023);
}
