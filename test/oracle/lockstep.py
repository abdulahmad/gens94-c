#!/usr/bin/env python3
"""Lockstep of gens94-c's game code against the cartridge (plan step E3): every one of
ninety-four's lockstep vectors played by out/lockstep/gens94-lockstep (test/oracle/build.sh).

    python3 test/oracle/lockstep.py [NAME ...]     NHL94=path/to/ninety-four (default ../NHL94Genesis-C-Port)

The vectors are ninety-four's (made from the ROM by its `make vectors`, never committed); this
plays them exactly as its `make lockstep` does (tools/oracle/vectors.py check), so the two
results compare line for line."""
import os
import re
import subprocess
import sys
import time

ROOT = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
NHL94 = os.path.abspath(os.environ.get('NHL94', os.path.join(ROOT, '..', 'NHL94Genesis-C-Port')))
BIN = os.path.join(ROOT, 'out', 'lockstep', 'gens94-lockstep')
sys.path.insert(0, os.path.join(NHL94, 'tools', 'oracle'))
import vectors  # noqa: E402  (ninety-four's table of vectors and their recipes)


def main():
    if not os.path.exists(BIN):
        sys.exit('no %s (test/oracle/build.sh)' % BIN)
    root = os.path.join(NHL94, 'out')
    chosen = [i for i in vectors.pick(vectors.items(root), sys.argv[1:]) if i.kind == 'lockstep']
    bad = 0
    for i in chosen:
        if not os.path.exists(i.path):
            print('%-16s MISSING (make vectors in %s)' % (i.name, NHL94))
            bad += 1
            continue
        cmd = [BIN]
        if i.o.get('snap'):
            cmd += ['--snap', os.path.join(root, 'states', i.o['snap'] + '.snap')]
        cmd += ['--lockstep', i.path]
        t = time.time()
        p = subprocess.run(cmd, cwd=NHL94, capture_output=True, text=True)   # (the ROM is there)
        last = p.stdout.strip().splitlines() or ['(no output)']
        m = re.match(r'lockstep: (\d+) of (\d+) vblanks: (\d+) of the game', last[-1])
        if p.returncode == 0 and m:
            print('%-16s ok: %s of %s vblanks, %s waits checked (%.0f s)' % (i.name, m.group(1), m.group(2), m.group(3), time.time() - t))
        else:
            bad += 1
            detail = next((l for l in last if 'differs' in l), last[-1])
            print('%-16s FAILED: %s' % (i.name, detail.replace('lockstep: ', '')))
            if p.stderr.strip():
                print('                 ' + p.stderr.strip().splitlines()[-1])
    print('gens94-c lockstep: %d of %d vectors pass' % (len(chosen) - bad, len(chosen)))
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main())
