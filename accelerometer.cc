#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <vector>

// Globally defining model parameters.
long C = 0, n = 0, o_0 = 0, Q = 0, L = 0, o_1 = 0;
float alpha = 0.0, speedup = 0.0, A = 0.0;
std::string threading = "";

void Sync (void) {
    try {
        speedup = 1.0/( (float)(1-alpha) + (alpha/(float)(A)) + ( ((float)(n)/(float)(C)) * ((float)(o_0) + (float)(L) + (float)(Q)) ) );
    } catch(...) {
        std::cout << "Invalid model parameter values\n";
        exit(0);
    }
}

void SyncOS (void) {
    try {
        speedup = 1.0/( (float)(1-alpha) + ( (float)(n)/(float)(C) * ((float)(o_0) + (float)(L) + (float)(Q) + (float)(o_1)) ) );
    } catch(...) {
        std::cout << "Invalid model parameter values\n";
        exit(0);
    }
}

void Async (void) {
    try {
        speedup = 1.0/( (float)(1-alpha) + ( (float)(n)/(float)(C) * ((float)(o_0) + (float)(L) + (float)(Q)) ) );
    } catch(...) {  
        std::cout << "Invalid model parameter values\n";
        exit(0);                        
    } 
}

int main (int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Format: <./binary> <input file name e.g., validation/aesni.txt>\n";
        exit(0);
    }

    // First read user input to get file containing model parameters.
    std::string parameters_file_name = argv[1];
    std::ifstream parameters_file(parameters_file_name);
    if (!parameters_file.good()) {
        std::cout << "Invalid file: file does not exist\n";
        exit(0);
    }


    // Read file to populate model parameter values.
    std::string line = "";
    int dimension = 0, curr_dimension = 0;

    // Process each file line.
    for(int i = 0; std::getline(parameters_file, line); i++)
    {
        std::istringstream buf(line);
        std::istream_iterator<std::string> begin(buf), end;
        std::vector<std::string> tokens(begin, end);
        // We only need model parameter and its value, error out otherwise.
        if (tokens.size() != 2) {
            std::cout << "input file has the wrong format\n";
            exit(0);
        }

        // Populate model values from the file to global vars.
        switch (i)
        {
        case 0:
            C = atol(tokens[1].c_str());
            break;
        case 1:
            alpha = atof(tokens[1].c_str());
            break;
        case 2:
            n = atol(tokens[1].c_str());
            break;
        case 3:
            o_0 = atol(tokens[1].c_str());
            break;
        case 4:
            Q = atol(tokens[1].c_str());
            break;
        case 5:
            L = atol(tokens[1].c_str());
            break;
        case 6:
            o_1 = atol(tokens[1].c_str());
            break;
        case 7:
            A = atof(tokens[1].c_str());
            break;
        case 8:
            threading = tokens[1];
            break;
        default:
            std::cout << "File can have only 8 lines containing model values\n";
            exit(0);
        } 
    }
    // std::cout << C << " " << alpha << " " << n << " " << o_0 << " " << Q << " " << L << " " << o_1 << " " << A << " " << std::endl;

        // Compute speedup based on the threading model.
        if (threading == "Sync") {
            Sync();
        } else if (threading == "Sync-OS") {
            SyncOS();
        } else if (threading == "Async") {
            Async();
        } else {
            std::cout << "Invalid threading option\n";
            exit(0);
        }


        std::cout << "Estimated speedup in % = " << (speedup - 1.0) * 100.0 << "%\n\n" << std::endl;


        
    return 0;

} 
