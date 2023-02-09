#Metric Based Grid Adaptation using SU2 and NASA/Refine
This repository contains the flow simulation results, meshes, configuration files, and certain small codes written in C++ for postprocessing.

##Get Started
Install the [SU2 package](https://su2code.github.io/) to solve flow simulations and [NASA/Refine](https://github.com/nasa/refine) to run the adaptation cycles.
General recommendation is to install SU2 and refine from source with MPI support (provided by openmpi or [MPICH](https://www.mpich.org/)). Packages have a long dependency list so make sure you read the instructions provided on their documentation/manpages carefully.

##Using SU2
Once installed, using SU2 is really easy. Start with running a couple of test cases and get a hold of the configuration options. An exhaustive list (it is really, really long) of available configuration options are listed with a brief description in the [config_template.cfg](https://github.com/su2code/SU2/blob/master/config_template.cfg) file. Not all configuration options need to be explored, find the relevant ones in your specific [testcases folder](https://github.com/su2code/TestCases) with relevant *.su2 grid files and start getting familiar with the usage.
Run SU2 from the terminal using the command `SU2_CFD config_filename.cfg` for serial processing and `mpirun -n $NP SU2_CFD config_filename.cfg` for parallel processing. $NP is the number of processes(threads) you wish to run. They should ideally not exceed the total number of processors and should be a multiple of 2.