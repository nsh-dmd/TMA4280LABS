#!/bin/bash
#PBS -N nesh_i8192_p36_t36
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=2:ncpus=20:mpiprocs=36:ompthreads=36
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 8192_36t36p.o
#PBS -e 36t36p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 8192
