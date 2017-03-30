#!/bin/bash
#PBS -N mpi
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=2:ncpus=20:mpiprocs=2
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o mpi_2_20.o
#PBS -e mpi_2_20.e
#PBS -q training

cd $PBS_O_WORKDIR

module load gcc
module load openmpi

mpiexec ./zeta1 32
mpiexec ./zeta1 64
mpiexec ./zeta1 128
mpiexec ./zeta1 256
mpiexec ./zeta1 512
mpiexec ./zeta1 1024
mpiexec ./zeta1 2048
mpiexec ./zeta1 4096
mpiexec ./zeta1 8192
mpiexec ./zeta1 16384

mpiexec ./mach1 32
mpiexec ./mach1 64
mpiexec ./mach1 128
mpiexec ./mach1 256
mpiexec ./mach1 512
mpiexec ./mach1 1024
mpiexec ./mach1 2048
mpiexec ./mach1 4096
mpiexec ./mach1 8192
mpiexec ./mach1 16384
