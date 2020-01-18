#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

std::string ExecuteShellCommand(const char* cmd)
{
    char buffer[128];
    std::string result = "";
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    return result;
}

int main(int argc, char** argv) {
    std::cout <<"\n\n**********************Conducting analytical model validation experiments (Table 6)************************\n";
    std::cout << "1. Estimating speedup for AES-NI case study:\n    Result: ";
    std::cout << ExecuteShellCommand("./accelerometer validation/aesni.txt");

    std::cout << "2. Estimating speedup for Encryption case study:\n    Result: ";
    std::cout << ExecuteShellCommand("./accelerometer validation/encryption.txt");

    std::cout << "3. Estimating speedup for Inference case study:\n    Result: ";
    std::cout << ExecuteShellCommand("./accelerometer validation/inference.txt");

    std::cout <<"\n\n**********************Conducting analytical model application experiments (Figure 17)************************\n";
    std::cout << "1. Estimating speedup for Compression On-chip:Sync application:\n    Result: ";
    std::cout << ExecuteShellCommand("./accelerometer application/compression_on-chip-sync.txt");

    std::cout << "2. Estimating speedup for Compression Off-chip:Sync application:\n    Result: ";
    std::cout << ExecuteShellCommand("./accelerometer application/compression_off-chip-sync.txt");

    std::cout << "3. Estimating speedup for Compression Off-chip:Sync-OS application:\n    Result: ";
    std::cout << ExecuteShellCommand("./accelerometer application/compression_off-chip-sync-os.txt");

    std::cout << "4. Estimating speedup for Compression Off-chip:Async application:\n    Result: ";
    std::cout << ExecuteShellCommand("./accelerometer application/compression_off-chip-async.txt");

    std::cout << "5. Estimating speedup for Memory Copy On-chip:Sync application:\n    Result: ";
    std::cout << ExecuteShellCommand("./accelerometer application/memcpy_on-chip-sync.txt");

    std::cout << "6. Estimating speedup for Memory Allocation On-chip:Sync application:\n    Result: ";
    std::cout << ExecuteShellCommand("./accelerometer application/malloc_on-chip-sync.txt");

    std::cout << "\n\n************************DONE************************\n\n";

    return 0;
}
