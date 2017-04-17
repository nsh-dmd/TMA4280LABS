#!/bin/bash
#PBS -N nesh_i8192_p2_t6
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=1:ncpus=20:mpiprocs=2:ompthreads=6
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 8192_6t2p.o
#PBS -e 6t2p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 8192
