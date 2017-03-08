#!/bin/bash
#PBS -N mach012H
#PBS -A imf_tma4280
#PBS -l walltime=00:01:00
#PBS -l select=2:ncpus=20:mpiprocs=16
#PBS -m abe
#PBS -M neshat.dmd@gmail.com

cd $PBS_O_WORKDIR
 
module load gcc
module load openmpi
 
mpiexec ./zeta1 1028
mpiexec ./mach1 1028

mv *.e* jobs/
mv *.o* jobs/
