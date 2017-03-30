#!/bin/bash
#PBS -N recur
#PBS -A imf_lille-tma4280
#PBS -W group_list=imf_lille-tma4280
#PBS -l walltime=00:05:00
#PBS -l select=2:ncpus=20:mpiprocs=2
#PBS -m abe
#PBS -M neshat.dmd@gmail.com
#PBS -o rec_2_20.o
#PBS -e rec_2_20.e
#PBS -q training

cd $PBS_O_WORKDIR

module load gcc
module load openmpi

mpiexec ./recur 32
mpiexec ./recur 64
mpiexec ./recur 128
mpiexec ./recur 256
mpiexec ./recur 512
mpiexec ./recur 1024
mpiexec ./recur 2048
mpiexec ./recur 4096
mpiexec ./recur 8192
mpiexec ./recur 16384

