#!/bin/bash
#PBS -N nesh_i512_p4_t12
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=1:ncpus=20:mpiprocs=4:ompthreads=12
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 512_12t4p.o
#PBS -e 12t4p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 512
