import os
import sys
import tempfile
import time
import unittest
from pathlib import Path
from tools.matching.permuter import bounded_run, search


class PermuterTests(unittest.TestCase):
    def test_long_run_requires_asserted_approval(self):
        with self.assertRaises(ValueError):
            search('/nonexistent', seconds=181)

    def test_timeout_stops_descendant_and_retains_log(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory)
            marker = path/'escaped'
            child = f'import time; from pathlib import Path; time.sleep(1); Path({str(marker)!r}).write_text("bad")'
            parent = f'import subprocess,sys,time; print("started", flush=True); subprocess.Popen([sys.executable,"-c",{child!r}]); time.sleep(5)'
            start = time.monotonic()
            self.assertEqual(bounded_run([sys.executable, '-c', parent], .2, path/'log'), 124)
            time.sleep(1.1)
            self.assertFalse(marker.exists())
            self.assertIn('started', (path/'log').read_text())
            self.assertLess(time.monotonic()-start, 4)
