#!/bin/bash
#PBS -N nesh_i16384_p1_t1
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:30:00
#PBS -l select=2:ncpus=20:mpiprocs=1:ompthreads=1
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 2node16384_1t1p.o
#PBS -e 1t1p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi

mpiexec ./poisson 16384