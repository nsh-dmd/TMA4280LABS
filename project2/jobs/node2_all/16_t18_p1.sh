#!/bin/bash
#PBS -N nesh_i16_p1_t18
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:10:00
#PBS -l select=2:ncpus=20:mpiprocs=1:ompthreads=18
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 16_18t1p.o
#PBS -e 18t1p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 16
