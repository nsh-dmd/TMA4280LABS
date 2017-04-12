#!/bin/bash
#PBS -N poisson_t4
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:20:00
#PBS -l select=2:ncpus=20:ompthreads=4
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o poisson_t4.o
#PBS -e poisson_t4.e
#PBS -q training


cd $PBS_O_WORKDIR

module load gcc
module load openmpi

for n in 16 32 64 256 512 2048 4096 16384
do
    mpiexec -np 1 ./poisson $n
    mpiexec -np 2 ./poisson $n
    mpiexec -np 3 ./poisson $n
    mpiexec -np 4 ./poisson $n
    mpiexec -np 6 ./poisson $n
    mpiexec -np 8 ./poisson $n
    mpiexec -np 16 ./poisson $n
    mpiexec -np 18 ./poisson $n
    mpiexec -np 32 ./poisson $n
    mpiexec -np 36 ./poisson $n
done
