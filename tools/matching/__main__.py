"""Matching tools. Run from the repository root inside nix develop."""
import argparse
import subprocess
import sys


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest='command', required=True)
    p = sub.add_parser('prepare', help='create isolated workspace; validate extracted reference bytes')
    p.add_argument('version', choices=['us', 'jp'])
    p.add_argument('name')
    p.add_argument('--reference-name', help='explicit disassembly alias when it differs from the C/manifest name')
    p.add_argument('--source', help='draft source; defaults to manifest C source')
    p.add_argument('--end', type=lambda s: int(s, 0), help='exclusive verified extent, required without manifest row')
    p.add_argument('--profile-source', help='production source path used to select game/libc profile')
    p = sub.add_parser('compile', help='compile current candidate with production flags')
    p.add_argument('workspace')
    p.add_argument('--source')
    p.add_argument('--dumps', choices=['lg', 'flg', 'a'])
    p = sub.add_parser('compile-object', help='compile standalone C with shared production profile')
    p.add_argument('source')
    p.add_argument('-o', required=True)
    p.add_argument('--profile-source', required=True)
    p.add_argument('--preprocessed', action='store_true')
    p = sub.add_parser('compare', help='link against baseline symbols, check bytes and show selected-function differences')
    p.add_argument('workspace')
    p = sub.add_parser('snapshot', help='preserve current candidate and artifacts under an immutable name')
    p.add_argument('workspace')
    p.add_argument('name')
    p = sub.add_parser('permuter-setup', help='create permuter inputs from current candidate (refuses overwrite)')
    p.add_argument('workspace')
    p = sub.add_parser('permuter-run', help='bounded optional search; default 120 seconds, 2 workers')
    p.add_argument('workspace')
    p.add_argument('--seconds', type=int, default=120)
    p.add_argument('--jobs', type=int, default=2)
    p.add_argument('--approved-long-run', action='store_true', help='assert user explicitly approved duration over 180 seconds')
    # Delegate legacy diagnostic/discovery arguments without duplicating their parsers.
    for name, help_text in [('diff-region', 'compare existing linked ROM region; use just diff-region to rebuild'),
                            ('match-versions', 'propose US/JP correspondences; no files changed'),
                            ('opcode-diff', 'legacy mnemonic-only structural diagnostic')]:
        sub.add_parser(name, help=help_text, add_help=False)
    args, rest = parser.parse_known_args()
    if args.command in ('diff-region', 'match-versions', 'opcode-diff'):
        module = {'diff-region': 'diff_region', 'match-versions': 'match_versions', 'opcode-diff': 'opcode_diff'}[args.command]
        sys.argv = [module, *rest]
        from importlib import import_module
        return import_module('tools.matching.' + module).main()
    if rest:
        parser.error('unrecognized arguments: ' + ' '.join(rest))
    from . import prepare, compile, compare, workspace, permuter
    if args.command == 'prepare':
        prepare.prepare(args.version, args.name, args.source, args.end, args.profile_source, args.reference_name)
    elif args.command == 'compile':
        compile.compile_workspace(args.workspace, args.source, args.dumps)
    elif args.command == 'compile-object':
        compile.compile_source(args.source, args.o, args.profile_source, preprocessed=args.preprocessed)
    elif args.command == 'compare':
        return compare.compare(args.workspace)
    elif args.command == 'snapshot':
        workspace.snapshot(args.workspace, args.name)
    elif args.command == 'permuter-setup':
        permuter.setup(args.workspace)
    elif args.command == 'permuter-run':
        return permuter.search(args.workspace, args.seconds, args.jobs, args.approved_long_run)
    return 0


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (ValueError, OSError, subprocess.CalledProcessError) as exc:
        sys.exit(str(exc))
