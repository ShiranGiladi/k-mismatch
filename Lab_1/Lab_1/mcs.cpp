#include "combinations.h"
//#include "createQueries.h"
#include "mcs.h"

#include <numeric>
#include <algorithm>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <string>

/*std::string readTextFromFile(const std::string& filename)
{
    std::ifstream infile(filename);
    std::stringstream buffer;
    buffer << infile.rdbuf();
    return buffer.str();
}*/

std::vector<Forms> buildMCS(int length, int mismatchK, int matchesPerForm)
{
    std::vector<Forms> resMCS;
    Forms forms;
    forms.N_glob = length; // size of word for search
    forms.N_2_glob = length-mismatchK; // minimal amount of matches
    forms.Nsovp1_Glob = matchesPerForm; // amount of matches in the filter
    std::vector<std::string> allCombinations = forms.generateAllCombinations();
    std::cerr << "done generate all combinations" << "\n";

    std::vector<std::string> allForms = forms.generateAllForms();
    std::cerr << "done generate all forms" << "\n";

    while (!allCombinations.empty())
    {
        std::cout << "Remaining combinations: " << allCombinations.size() << std::endl;

        // Calculate the form that contributes to the maximal number of combinations
        std::pair<std::string, uint64_t> bestFormCount = std::accumulate(allForms.begin(), allForms.end(),
            std::make_pair(std::string(), 0),
            [&](std::pair<std::string, uint64_t> a, const std::string& b) {
                uint64_t count = std::count_if(allCombinations.begin(), allCombinations.end(),
                    [&](const std::string& comb) {
                        return comb.find(b) != std::string::npos;
                    });
                return (count > a.second) ? std::make_pair(b, count) : a;
            });

        // Adding the best form to the MCS
        Forms bestForm;
        // Convert bestFormCount.first to Form object

        resMCS.push_back(bestForm);

        // Removing the combinations containing the best form
        allCombinations.erase(std::remove_if(allCombinations.begin(), allCombinations.end(),
            [&](const std::string& comb) {
                return comb.find(bestFormCount.first) != std::string::npos;
            }), allCombinations.end());
    }

    return resMCS;
}


/*std::map<std::string, std::set<size_t>> mcsSearch(std::vector<std::string> queries, size_t maxMismatchs, std::vector<Forms> mcs)
{
    std::map<std::string, std::vector<size_t>> formMap;
    std::map<std::string, std::vector<size_t>> resultMap;

    std::string text = readTextFromFile("random_text.txt");

    std::for_each(std::execution::par, indices.begin(), indices.end(),
        [&](size_t pos) {
            for (auto& form : mcs)
            {
                if (pos + form.getSize() <= text.size())
                {
                    std::string cur_str = form.getStringFromPosition(text, pos);
                    formMap[cur_str].push_back(pos);
                }
            }
        });

    for (const auto& query : queries)
    {
        for (auto& form : mcs.getMcsForms())
        {
            for (size_t qPos = 0; qPos + form.getSize() <= query.size(); qPos++)
            {
                for (size_t pos : formMap[form.getStringFromPosition(query, qPos)])
                {
                    if (CheckQueryOnPosition(query, pos - qPos, maxMismatchs)) {
                        resultMap[query].insert(pos - qPos);
                    }
                }
            }
        }
    }
    return resultMap;
}*/

/*bool CheckQueryOnPosition(const std::string& query, int64_t position, size_t maxMismatchs)
{
    std::string text = readTextFromFile("random_text.txt");
    if (position + query.size() > text.size() || position < 0)
        return false;

    for (auto& ch : query)
    {
        if (ch != text[position])
        {
            if (maxMismatchs != 0) {
                maxMismatchs--;
            }
            else {
                return false;
            }
        }
        position++;
    }

    return true;
}*/