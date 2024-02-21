#ifndef _INC_MAIN
#define _INC_MAIN

//#include "combinations.h"

#include <atlstr.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>

class Forms
{
public:
    int Nform1_Glob;
    int form1Size;
    int Nsovp1_Glob;
    int N_2_glob;
    int N_glob;
    int** forms1Glob;
    bool** Vars_Glob;
    int* VarsDescr_Glob;
    int NVars_Glob;
    int* NForms_pos_Glob;
    int*** forms1_pos_Glob;
    int* SeqPos;

    // Constructor
    Forms()
    {
        forms1Glob = nullptr; // Initialize to nullptr
    }

    // Destructor
    ~Forms()
    {
        // Deallocate memory for forms1Glob
        if (forms1Glob != nullptr)
        {
            for (int i = 0; i < Nform1_Glob; i++)
                delete[] forms1Glob[i];
            delete[] forms1Glob;
        }
    }

    bool FindWord(std::ifstream&, std::string);
    //void Read_Forms1(std::string);
    double degInt(int, double);

    std::vector<std::string> generateAllCombinations();
    std::vector<std::string> generateAllForms();

    std::vector<std::string> getForms() const {
        std::vector<std::string> formsVector;
        for (int i = 0; i < Nform1_Glob; i++) {
            std::string form;
            for (int j = 0; j < form1Size; j++) {
                form += std::to_string(forms1Glob[i][j]);
            }
            formsVector.push_back(form);
        }
        return formsVector;
    }
};

std::vector<std::string> removeTrailingZeros(const std::vector<std::string>& allForms);

class Combination {
public:
    std::vector<bool> bits;

    Combination(int size) : bits(size, false) {}

    void generate(int wordSize, int misMatchs);

    friend std::ostream& operator<<(std::ostream& os, const Combination& combination);
};

#endif  //_INC_MAIN
