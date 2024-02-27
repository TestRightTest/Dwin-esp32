#define HEATER_LEDC_PIN             2
#define HEATER_LEDC_FREQUENCY       5000
#define HEATER_LEDC_CHANNEL         1
#define HEADER_LEDC_RESOLUTION      10

bool heaterInit() 
{
  if (!ledcSetup(HEATER_LEDC_CHANNEL, HEATER_LEDC_FREQUENCY, HEADER_LEDC_RESOLUTION)) {
    return false;  
  }
  ledcAttachPin(HEATER_LEDC_PIN, HEATER_LEDC_CHANNEL);
  return true;
}

bool heaterWrite(int value)
{
    ledcWrite(HEATER_LEDC_CHANNEL, constrain(value, 0, 1023));
    return true;
}
