#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "forms_generation.h"

void generateForms(int N, int N_2, int Nsovp1)
{
    int* mas1, * mas2;
    mas1 = new int[N];
    mas2 = new int[N];

    for (int i = 0; i < N; i++)
        mas1[i] = pow(2, i);

    double d1 = 1.0;
    int n = N - N_2;
    for (int i = 0; i < n; i++)
        d1 = d1 * (N - i) / double(n - i);

    int Nmas = int(d1) + 1;

    bool** Vars_Glob;
    int NVars_Glob = 0;

    Vars_Glob = new bool* [Nmas];
    for (int i = 0; i < Nmas; i++)
        Vars_Glob[i] = new bool[N];

    for (int i = 0; i < Nmas; i++)
        for (int j = 0; j < N; j++)
            Vars_Glob[i][j] = 0;

    std::ofstream fout("forms");

    /*for (int i = 0; i < pow(2, N); i++)
    {
        for (int j = 0; j < N; j++)
            fout << Vars_Glob[i][j];

        fout << std::endl;

        NVars_Glob++;

        if (NVars_Glob > Nmas)
        {
            std::cerr << "\n NVars_Glob > Nmas";
            return;
        }
    }*/

    for (int i = 0; i < Nmas; i++)
    {
        for (int j = 0; j < N; j++)
            fout << Vars_Glob[i][j];

        fout << std::endl;

        NVars_Glob++;

        if (NVars_Glob > Nmas)
        {
            std::cerr << "\n NVars_Glob > Nmas";
            break;
        }
    }


    fout.close();
}

/*int main()
{
    int N = 20;       // Size of word for search
    int N_2 = 13;     // Minimal amount of matches
    int Nsovp1 = 4;   // Amount of matches in the filter

    generateForms(N, N_2, Nsovp1);

    return 0;
}*/
