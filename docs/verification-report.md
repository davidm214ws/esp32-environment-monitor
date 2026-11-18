# ESP32 Environmental Monitor — Evidence & Verification Status

**Status:** Software demonstration prepared; physical hardware verification **NOT PERFORMED**.  
**Report date:** 2026-11-18  
**Hardware available:** None.  
**Sensor readings:** Synthetic example values, not actual BME280 measurements.

## Evidence created

| Item | Result | Evidence | Interpretation |
|---|---|---|---|
| Wiring reference | DOCUMENTED | `assets/wiring-diagram.svg` | Recommended connections; not electrically verified |
| Demonstration dashboard | CREATED | `assets/synthetic-dashboard-demo.png` | Mockup based on fabricated sample readings |
| Example MQTT payloads | CREATED | `demo/synthetic-mqtt.jsonl` | Demonstrates expected JSON format, no broker required |
| Python sample schema checks | PASS (offline) | `python -m unittest discover -s demo -p 'test_*.py'` | Validates synthetic samples only |
| Python syntax | PASS (offline) | `python -m compileall -q receiver demo` | Syntax only; not proof MQTT connectivity |
| PlatformIO ESP32 firmware build | NOT RUN | GitHub Actions workflow included | Run Actions workflow to verify compilation |
| ESP32 power-up | NOT TESTED | No physical board | Requires actual ESP32 |
| BME280 sensor detection | NOT TESTED | No physical sensor | Requires actual BME280 |
| Wi-Fi connectivity | NOT TESTED | No device used | Requires physical or genuine supported virtual execution |
| MQTT broker integration | NOT TESTED | No broker run | Can be tested on computer with a broker |
| Reconnect/resilience | NOT TESTED | No hardware/network tests | Requires integration testing |
| Actual hardware photos and serial logs | NOT AVAILABLE | No physical test took place | Do not substitute synthetic screenshots |

## Hardware test checklist for future

- [ ] Verify pinout and voltage levels of the exact BME280 breakout
- [ ] Build firmware using PlatformIO and save CI build log
- [ ] Upload firmware to ESP32 and save serial boot log
- [ ] Confirm BME280 at 0x76 or 0x77
- [ ] Verify sensor readings against independent instrument
- [ ] Observe end-to-end MQTT messages and receiver output
- [ ] Test disconnect/reconnect behavior
- [ ] Add physical photo, firmware commit ID, date, configuration and captured logs

## Sample data note

Values in this repository were intentionally generated for demonstration and should not be presented as laboratory measurements or hardware test evidence.
