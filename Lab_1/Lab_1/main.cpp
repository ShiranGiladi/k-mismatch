#include <iostream>
#include <vector>

#include "random_text_generation.h"
//#include "position_map_creation.h"
//#include "searchMCS.h"
//#include "forms_generation.h"
#include "createQueries.h"
#include "combinations.h" // TO DELETE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//#include "mcs.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <unordered_map>

using namespace std;

// Function to build a position map based on forms and patterns
/*unordered_map<string, vector<int>> buildPositionMap(const string& text, const vector<string>& patterns, const vector<string>& forms, int wordSize) {
    unordered_map<string, vector<int>> positionMap;
    int count = 0;
    for (const string& pattern : patterns) {
        for (const string& form : forms) {
            string variant;
            for (int i = 0; i < form.length(); ++i) {
                if (form[i] == '1') {
                    variant.push_back(pattern[i]);
                }
                else {
                    variant.push_back('0'); // Placeholder for mismatches
                }
            }
            for (int i = 0; i <= text.size() - wordSize; ++i) {
                bool match = true;
                for (int j = 0; j < wordSize; ++j) {
                    if (form[j] == '1' && text[i + j] != variant[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    positionMap[variant].push_back(i);
                }
            }
        }
        std::cerr << pattern << count << "\n";
        count++;
    }
    return positionMap;
}*/

// Function to build a position map based on forms and patterns
unordered_map<string, vector<int>> buildFormMap(const string& text, const string& pattern, const string& form, int wordSize) {
    unordered_map<string, vector<int>> positionMap;

    //for (const string& form : forms) {
        string variant;
        for (int i = 0; i < form.length(); ++i) {
            if (form[i] == '1') {
                variant.push_back(pattern[i]);
            }
            else {
                variant.push_back('0'); // Placeholder for mismatches
            }
        }
        for (int i = 0; i <= text.size() - wordSize; ++i) {
            bool match = true;
            for (int j = 0; j < wordSize; ++j) {
                if (form[j] == '1' && text[i + j] != variant[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                positionMap[variant].push_back(i);
            }
        }
    //}
    //std::cerr << pattern << "\n";
    
    return positionMap;
}

// Function to search for patterns in the text with up to k mismatches using the position map
vector<int> searchWithMismatches(const string& text, const string& pattern, const unordered_map<string, vector<int>>& positionMap, int wordSize, int mismatches) {
//bool searchWithMismatches(const string& text, const unordered_map<string, vector<int>>& positionMap, int wordSize, int mismatches) {
    vector<int> matches;
    for (const auto& entry : positionMap) {
        //const string& pattern = entry.first;
        const vector<int>& positions = entry.second;
        for (int pos : positions) {
            int mismatchCount = 0;
            for (int i = 0; i < wordSize; ++i) {
                if (text[pos + i] != pattern[i]) {
                    ++mismatchCount;
                    if (mismatchCount > mismatches) {
                        break;
                    }
                }
            }
            if (mismatchCount <= mismatches) {
                matches.push_back(pos);
            }
        }
    }
    return matches;
}

int main()
{
    std::string textFilename = "random_text.txt";
    int textSize = 1000000; // 10M
    int wordSize = 20;       // S = 20
    int misMatchs = 7;
    //int alphabetSize = 10;
    int numberOfQueries = 100000; //100000
    int matchesPerForm = 4;

    generateRandomTextFile(textFilename, textSize);
    std::cerr << "done generate random text" << "\n";

    std::string text = readTextFromFile("random_text.txt");

    std::vector<std::string> queries;
    queries = generateQueries(wordSize, numberOfQueries);
    std::cerr << "done create queries" << "\n";
    
    // Print queries to the screen - Checkkkkkkkkkkkk
    /*for (const auto& query : queries)
    {
        std::cout << query << std::endl;
    }*/

    //MCS build
    Forms forms;
    forms.N_glob = 20; //size of word for search
    forms.N_2_glob = 13; //minimal amount of matches
    forms.Nsovp1_Glob = 5; //amount of matches in the filter

    std::vector<std::string> allCombinations = forms.generateAllCombinations();
    std::cerr << "done generate all combimations" << "\n";
    // Print the combinations - Checkkkkkkkkkkkk
    /*for (const auto& combination : allCombinations) {
        std::cout << combination << std::endl;
    }*/

    std::vector<std::string> mcs = forms.generateAllForms();
    std::cerr << "done generate all forms" << "\n";
    std::cerr << "mcs size: " << mcs.size() << "\n";
    // Print the forms - Checkkkkkkkkkkkk
    /*for (const auto& form : mcs) {
        std::cout << form << std::endl;
    }*/

    // Build position map
    //unordered_map<string, vector<int>> formMap = buildPositionMap(text, queries, mcs, wordSize);

    // Print the position map
    /*for (const auto& entry : positionMap) {
        const string& pattern = entry.first;
        const vector<int>& positions = entry.second;
        cout << "Pattern: " << pattern << ", Positions: ";
        for (int pos : positions) {
            cout << pos << " ";
        }
        cout << endl;
    }*/
    int count = 0;
    unordered_map<string, vector<int>> positionMap;
    for (const string& pattern : queries) {
        std::cerr << count << "\n";
        for (auto& form : mcs) {
            for (size_t qPos = 0; qPos + form.length() <= pattern.length(); qPos++) {
                unordered_map<string, vector<int>> formMap = buildFormMap(text, pattern, form, wordSize);
                vector<int> matches = searchWithMismatches(text, pattern, formMap, wordSize, misMatchs);
                positionMap[pattern] = matches;
            }
        }

        //unordered_map<string, vector<int>> formMap = buildFormMap(text, pattern, mcs, wordSize);
        //vector<int> matches = searchWithMismatches(text, pattern, formMap, wordSize, misMatchs);
        
        //positionMap[pattern] = matches;
        count++;
    }

    int countMatchesAbove2 = 0;
    // Search for patterns in the text with up to k mismatches
    for (const string& pattern : queries) {
        //vector<int> matches = searchWithMismatches(text, positionMap, wordSize, misMatchs);
        cout << "Pattern: " << pattern << ", Matches: " << positionMap[pattern].size() << endl;
        countMatchesAbove2++;
    }
    cout << "Queries Above Two Matches: " << countMatchesAbove2;

    /*for (const auto& entry : positionMap) {
        const string& pattern = entry.first;
        const vector<int>& positions = entry.second;
        cout << "Pattern: " << pattern << ", Positions: ";
        for (int pos : positions) {
            cout << pos << " ";
        }
        cout << endl;
    }
    for (const auto& entry : formMap) {
        const string& form = entry.first;
        const vector<int>& positions = entry.second;
        cout << "Form: " << form << ", Positions: ";
        for (int pos : positions) {
            cout << pos << " ";
        }
        cout << endl;
    }
    for (int m : matches) {
        cout << m << " ";
    }
    cout << endl;
    */

    return 0;
}
