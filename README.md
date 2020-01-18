# Accelerometer
The accelerometer analytical model published in ASPLOS 2020 (Accelerometer: Understanding Acceleration Opportunities forData Center Overheads at Hyperscale)


Please follow the following steps to install and run the Accelerometer model:

Step 1: Download the package Accelerometer

Step 2: Decompress the package on a Linux machine with a recent version of GCC installed

Step 3: You should be able to see files such as run.cc, analytical_model.cc, etc

Step 4: Run "make"

Step 5: You should see the two binaries "run" and "accelerometer” created

Step 6: Run "./run" to automatically run all experiments to re-create analytical model validation and application results (i.e., Table 6 and Fig. 17) in the “Accelerometer: Understanding Acceleration Opportunities forData Center Overheads at Hyperscale” paper from ASPLOS 2020.

Step 7: If you want to individually run each of the cases in the analytical model validation (i.e., table 6 in the paper) individually, you can run them like so: "./analytical_model validation/aesni.txt", "./analytical_model validation/encryption.txt", and "./analytical_model validation/inference.txt"

Step 8: If you want to individually run each of the cases in the analytical model application (i.e., Fig. 17 in the paper) individually, you can run them
like so: "./analytical_model application/compression_on-chip-sync.txt", "application/compression_off-chip-sync.txt", "application/compression_off-chip-sync-os.txt", "application/compression_off-chip-async.txt", "application/memcpy_on-chip-sync.txt", and "application/malloc_on-chip-sync.txt"

Step 9: If you want to run the accelerometer model for a new hardware accelerator to estimate its speedup, you must create a file with the following specifications to feed as input to the “accelerometer” program.

C <Total cycles spent by the host to execute all logic in a fixed time unit (in cycles)> 
a <Fraction of cycles spent by the host in running the kernel to be accelerated (in cycles)>
n <Number of times the host offloads a kernel of lucrative size in a fixed time unit>
o0 <Cycles the host spends in setting up the kernel prior to a single offload (in cycles)>
Q <Avg. cycles spent in queuing between host and accelerator for a single offload (in cycles)>
L <Avg. cycles to move an offload from host to accelerator across the interface, including cycles the data spends in caches/memory (in cycles)>
o1 <Cycles spent in switching threads (due to context switches and cache pollution) for a single offload (in cycles)>
A <Peak speedup of an accelerator>
Threading <Threading model (i.e., Sync or Sync-OS or Async)>

