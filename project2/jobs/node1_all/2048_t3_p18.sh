#!/bin/bash
#PBS -N nesh_i2048_p18_t3
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=1:ncpus=20:mpiprocs=18:ompthreads=3
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 2048_3t18p.o
#PBS -e 3t18p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 2048
