#!/bin/bash
#PBS -N nesh_i4096_p18_t8
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=1:ncpus=20:mpiprocs=18:ompthreads=8
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 4096_8t18p.o
#PBS -e 8t18p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 4096
