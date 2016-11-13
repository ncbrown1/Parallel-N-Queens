#!/usr/bin/env python
import sys

## Sample run:
##   ./slurmgen.py [procs] [n]
##   to run `./nqueens [n]` on [procs] processors

template = """#!/bin/bash
#SBATCH --job-name="nqueens"
#SBATCH --output="nqueens.%s.%s.out"
#SBATCH --partition=shared
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=%s
#SBATCH --export=ALL
#SBATCH -t 00:30:00
#SBATCH -A TG-ASC160059

export CILK_NWORKERS=%s
cd /home/$USER/nqueens/
./nqueens %s
"""

procs = sys.argv[1]
n = sys.argv[2]
print template % (procs, n, procs, procs, n)
