#!/bin/bash
#PBS -N poisson_t4
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:20:00
#PBS -l select=2:ncpus=20:ompthreads=4:mpiprocs=4
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o poisson_t4_p4.o
#PBS -e poisson_t4_p4.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi

for n in 16 32 64 256 512 1024 2048 4096 8192 16384
do
    mpiexec ./poisson $n
    mpiexec ./poisson $n
    mpiexec ./poisson $n
    mpiexec ./poisson $n
    mpiexec ./poisson $n
    mpiexec ./poisson $n
    mpiexec ./poisson $n
    mpiexec ./poisson $n
    mpiexec ./poisson $n
    mpiexec ./poisson $n
done
