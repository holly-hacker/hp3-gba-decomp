# Task runner for the HP3 GBA decomp. Run `just` to list recipes.

default:
    @just --list

# Verify the donor ROMs match the pinned hashes.
setup:
    sha1sum -c rom.us.sha1
    sha1sum -c rom.jp.sha1
