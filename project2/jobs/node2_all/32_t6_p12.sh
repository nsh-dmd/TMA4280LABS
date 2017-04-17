#!/bin/bash
#PBS -N nesh_i32_p12_t6
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=2:ncpus=20:mpiprocs=12:ompthreads=6
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 32_6t12p.o
#PBS -e 6t12p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 32
