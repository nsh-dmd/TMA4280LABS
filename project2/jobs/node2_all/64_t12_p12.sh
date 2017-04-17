#!/bin/bash
#PBS -N nesh_i64_p12_t12
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=2:ncpus=20:mpiprocs=12:ompthreads=12
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 64_12t12p.o
#PBS -e 12t12p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 64
