#!/bin/bash
#PBS -N nesh_i4096_p4_t16
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=2:ncpus=20:mpiprocs=4:ompthreads=16
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 4096_16t4p.o
#PBS -e 16t4p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 4096
