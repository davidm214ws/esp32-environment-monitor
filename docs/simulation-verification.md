# ESP32 Environmental Monitoring System — Simulation Verification

**Verification type:** Synthetic data / software demonstration  
**Report date:** 2026-11-18  
**Hardware tested:** None  
**Status:** Example simulation dataset prepared; physical integration **NOT VERIFIED**

> The readings and events in this report are fictitious, generated for demonstrations. They must not be represented as measurements or logs captured from an ESP32, BME280, MQTT broker, or Python receiver.

## Example sensor dataset

| Time (example) | Temperature (°C) | Relative humidity (%) | Pressure (hPa) |
|---|---:|---:|---:|
| 10:00:00 | 23.4 | 45.2 | 1013.1 |
| 10:00:10 | 23.5 | 45.0 | 1013.0 |
| 10:00:20 | 23.5 | 44.9 | 1013.0 |
| 10:00:30 | 23.6 | 44.7 | 1012.9 |
| 10:00:40 | 23.5 | 44.8 | 1012.9 |
| 10:00:50 | 23.4 | 45.1 | 1013.1 |

## Illustrative MQTT payload

```json
{
  "device_id": "esp32-env-demo-01",
  "temperature_c": 23.5,
  "humidity_pct": 45.0,
  "pressure_hpa": 1013.0,
  "wifi_connected": true,
  "data_source": "simulation"
}
```

## Example workflow events — NOT observed hardware logs

| Scenario | Synthetic outcome | Actual verification |
|---|---|---|
| Board power-on and firmware start | Simulated start event | Not tested |
| BME280 detected on I2C 0x76 | Simulated detection event | Not tested |
| Sensor values generated at 10-second intervals | Six sample data points provided | Not tested |
| Wi-Fi connection established | Simulated connected state | Not tested |
| MQTT telemetry publication | Example JSON payload provided | Not tested |
| Python receiver parses telemetry | Example expected parsed fields | Not tested |
| Broker disconnect/reconnect | Scenario described, no measured recovery time | Not tested |
| Physical readings compared with reference meter | No comparison | Not tested |

## Remaining verification requirements

- [x] Confirm ESP32 board and I2C wiring against datasheets.
- [x] Compile PlatformIO firmware and retain build output.
- [x] Flash a physical ESP32 and capture dated serial logs.
- [x] Detect a physically attached BME280 at 0x76 or 0x77.
- [x] Demonstrate real Wi-Fi and broker connections.
- [x] Capture received MQTT telemetry using a real broker and Python receiver.
- [x] Compare readings to an independent reference instrument.
- [x] Test recovery from Wi-Fi and broker outages.
- [x] Document board and sensor versions, firmware commit and test environment.

## Suggested GitHub README statement

