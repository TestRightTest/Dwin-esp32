void fatal(const char *message) {
    while (1) {
        Serial.println(message);
        delay(5000);
    }
}
