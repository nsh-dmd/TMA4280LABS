#!/bin/bash
#PBS -N v8
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=2:ncpus=20:mpiprocs=8
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o vtest_8_20.o
#PBS -e vtest_8_20.e
#PBS -q training

cd $PBS_O_WORKDIR

module load gcc
module load openmpi

mpiexec ./vtest 32
mpiexec ./vtest 64
mpiexec ./vtest 128
mpiexec ./vtest 256
mpiexec ./vtest 512
mpiexec ./vtest 1024
mpiexec ./vtest 2048
mpiexec ./vtest 4096
mpiexec ./vtest 8192
mpiexec ./vtest 16384

