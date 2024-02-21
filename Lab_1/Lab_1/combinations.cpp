#ifndef _INC_forms1
#define _INC_forms1

#include "combinations.h"
//#include "forms_generation.h"
#include <vector>
#include <fstream>

bool Forms::FindWord(std::ifstream& fin, std::string aaa)
{
    char a1, a2;
    int i;
    char buf[1000];

    //cerr << "\nT_ " << aaa[0];

    while (!fin.eof())
    {
        for (i = 0; i < aaa.length(); i++)
        {
            fin.get(a1);
            if (a1 == aaa[i]) continue;
            else
                break;
        }

        if (i == aaa.length()) return(1);

    }
    return (0);
}

double Forms::degInt(int n, double q)
{
    double a = 1.0;
    for (int i = 0; i < n; i++)
        a = a * q;
    return (a);
}

std::vector<std::string> Forms::generateAllCombinations()
{
    std::vector<std::string> allCombinations;

    int i, j, i1, n, n1;

    int N = N_glob;
    int N_2 = N_2_glob;

    int* mas1, * mas2;
    mas1 = new int[N];
    mas2 = new int[N];

    for (i = 0; i < N; i++)
        mas1[i] = degInt(i, 2);

    double d1;

    d1 = 1.0;
    n = N - N_2;
    for (i = 0; i < n; i++)
        d1 = d1 * (N - i) / double(n - i);

    int Nmas = int(d1) + 1;

    NVars_Glob = 0;

    Vars_Glob = new bool* [Nmas];
    for (i = 0; i < Nmas; i++)
        Vars_Glob[i] = new bool[N];

    for (i = 0; i < Nmas; i++)
        for (j = 0; j < N; j++)
            Vars_Glob[i][j] = 0;

    for (i = 0; i < degInt(N, 2); i++)
    {
        // Generation of all the match/mismatch combinations
        n1 = 0;
        n = i;
        for (i1 = N - 1; i1 >= 0; i1--)
        {
            mas2[i1] = int(n / mas1[i1]); // i1-position in cod binary
            n1 += mas2[i1]; // calculate amount of "1"
            n = n - (mas2[i1] * mas1[i1]);
        }

        if (n1 != N_2) continue;
        if (mas2[0] != 1) continue;

        for (j = 0; j < N; j++)
            Vars_Glob[NVars_Glob][j] = mas2[j];

        std::string combination(N, '0');
        for (j = 0; j < N; j++)
            combination[j] = mas2[j] + '0';

        allCombinations.push_back(combination);

        NVars_Glob++;

        //if (NVars_Glob % 100 == 0)
            //std::cerr << "\n " << NVars_Glob;

        if (NVars_Glob > Nmas)
        {
            std::cerr << "\n NVars_Glob > Nmas";
            return allCombinations;
        }
    }

    return allCombinations;
}


#endif  // _INC_forms1
