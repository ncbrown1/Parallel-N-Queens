#!/usr/bin/env python
import sys

## Sample run:
##   ./slurmgen.py [procs] [n] [flag]
##   to run `./nqueens [flag] [n]` on [procs] processors

template = """#!/bin/bash
#SBATCH --job-name="nqueens"
#SBATCH --output="nqueens.%s.%s.%s.out"
#SBATCH --partition=compute
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --export=ALL
#SBATCH -t 00:30:00
#SBATCH -A TG-ASC160059

export CILK_NWORKERS=%s
cd /home/$USER/nqueens/
./nqueens %s %s
"""

procs = sys.argv[1]
n = sys.argv[2]
if len(sys.argv) > 3:
  flag = sys.argv[3]
else:
  flag = "-p"
print template % (flag[1:], procs, n, procs, flag, n)
