#!/bin/bash
#PBS -N nesh_i16_p2_t16
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=1:ncpus=20:mpiprocs=2:ompthreads=16
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 16_16t2p.o
#PBS -e 16t2p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 16
