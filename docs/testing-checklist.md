# Hardware & Integration Test Checklist

All items below are **not yet verified**; check them only after running real tests.

- [ ] Confirm ESP32 board model and I2C wiring against the hardware datasheets
- [ ] PlatformIO firmware builds successfully
- [ ] ESP32 boots and detects BME280 at 0x76 or 0x77
- [ ] Device connects to the specified Wi-Fi network
- [ ] Local MQTT broker accepts connection
- [ ] Python receiver prints valid JSON every ~10 seconds
- [ ] Reported readings are plausible versus a reference instrument
- [ ] Disconnect/reconnect Wi-Fi and broker and confirm telemetry resumes
- [ ] Confirm secret configuration file is not committed
- [ ] Capture a real hardware photo, serial log, and test date for the README

Record: hardware revision, firmware commit, sensor board, broker version, test date, evidence, and known issues.
