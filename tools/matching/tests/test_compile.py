import shutil
import tempfile
import unittest
from pathlib import Path
from tools.c.compile_c import profile, place_in_text, compile_one, agbcc_prefix
from tools.matching.compile import compile_source


class CompileTests(unittest.TestCase):
    def test_profile_and_writable_sections(self):
        self.assertTrue(profile('src/libc/a.c', '/tool')[0].endswith('/old_agbcc'))
        self.assertNotIn('-mthumb-interwork', profile('src/libc/a.c', '/tool')[2])
        self.assertIn('-mthumb-interwork', profile('src/battle/a.c', '/tool')[2])
        self.assertEqual(place_in_text('.section .rodata\n', 'a.c'), '.text\n')
        with self.assertRaises(SystemExit):
            place_in_text('.comm x,4\n', 'a.c')

    @unittest.skipUnless(shutil.which('agbcc'), 'requires Nix compiler')
    def test_candidate_matches_production_assembly(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory)
            for source in ['src/battle/resolve_enemy_attack.c', 'src/libc/memcpy.c']:
                compile_one(source, str(path/'production.s'), agbcc_prefix())
                compile_source(source, path/'candidate.o', source)
                # Only the extra separator newline differs between wrappers.
                self.assertEqual((path/'production.s').read_text().split(),
                                 (path/'candidate.s').read_text().split())
