#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "random_text_generation.h"

void generateRandomTextFile(const std::string& filename, int size)
{
    std::ofstream outfile(filename);

    //const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    const std::string alphabet = "abcdefghijkl";
    const int W = alphabet.size();

    srand(time(0));
    for (int i = 0; i < size; ++i)
    {
        if (i % 10000 == 0)
            std::cerr << i << "\n";
        char letter = alphabet[rand() % W];
        outfile << letter;
    }

    outfile.close();
}
