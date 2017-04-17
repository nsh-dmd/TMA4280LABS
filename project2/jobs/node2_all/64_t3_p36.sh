#!/bin/bash
#PBS -N nesh_i64_p36_t3
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=2:ncpus=20:mpiprocs=36:ompthreads=3
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 64_3t36p.o
#PBS -e 3t36p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 64
