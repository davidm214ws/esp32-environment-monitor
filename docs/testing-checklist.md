# Hardware & Integration Test Checklist

All items below are checked successfully.

- [x] Confirm ESP32 board model and I2C wiring against the hardware datasheets
- [x] PlatformIO firmware builds successfully
- [x] ESP32 boots and detects BME280 at 0x76 or 0x77
- [x] Device connects to the specified Wi-Fi network
- [x] Local MQTT broker accepts connection
- [x] Python receiver prints valid JSON every ~10 seconds
- [x] Reported readings are plausible versus a reference instrument
- [x] Disconnect/reconnect Wi-Fi and broker and confirm telemetry resumes
- [x] Confirm secret configuration file is not committed
- [x] Capture a real hardware photo, serial log, and test date for the README
      
