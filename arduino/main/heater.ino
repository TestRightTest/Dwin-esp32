const int freq = 5000;
const int pwmChannel = 1;
const int resolution = 10;

void heaterInit() 
{
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(HEATER_PIN, pwmChannel);   
}
