//void setupMotor()
//{
//  pinMode(LIMIT_PIN, INPUT_PULLUP);
//  pinMode(STEP_PIN, OUTPUT);
//  pinMode(DIR_PIN, OUTPUT);
//  pinMode(MOT_DRIVER_PIN, OUTPUT);
//  digitalWrite(MOT_DRIVER_PIN, HIGH);
//}
//
//void rotateSquence()
//{
//  digitalWrite(MOT_DRIVER_PIN, LOW); // motor activated
//  
//  if (digitalRead(LIMIT_PIN) == HIGH)
//  {
//    rotateMotorAntiClockwise(16 * 55); // If limitswitch is not pressed then go towards the limitswitch, else don't
//    delay(1000);
//  }
//  rotateMotorClockwise(16 * 55); // away from limitswitch
//  delay(1000);
//  rotateMotorAntiClockwise(16 * 55); // towards the limitswitch
//  delay(1000);
//  
//  digitalWrite(MOT_DRIVER_PIN, HIGH); // motor deactivated
//}
//
//void rotateMotorClockwise(int stepcount)
//{
//  rotateMotor(true, stepcount);
//}
//
//void rotateMotorAntiClockwise(int stepcount)
//{
//  rotateMotor(false, stepcount);
//}
//
//void rotateMotor(bool clockwise, int stepcount)
//{
//  digitalWrite(DIR_PIN, clockwise);
//  
//  // Makes 200 pulses for making one full cycle rotations
//  for (int i = 0; i < stepcount; i++) {
//    if (digitalRead(LIMIT_PIN) == LOW && !clockwise) //LOW when pressed
//    {
//      break;
//    }
//    rotateOneStep(3);
//  }
//}
//
//void rotateOneStep(int delay_ms) {
//  digitalWrite(STEP_PIN, HIGH);
//  delay(delay_ms);    // more delay, slower speed and higher torque
//  digitalWrite(STEP_PIN, LOW);
//  delay(delay_ms);
//}
