"""Offline tests for synthetic payload schema; NOT hardware verification."""
import json
import unittest
from pathlib import Path

class SyntheticMessageTests(unittest.TestCase):
    def test_schema_and_plausibility(self):
        entries = [json.loads(line) for line in (Path(__file__).parent / "synthetic-mqtt.jsonl").read_text().splitlines()]
        self.assertEqual(len(entries), 12)
        for entry in entries:
            self.assertEqual(entry["topic"], "portfolio/esp32/environment")
            p = entry["payload"]
            self.assertEqual(p["device_id"], "esp32-env-01")
            self.assertTrue(-40 <= p["temperature_c"] <= 85)
            self.assertTrue(0 <= p["humidity_pct"] <= 100)
            self.assertTrue(300 <= p["pressure_hpa"] <= 1100)

if __name__ == "__main__":
    unittest.main()
