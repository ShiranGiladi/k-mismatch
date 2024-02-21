#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include "searchMCS.h"

// Function to search for MCSs in the random text using the position map
void searchMCSs(const std::string& textFilename, int wordSize, const std::map<std::string, std::vector<int>>& positionMap)
{
    // Read the forms from file
    std::ifstream formFile("forms");
    std::vector<std::vector<int>> forms;
    std::string formLine;
    while (std::getline(formFile, formLine))
    {
        std::istringstream iss(formLine);
        std::vector<int> form;
        int val;
        while (iss >> val)
        {
            form.push_back(val);
        }
        forms.push_back(form);
    }
    formFile.close();

    // Use the forms for MCS search
    for (const auto& form : forms)
    {
        // Ensure form has at least two elements
        if (form.size() < 2)
        {
            std::cerr << "Invalid form format\n";
            continue;
        }

        std::string formString;
        for (size_t i = 1; i < form.size(); ++i)
        {
            formString += std::to_string(form[i]);
        }

        for (const auto& entry : positionMap)
        {
            const std::string& query = entry.first;
            const std::vector<int>& positions = entry.second;

            if (positions.empty())
            {
                continue;
            }

            // Ensure form[0] is a valid index for positions
            if (form[0] < 0 || form[0] >= static_cast<int>(positions.size()))
            {
                std::cerr << "Invalid form index\n";
                continue;
            }

            for (size_t i = 0; i <= positions.size() - form[0]; ++i)
            {
                if (query.substr(positions[i], formString.size()) == formString)
                {
                    // Word found using MCS algorithm
                    std::string foundWord = query.substr(positions[i], formString.size());
                    std::cout << "Found MCS at position " << positions[i] << ": " << foundWord << std::endl;
                }
            }
        }
    }

}