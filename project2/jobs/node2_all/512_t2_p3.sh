#!/bin/bash
#PBS -N nesh_i512_p3_t2
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=2:ncpus=20:mpiprocs=3:ompthreads=2
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o 512_2t3p.o
#PBS -e 2t3p.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi
mpiexec ./poisson 512
