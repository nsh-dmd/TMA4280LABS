#!/bin/bash
#PBS -N nesh_i4096_p2_t4
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=1:ncpus=20:mpiprocs=2:ompthreads=4
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 4096_4t2p.o
#PBS -e 4t2p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 4096
