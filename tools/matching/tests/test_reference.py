import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch
from tools.matching.reference import build_target_asm


class ReferenceTests(unittest.TestCase):
    def test_inline_and_standalone_literals_and_boundary(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root/'build/us').mkdir(parents=True)
            (root/'ram_symbols.us.inc').write_text('.set State, 0x03000000\n')
            (root/'build/us/full_disasm.s').write_text('thumb_func_start A\nA: @ 0x08000000\nbx lr\n_pool: .4byte 0x03000000 @ state\n.4byte 0x03000000\nthumb_func_start B\nB:\nmovs r0,#99\n')
            with patch('tools.matching.reference.ROOT', root):
                asm, mode = build_target_asm('us', 'A')
            self.assertEqual(mode, 'thumb')
            self.assertIn('_pool: .4byte State', asm)
            self.assertEqual(asm.count('.4byte State'), 2)
            self.assertNotIn('#99', asm)

    def test_missing_function(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root/'build/us').mkdir(parents=True)
            (root/'build/us/full_disasm.s').write_text('')
            with patch('tools.matching.reference.ROOT', root), self.assertRaises(ValueError):
                build_target_asm('us', 'Absent')

    def test_explicit_end_excludes_following_data(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root/'build/us').mkdir(parents=True)
            (root/'build/us/full_disasm.s').write_text('thumb_func_start A\nA: @ 0x08000000\nbx lr\n.align 2,0\n_08000004:\n.byte 99,99,99,99\n')
            with patch('tools.matching.reference.ROOT', root):
                asm, _ = build_target_asm('us', 'A', 0x08000004)
            self.assertNotIn('.byte', asm)
            self.assertIn('bx lr', asm)

    def test_conflicting_manifest_name_fails_before_workspace_creation(self):
        from tools.matching.prepare import prepare
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root/'build/us').mkdir(parents=True)
            (root/'regions.us.txt').write_text('c-file 0x08000010 0x08000014 src/a.c A\n')
            (root/'build/us/full_disasm.s').write_text('thumb_func_start A\nA: @ 0x08000000\nbx lr\n')
            with patch('tools.matching.prepare.ROOT', root), self.assertRaisesRegex(ValueError, 'manifest'):
                prepare('us', 'A')
            self.assertFalse((root/'build/matching').exists())
