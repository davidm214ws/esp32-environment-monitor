"""Print incoming sensor readings. Set MQTT_HOST and MQTT_TOPIC if needed."""
import json
import os
import paho.mqtt.client as mqtt

HOST = os.getenv("MQTT_HOST", "127.0.0.1")
PORT = int(os.getenv("MQTT_PORT", "1883"))
TOPIC = os.getenv("MQTT_TOPIC", "portfolio/esp32/environment")


def on_connect(client, userdata, flags, reason_code, properties):
    if reason_code == 0:
        print(f"Connected; subscribing to {TOPIC}")
        client.subscribe(TOPIC)
    else:
        print(f"Connection failed: {reason_code}")


def on_message(client, userdata, message):
    try:
        payload = json.loads(message.payload.decode("utf-8"))
        print(json.dumps(payload, indent=2))
    except (UnicodeDecodeError, json.JSONDecodeError) as exc:
        print(f"Invalid message: {exc}")


def main():
    client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(HOST, PORT, keepalive=60)
    client.loop_forever()


if __name__ == "__main__":
    main()
