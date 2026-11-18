"""Offline demonstration of MQTT-style payload format. No hardware or broker required."""
import json
from pathlib import Path

def main():
    for line in (Path(__file__).parent / "synthetic-mqtt.jsonl").read_text().splitlines():
        entry = json.loads(line)
        print(f"[SIMULATED {entry['timestamp_demo_only']}] {entry['topic']} {json.dumps(entry['payload'])}")

if __name__ == "__main__":
    main()
