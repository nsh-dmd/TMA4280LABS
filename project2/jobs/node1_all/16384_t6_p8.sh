#!/bin/bash
#PBS -N nesh_i16384_p8_t6
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=1:ncpus=20:mpiprocs=8:ompthreads=6
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 16384_6t8p.o
#PBS -e 6t8p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 16384
