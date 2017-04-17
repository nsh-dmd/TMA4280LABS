#!/bin/bash
#PBS -N nesh_i2048_p16_t4
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=2:ncpus=20:mpiprocs=16:ompthreads=4
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 2048_4t16p.o
#PBS -e 4t16p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 2048
