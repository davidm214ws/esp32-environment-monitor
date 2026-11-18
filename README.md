# ESP32 Environmental Monitor (BME280 + MQTT)

> **Status: reference implementation — hardware integration and end-to-end tests pending.**

A small, documented embedded portfolio project demonstrating an ESP32 reading temperature, humidity and pressure from a BME280 sensor and publishing measurements as JSON over MQTT to a locally hosted broker. Includes a Python subscriber for verifying messages.

## What it demonstrates

- ESP32 firmware in C++ with PlatformIO
- I2C peripheral integration and basic sensor validation
- Wi-Fi and MQTT reconnect handling
- Machine-readable JSON telemetry, serial diagnostics
- Separation of secrets from version-controlled source code

## Hardware

- ESP32 DevKit-compatible board
- **BME280** breakout board (not BMP280: BMP280 does not measure humidity)
- Jumper wires and USB cable
- PC or Raspberry Pi running a local MQTT broker such as Mosquitto

## Wiring (common ESP32 DevKit, 3.3V BME280 breakout)

| BME280 | ESP32 |
| --- | --- |
| VCC/VIN | 3V3 (check your breakout voltage rating) |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

Most breakout boards provide I2C pull-ups. Confirm your board's datasheet and pinout before powering it. This example tries sensor I2C addresses `0x76` then `0x77`.

## Firmware setup

1. Install [VS Code](https://code.visualstudio.com/) and [PlatformIO](https://platformio.org/install/ide?install=vscode).
2. Open this directory as a PlatformIO project.
3. Copy `include/config.example.h` to `include/config.h` and enter your Wi-Fi details and **local** MQTT broker IP.
4. Connect your ESP32. Use **PlatformIO: Build**, then **Upload**.
5. Open the serial monitor at **115200 baud**.

The firmware publishes to `portfolio/esp32/environment` about every 10 seconds while connected.

Example message (illustrative, not a measured result):

```json
{"device_id":"esp32-env-01","temperature_c":24.10,"humidity_pct":52.30,"pressure_hpa":1012.40}
```

## MQTT broker and receiver

Run Mosquitto or another MQTT broker on your own trusted LAN; configure the broker for authorized local access. **Port 1883 is unencrypted**. Do not expose it publicly. Add authenticated TLS before any Internet/cloud deployment.

On the PC receiving data:

```bash
python -m pip install -r receiver/requirements.txt
python receiver/subscribe.py
```

By default the receiver connects to `127.0.0.1:1883`. If your broker is hosted elsewhere, set `MQTT_HOST` and optionally `MQTT_PORT` and `MQTT_TOPIC` environment variables.

## Project structure

```text
esp32-environment-monitor/
├── .github/workflows/firmware.yml
├── docs/testing-checklist.md
├── include/config.example.h
├── receiver/requirements.txt
├── receiver/subscribe.py
├── src/main.cpp
├── .gitignore
├── LICENSE
├── platformio.ini
└── README.md
```

## Verification checklist

See [`docs/testing-checklist.md`](docs/testing-checklist.md). Add actual logs, hardware photos and measured results only after completing the tests.

## Planned improvements

- On-device watchdog and sensor fault reporting
- Broker authentication and TLS
- Telemetry dashboard and data logging
- Custom PCB design, schematic, BOM and fabricated-board photos

## License

MIT; see [`LICENSE`](LICENSE).


## Portfolio demonstration assets

- [ESP32 ↔ BME280 wiring guide](docs/demo-guide.md#wiring-reference)
- [Synthetic dashboard preview](docs/demo-guide.md#simulated-dashboard-preview)
- [Synthetic MQTT examples and local tests](docs/demo-guide.md#run-the-offline-demonstration)
- [Verification status and pending hardware tests](docs/verification-report.md)

**Evidence disclosure:** These demonstration readings and dashboard images are synthetic. No physical ESP32 or BME280 verification is claimed.
