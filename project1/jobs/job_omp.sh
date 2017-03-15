#!/bin/bash
#PBS -N omp
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=2:ncpus=20:mpiprocs=2
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o omp_2_20.o
#PBS -e omp_2_20.e
#PBS -q training

cd $PBS_O_WORKDIR

module load gcc
module load openmpi

mpiexec ./zeta2 32
mpiexec ./zeta2 64
mpiexec ./zeta2 128
mpiexec ./zeta2 256
mpiexec ./zeta2 512
mpiexec ./zeta2 1024
mpiexec ./zeta2 2048
mpiexec ./zeta2 4096
mpiexec ./zeta2 8192
mpiexec ./zeta2 16384

mpiexec ./mach2 32
mpiexec ./mach2 64
mpiexec ./mach2 128
mpiexec ./mach2 256
mpiexec ./mach2 512
mpiexec ./mach2 1024
mpiexec ./mach2 2048
mpiexec ./mach2 4096
mpiexec ./mach2 8192
mpiexec ./mach2 16384
