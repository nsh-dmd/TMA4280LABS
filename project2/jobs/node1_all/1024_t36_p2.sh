#!/bin/bash
#PBS -N nesh_i1024_p2_t36
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=1:ncpus=20:mpiprocs=2:ompthreads=36
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 1024_36t2p.o
#PBS -e 36t2p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 1024
