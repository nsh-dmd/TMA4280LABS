#!/bin/bash
#PBS -N nesh_i1024_p4_t4
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=2:ncpus=20:mpiprocs=4:ompthreads=4
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 1024_4t4p.o
#PBS -e 4t4p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 1024
