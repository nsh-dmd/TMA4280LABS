#!/bin/bash
#PBS -N nesh_i64_p16_t8
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=1:ncpus=20:mpiprocs=16:ompthreads=8
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 64_8t16p.o
#PBS -e 8t16p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 64
