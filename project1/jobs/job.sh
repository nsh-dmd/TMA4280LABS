#!/bin/bash
#PBS -N mach012H
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:01:00
#PBS -l select=2:ncpus=20:mpiprocs=8
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o hyb_8_20
#PBS -e hyb_8_20


cd $PBS_O_WORKDIR

module load gcc
module load openmpi

mpiexec ./zeta 32
mpiexec ./zeta 64
mpiexec ./zeta 128
mpiexec ./zeta 256
mpiexec ./zeta 512
mpiexec ./zeta 1024
mpiexec ./zeta 2048
mpiexec ./zeta 4096
mpiexec ./zeta 8192
mpiexec ./zeta 16384

mpiexec ./mach 32
mpiexec ./mach 64
mpiexec ./mach 128
mpiexec ./mach 256
mpiexec ./mach 512
mpiexec ./mach 1024
mpiexec ./mach 2048
mpiexec ./mach 4096
mpiexec ./mach 8192
mpiexec ./mach 16384
