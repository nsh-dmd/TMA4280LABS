#!/bin/bash
#PBS -N nesh_i256_p36_t1
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:10:00
#PBS -l select=2:ncpus=20:mpiprocs=36:ompthreads=1
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 256_1t36p.o
#PBS -e 1t36p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 256
