#!/bin/bash
#PBS -N nesh_i1024_p16_t16
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=1:ncpus=20:mpiprocs=16:ompthreads=16
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 1024_16t16p.o
#PBS -e 16t16p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 1024
