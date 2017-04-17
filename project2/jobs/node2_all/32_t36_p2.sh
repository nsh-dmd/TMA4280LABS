#!/bin/bash
#PBS -N nesh_i32_p2_t36
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=2:ncpus=20:mpiprocs=2:ompthreads=36
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 32_36t2p.o
#PBS -e 36t2p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 32
