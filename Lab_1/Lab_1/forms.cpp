#include "combinations.h"

#include <vector>
#include <fstream>
#include <sstream>

std::vector<std::string> Forms::generateAllForms()
{
    std::vector<std::string> allForms;

    int i, i1, j1, j2, k, n1, Nform, flag1;

    int N = N_glob;
    int N_2 = N_2_glob;
    int Nsovp = Nsovp1_Glob;

    int NformMax = 10000; // maximal amount of forms
    int** forms = new int* [NformMax];
    for (i = 0; i < NformMax; i++)
        forms[i] = new int[N + 1];

    for (i = 0; i < NformMax; i++)
        for (j1 = 0; j1 < N; j1++)
            forms[i][j1] = 0;

    for (i = 0; i < NformMax; i++)
    {
        forms[i][N] = -1;
        forms[i][0] = 1;
    }

    k = 0;
    Nform = 0;

    //print Vars_Glob values - Checkkkkkkkkkkkkkkkkkkkk
    /*for (i = 0; i < NVars_Glob; i++)
    {
        for (j1 = 0; j1 < N; j1++)
        {
            std::cout << Vars_Glob[i][j1] << " ";
        }
        std::cout << std::endl;
    }*/


    for (i = 0; i < NVars_Glob; i++)
    {
        flag1 = 1;
        for (i1 = 0; i1 < Nform; i1++)
        {
            for (j1 = 0; j1 <= N - forms[i1][N]; j1++)
            {
                if (Vars_Glob[i][j1] == 0) continue;

                flag1 = 0;
                for (j2 = 1; j2 < forms[i1][N]; j2++)
                {
                    if (forms[i1][j2] == 0) continue;

                    if (Vars_Glob[i][j1 + j2] != 1)
                    {
                        flag1 = 1;
                        break;
                    }
                }

                if (flag1 == 0) break; // a form is found, goto the next combination
            }

            if (flag1 == 0) break;
        }

        if (flag1 == 0) continue;

        for (j1 = 0; j1 < N; j1++)
        {
            if (Vars_Glob[i][j1] == 0) continue;

            n1 = 1;
            for (j2 = 1; j2 < N; j2++)
            {
                forms[Nform][j2] = Vars_Glob[i][j2 + j1];

                if (forms[Nform][j2] == 1)
                    n1++;

                if (n1 == Nsovp)
                {
                    forms[Nform][N] = j2 + 1; // size of the form
                    Nform++;
                    break;
                }
            }

            break;
        }

        if (Nform == NformMax)
            break;
    }

    for (i1 = 0; i1 < Nform; i1++)
    {
        std::string form;
        for (j1 = 0; j1 < N; j1++)
            form += std::to_string(forms[i1][j1]);

        allForms.push_back(form);
    }

    ///////////////////copy to forms_Glob
    Nform1_Glob = Nform;
    form1Size = N + 1;

    forms1Glob = new int* [Nform1_Glob];
    for (i = 0; i < Nform1_Glob; i++)
        forms1Glob[i] = new int[form1Size];

    for (i1 = 0; i1 < Nform1_Glob; i1++)
        for (j1 = 0; j1 < form1Size; j1++)
            forms1Glob[i1][j1] = forms[i1][j1];
    ///////////////////////////////////////

    for (i = 0; i < NformMax; i++)
        delete[] forms[i];
    delete[] forms;

    std::vector<std::string> trimmedForms = removeTrailingZeros(allForms);

    return trimmedForms;
}

std::vector<std::string> removeTrailingZeros(const std::vector<std::string>& allForms)
{
    std::vector<std::string> trimmedForms;

    for (const std::string& form : allForms)
    {
        size_t lastOne = form.find_last_of('1');
        trimmedForms.push_back(form.substr(0, lastOne + 1));
    }

    return trimmedForms;
}