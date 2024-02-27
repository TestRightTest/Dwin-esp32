//#define STORAGE_MAGIC_UPPER_BYTE     0xAA
//#define STORAGE_MAGIC_LOWER_BYTE     0x55
//
//
//
//void initStorage() {
//    
//}
//
//void readStorage(char *buffer, int address, int maxLength) {
//  for (int i = 0; i < maxLength; ++i) {
//    char c = EEPROM.read(address + i);
//    buffer[i] = c;
//    if (c == '\0') break; // Stop reading at null terminator
//  }
//}
//
//void saveStorage(const char *data, int address, int maxLength) {
//  for (int i = 0; i < maxLength; ++i) {
//    char c = data[i];
//    EEPROM.write(address + i, c);
//    if (c == '\0') break; // Stop writing at null terminator
//  }
//  EEPROM.commit(); // Commit changes to EEPROM
//}
