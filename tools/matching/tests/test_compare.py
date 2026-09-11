import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path
from tools.matching.compare import category, instructions


class ComparisonTests(unittest.TestCase):
    def test_operands_not_hidden(self):
        self.assertEqual(category(('movs', 'r0, #1'), ('movs', 'r1, #1')), 'register')
        self.assertEqual(category(('movs', 'r0, #1'), ('movs', 'r0, #2')), 'operand/constant/address')
        self.assertEqual(category(('bl', '100'), ('bl', '200')), 'branch/operand')

    @unittest.skipUnless(shutil.which('arm-none-eabi-as'), 'requires Nix binutils')
    def test_selected_function_and_relocation(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory)
            (path / 'a.s').write_text('.syntax unified\n.thumb\n.global Wanted\n.type Wanted,%function\n.thumb_func\nWanted:\nmovs r0,#1\nbl External\nbx lr\n.size Wanted,.-Wanted\n.global Other\n.type Other,%function\n.thumb_func\nOther:\nmovs r1,#99\nbx lr\n.size Other,.-Other\n')
            subprocess.run(['arm-none-eabi-as', '-mcpu=arm7tdmi', '-o', path/'a.o', path/'a.s'], check=True)
            decoded = instructions(path/'a.o', 'Wanted')
            self.assertTrue(any(m == 'movs' and '#1' in o for m, o in decoded))
            self.assertTrue(any(m == 'relocation' and 'External' in o for m, o in decoded))
            self.assertFalse(any('#99' in o for _, o in decoded))

    def test_source_changed_since_compile_is_rejected(self):
        import hashlib
        import json
        from tools.matching.compare import compare
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root/'workspace.json').write_text('{}')
            (root/'current').mkdir()
            (root/'current/candidate.c').write_text('changed')
            (root/'current/compiled.json').write_text(json.dumps({'source_sha256': hashlib.sha256(b'old').hexdigest()}))
            with self.assertRaisesRegex(ValueError, 'compile again'):
                compare(root)
