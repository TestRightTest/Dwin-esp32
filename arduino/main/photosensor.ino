//
//#define NUM_OF_LEDS                 (NUM_OF_CHANNELS * 2)
//
//// Led Mux Select Pins
//#define LED_MUX_SO                  4
//#define LED_MUX_S1                  12
//#define LED_MUX_S2                  13
//#define LED_MUX_S3                  14
//
//// Led Mux Control Pins
//#define LED_MUX_COM1                27
//#define LED_MUX_COM2                26
//
//
//// 16 milk samples -> each has two led and one photodiode
//// Channel
//
//// 1 ADC handles 4 photodios. 2 ADC in one PCB. Total 2 PCB. Total 4 ADC for 16 Photodiodes
//// 1 ADC for temperature
//
//
//
//enum LedType {
//  RED_LED,
//  IR_LED
//};
//
//const uint8_t channelMap[NUM_OF_LEDS] = { 6, 7, 4, 5, 2, 3, 0, 1, 14, 15, 12, 13, 10, 11, 8, 9, 24, 25, 26, 27, 28, 29, 30, 31, 16, 17, 18, 19, 20, 21, 22, 23 };
//
//unsigned getAdsChannel(unsigned channel)
//{
//  return channelMap[channel * 2] % 4;
//}
//
//unsigned getAdsId(unsigned channel)
//{
//  return channelMap[channel * 2] / 4 + 1;
//}
//
//unsigned getRedLedForChannel(unsigned channel)
//{
//  return channelMap[channel * 2];
//}
//
//unsigned getIRLedForChannel(unsigned channel)
//{
//  return channelMap[channel * 2 + 1];
//}
//
//void photosensorInit()
//{
//  pinMode(muxS0, OUTPUT);
//  pinMode(muxS1, OUTPUT);
//  pinMode(muxS2, OUTPUT);
//  pinMode(muxS3, OUTPUT);
//  pinMode(COM1, OUTPUT);
//  pinMode(COM2, OUTPUT);
//
//  digitalWrite(muxS0, LOW);
//  digitalWrite(muxS1, LOW);
//  digitalWrite(muxS2, LOW);
//  digitalWrite(muxS3, LOW);
//  digitalWrite(COM1, LOW);
//  digitalWrite(COM2, LOW);
//
//  I2Cone.begin(SDA_PHOTODIODE, SCL_PHOTODIODE, 100000);
//
//  if (!ads1.begin(0x49, &I2Cone)) {
//    Serial.println("Failed to initialize ads1.");
//    while (1);
//  }
//  if (!ads2.begin(0x4B, &I2Cone)) {
//    Serial.println("Failed to initialize ads2.");
//    while (1);
//  }
//  if (!ads3.begin(0x48, &I2Cone)) {
//    Serial.println("Failed to initialize ads3.");
//    while (1);
//  }
//  if (!ads4.begin(0x4A, &I2Cone)) {
//    Serial.println("Failed to initialize ads4.");
//    while (1);
//  }
//  // TODO: Check if needed?
//  delay(500);
//
//  // Set gain for all ADS1115 devices
//  ads1.setGain(GAIN_ONE);
//  ads2.setGain(GAIN_ONE);
//  ads3.setGain(GAIN_ONE);
//  ads4.setGain(GAIN_ONE);
//
//  printwhite(); //print white values on serial
//}
//
//void ledPinSelect(int channel, bool state) {
//  int comPin = (channel < numChannels) ? COM1 : COM2;
//
//  channel = channel % numChannels;
//
//  int muxChannel[16][4] = {
//    {1, 0, 0, 0}, // channel 0 R1
//    {0, 0, 0, 0}, // channel 1 IR1
//    {1, 1, 0, 0}, // channel 2 R2
//    {0, 1, 0, 0}, // channel 3 IR2
//
//    {1, 0, 1, 0}, // channel 4 R3
//    {0, 0, 1, 0}, // channel 5 IR3
//    {1, 1, 1, 0}, // channel 6 R4
//    {0, 1, 1, 0}, // channel 7 IR4
//
//    {1, 0, 0, 1}, // channel 8 R5
//    {0, 0, 0, 1}, // channel 9 IR5
//    {1, 1, 0, 1}, // channel 10 R6
//    {0, 1, 0, 1}, // channel 11 IR6
//
//    {1, 0, 1, 1}, // channel 12 R7
//    {0, 0, 1, 1}, // channel 13 IR7
//    {1, 1, 1, 1}, // channel 14 R8
//    {0, 1, 1, 1}  // channel 15 IR8
//  };
//
//  digitalWrite(LED_MUX_S0, muxChannel[channel][0]);
//  digitalWrite(LED_MUX_S1, muxChannel[channel][1]);
//  digitalWrite(LED_MUX_S2, muxChannel[channel][2]);
//  digitalWrite(LED_MUX_S3, muxChannel[channel][3]);
//
//  digitalWrite(comPin, state)
//}
//
//
//int readPhotodiodeWithLed(unsigned channel, enum LedType type) {
//  unsigned adsID = getAdsId(channel);
//  unsigned adsChannel = getAdsChannel(channel);
//  unsigned led = (type == RED_LED) ? getRedLedForChannel(channel) : getIRLedForChannel(channel);
//
//  Serial.print(" adschannel" + String(adsChannel) + " ");
//  Serial.print(" adsID" + String(adsID) + ":  ");
//
//  ledPinSelect(led, HIGH);
//
//  int sensorValue = 0;
//  switch (adsID) {
//    case 1: sensorValue = ads1.readADC_SingleEnded(adsChannel); break;
//    case 2: sensorValue = ads2.readADC_SingleEnded(adsChannel); break;
//    case 3: sensorValue = ads3.readADC_SingleEnded(adsChannel); break;
//    case 4: sensorValue = ads4.readADC_SingleEnded(adsChannel); break;
//  }
//
//  delay(200);
//  Serial.println(sensorValue);
//
//  ledPinSelect(led, LOW);
//  return sensorValue;
//}
//
//long calculateAbsValue(unsigned channel)
//{
//  ChannelData *channelData = getChannel(channel);
//  float redLedAbs = (float)channelData->redBaseline / readPhotodiodeWithLed(channel, RED_LED);
//  float irLedAbs = (float)channelData->irBaseline / readPhotodiodeWithLed(channel, IR_LED);
//
//  return round(100000 * (log10(redLedAbs) - log10(irLedAbs)));
//}
//
//int readOneChannel(unsigned channel) {
//  unsigned long currentMillis = millis();
//  unsigned long durationSeconds = (currentMillis - channelStartTimes[channel]) / 1000; // Convert to seconds
//
//  float durationMinutes = durationSeconds / 60.0; // Convert to minutes with one decimal place
//
//  Serial.print("Channel " + String(channel + 1) + ": ");
//  Serial.print(durationMinutes, 0); // Display with zero decimal place
//  Serial.print(",");
//
//  long absVal = calculateAbsValue(channel);
//  progressValues[channel] = round(100 * ((float)(firstReading[channel] - absVal) / firstReading[channel]));
//  Serial.println(progressValues[channel]);
//  progressValues[channel] = constrain(progressValues[channel], 0, 99);
//}
//
//void readChannels() {
//  unsigned long currentMillis = millis();
//  static unsigned long lastDisplayTime = 0;
//
//  // Check if 30 seconds have passed since the last display
//  if (currentMillis - lastDisplayTime >= datainterval * 60000) {
//    lastDisplayTime = currentMillis;
//
//    for (int i = 0; i < numChannels; i++) {
//      if (isRunning[i]) {
//        readOneChannel(channel);
//        if (progressValues[i] >= progressThreshold) completedChannel(i + 1);
//        updateProgress(i + 1);
//        updateAllElapsedTime(); //priority 2
//      }
//    }
//  }
//}
//
//
//void takeWhite(int chID)
//{
//  Serial.println("White started for channel " + String(chID + 1) );
//  for (int i = 0; i < 2 ; i++)
//  {
//    whiteData[chID * 2 + i] = sensorRead(chID * 2 + i);
//    Serial.println(String(whiteData[chID * 2 + i]) + ",");
//
//    byte quotient = whiteData[chID * 2 + i] / 255;  // Calculate quotient (0-254)
//    byte remainder = whiteData[chID * 2 + i] % 255; // Calculate remainder (0-254)
//    EEPROM.write(chID * 4 + i * 2, quotient); // Store quotient
//    EEPROM.write(chID * 4 + i * 2 + 1, remainder); // Store remainder
//  }
//  Serial.println();
//  EEPROM.commit();
//}
//
//void printwhite() {
//  Serial.print("White values: ");
//  for (int i = 0; i < numChannels * 2; i++)
//  {
//    byte quotient = EEPROM.read(2 * i);          // Read quotient
//    byte remainder = EEPROM.read(2 * i + 1);     // Read remainder
//
//    whiteData[i] = quotient * 255 + remainder;   // Combine quotient and remainder
//    Serial.print(whiteData[i]); Serial.print(" ,");
//  }
//
//  Serial.println();
//}
//
//void takeFirstReading(int chID) {
//  // Serial.println("Channel " + String(chID+1) + " started");
//  rawReadingFlag = false;
//
//  int i = chID * 2;
//  firstReading[chID] = round(100000 * (log10((float)whiteData[i] / sensorRead(i)) - log10((float)whiteData[i + 1] / sensorRead(i + 1))));
//  Serial.print("First Reading = ");
//  Serial.println(firstReading[chID]);
//  progressValues[chID] = 0;
//  autoReadFlag = true;
//
//  //send firstreading to firebase
//  //send white1 and white2
//  String uidStr = String(auth.token.uid.c_str());
//  sendDataToFirebase("/sampleDetails/"  + uidStr + " channel "   + String(chID + 1) + "/FirstReading" , String(firstReading[chID]));
//  sendDataToFirebase("/sampleDetails/"  + uidStr + " channel "   + String(chID + 1) + "/White1" , String(whiteData[i]));
//  sendDataToFirebase("/sampleDetails/"  + uidStr + " channel "   + String(chID + 1) + "/White2" , String(whiteData[i + 1]));
//
//
//}
