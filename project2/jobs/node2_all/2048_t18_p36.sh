#!/bin/bash
#PBS -N nesh_i2048_p36_t18
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=2:ncpus=20:mpiprocs=36:ompthreads=18
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 2048_18t36p.o
#PBS -e 18t36p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 2048
