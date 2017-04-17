#!/bin/bash
#PBS -N nesh_i16_p12_t4
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=1:ncpus=20:mpiprocs=12:ompthreads=4
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 16_4t12p.o
#PBS -e 4t12p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 16
