void temperatureInit()
{
  I2Ctwo.begin(SDA_TEMP, SCL_TEMP, 100000);

  // Initialize each ADS1115 on the main I2C bus
  if (!adsTemp.begin(0x48, &I2Ctwo)) {
    Serial.println("Failed to initialize adsTemp.");
    while (1);
  }

  adsTemp.setGain(GAIN_ONE);
}

void temperatureControlLoop()
{
  temperature = adsTemp.readADC_SingleEnded(0); //adc value
  temperature = static_cast<float>(Thermistor(static_cast<double>(temperature)));//adc to Celcius
  temperature = temperature;// - tempShift; //tempShift = 0 by default
  Control_PID(temperature);
}

void Control_PID(float iTemp) {

  //Overheat protection
  if (iTemp > MaxTemp) {
    ledcWrite(pwmChannel, 0);
    //Serial.println("Error:overheat. Heater turned off");
    return;
  }

  //In range? If in range, maybe turn on LED?
  if ((iTemp) >= SetTemp) {

    if (bInRange == 0) {
      //digitalWrite(ledPin1, HIGH);

      bInRange = 1;
    }
  } else {
    if (bInRange == 1) {

      //digitalWrite(ledPin1, LOW);
      bInRange = 0;
    }

  }


  //PID subroutine
  float err = SetTemp - iTemp;
  //Serial.println(err);
  s_integral += err * dt;
  //Serial.println(s_integral);
  float s_derivative = (err - previous_error) / dt;
  //Serial.println(s_derivative);
  int U_in_ctrl = (K_P_ctrl * err + K_I_ctrl * s_integral + K_D_ctrl * s_derivative) / (MaxTemp - MinTemp) * 1023;
  //if (U_in_ctrl > 700) U_in_ctrl = 700;

  previous_error = err;


  // put voltage to output and write value to serial monitor
  //  Serial.print("Output PWM frequency: ");

  if (U_in_ctrl <= 1023) {
    if (U_in_ctrl > 0) {
      ledcWrite(pwmChannel, U_in_ctrl);
      //     Serial.println(U_in_ctrl);

    }
    else
    {

      ledcWrite(pwmChannel, 1);
      //    Serial.println("1 / 0 V");
    }
  }
  else {
    ledcWrite(pwmChannel, 1023); //ledcWrite(pwmChannel,700);

    //   Serial.println("1023 / 3.3 V");
  }

}
