for p in [2, 3, 4, 8, 12, 16, 24, 32, 36]:
    for t in [2, 4, 8, 16]:

        name = "job"+str(p)+"_t"+str(t)+".sh"
        jobFile = open(name, 'a')

        jobFile.write("#!/bin/bash\n")
        jobFile.write("#PBS -N poisson_t"+str(t)+"\n")
        jobFile.write("#PBS -A imf_lille-tma4280\n")
        jobFile.write("#PBS -W group_list=imf_lille-tma4280\n")
        jobFile.write("#PBS -l walltime=00:10:00\n")
        jobFile.write("#PBS -l select=2:ncpus=20:mpiprocs="+str(p)+":ompthreads="+str(t)+"\n")
        jobFile.write("#PBS -m abe\n")
        jobFile.write("#PBS -M neshat.dmd@gmail.com\n")
        jobFile.write("#PBS -o poisson_t"+str(t)+"_p"+str(p)+".o\n")
        jobFile.write("#PBS -e poisson_t"+str(t)+"_p"+str(p)+".e\n")
        jobFile.write("#PBS -q training\n\n\n")


        jobFile.write("cd $PBS_O_WORKDIR\n\n")

        jobFile.write("module load gcc\n")
        jobFile.write("module load openmpi\n")

        for i in [16, 32, 64, 256, 512, 1024, 2048, 4096, 8192, 16384]:
            jobFile.write("mpiexec ./poisson" + str(i)+"\n")

        jobFile.close()
