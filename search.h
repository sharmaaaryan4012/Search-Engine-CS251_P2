/*
Name: Aaryan Sharma
CS 251 (Fall 2023) - Prof Drishika Dey
Search.h
*/

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <map>
#include <algorithm>
#include <iterator>
using namespace std;

string cleanToken(string s) {
    /*
     * This function trims edge punctuation, converts to lowercase, and discards non-alphabetic tokens
     */

    int count = 0;
    for (int i=0; i<s.length(); i++) {
        if (isalpha(s[i])) {                                                                                         // In case the character is an alphabet: 1. count is incremented and 2. the character is converted to lowercase.
            count++;
            s[i]= tolower(s[i]);
        }
    }

    if (count == 0) {                                                                                                   // If there are no alphabets in the string, an empty string is returned.
        return "";
    }

    int front = 0;                                                                                                      // Defining two iterators, front increments and back decrements.
    int back = s.length()-1;

    while (ispunct(s[front])) {                                                                                      // "front" is incremented until the character is not a punctuation.
        front++;
    }

    while (ispunct(s[back])) {                                                                                       // "back" is decremented until the character is not a punctuation.
        back--;
    }

    s = s.substr(front, (back-front)+1);                                                                        // the token is cleaned using the substr functionality.


    return s;
}


void splitString(string line, char delimiter, set<string>& items ) {
    /*
     * This is a helper function, which spits the "line" parameter, formats the "item" string and adds it to the "items" set.
     */

    stringstream s_stream(line);

    while (s_stream.good()) {
        string item;
        getline(s_stream, item, delimiter);                                                                  // Split the string using the delimiter.
        item = cleanToken(item);                                                                                     // Employing the "cleanToken" function to format the "item" string.
        if (item != "") {
            items.emplace(item);                                                                                        // Adding the item to a set.
        }
    }
}


void splitStringVector(string line, char delimiter, vector<string>& items ) {
    /*
     * This is a helper function, which spits the "line" parameter, formats the "item" string and adds it to the "items" vector.
     */

    stringstream s_stream(line);

    while (s_stream.good()) {
        string item;
        getline(s_stream, item, delimiter);                                                                  // Split the string using the delimiter.
        if (item != "") {
            items.push_back(item);                                                                                      // Adding the item to a vector of strings.
        }
    }
}


set<string> gatherTokens(string text) {
    /*
    * This function extracts a set of unique tokens from the body text.
    */

    set<string> tokens;

    splitString(text,' ', tokens);

    return tokens;
}


int buildIndex(string filename, map<string, set<string>>& index) {
    /*
     * This function processes the content from a file and gives out an inverted index.
     */

    ifstream object;
    object.open(filename);                                                                                           // Creating a file object, and opening the file of user's choice.
    int countPage = 0;
    if (object.is_open()) {
        while (!object.eof()) {
            string url;
            string tokens;
            getline(object, url);                                                                                 // Withing the while loop, the getline function is used twice, in order to read the URL and the Tokens together.
            if (url == "") {                                                                                            // In case the url is an empty string, we do not add to the "index" map.
                break;
            }
            countPage++;
            getline(object, tokens);

            set<string> tokenSet = gatherTokens(tokens);
            for (auto i:tokenSet) {                                                                              // Traversing through the tokenSet and inserting urls to the inverse index map.
                index[i].insert(url);
            }
        }
    }

    object.close();

    return countPage;
}


set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    /*
     * This function is used to find the query matches based on user input(string sentence), from the index map that we built in the last function.
     */

    set<string> s1;
    set<string> result;
    string seperator;
    char modType;
    int count = 0;
    stringstream s(sentence);

    while (s >> seperator) {
        count++;
        if (seperator[0] == '+' || seperator[0] == '-') {                                                               // In case the first character of the string "seperator" is a modifier, we skip it and store the rest into "seperator".
            modType = seperator[0];
            seperator = seperator.substr(1);
            s1 = index.at(seperator);
        }
        else {                                                                                                          // Else, we set the modType as ' ', so that identification is easier later on.
            modType = ' ';
            s1 = index.at(seperator);
        }

        if (result.size() == 0 && count == 1) {
            result = s1;
            continue;
        }

        set<string>tempResult = result;
        result.clear();
        if (modType != '+' && modType != '-') {                                                                         // If the modifier is neither "+" nor "-", we take the set union.
            set_union(tempResult.begin(),tempResult.end(),s1.begin(),s1.end(),inserter(result, result.begin()));
        }
        else if (modType == '-') {                                                                                      // If the modifier is "-", we calculate the set difference.
            set_difference(tempResult.begin(),tempResult.end(),s1.begin(),s1.end(),inserter(result, result.begin()));
        }
        else {                                                                                                          // If the modifier is "+", we calculate the intersection.
            set_intersection(tempResult.begin(),tempResult.end(),s1.begin(),s1.end(),inserter(result, result.begin()));
        }
    }
    return result;
}


void searchEngine(string filename) {
    /*
     * This function combines all of the previous functions, in order to run the Search Engine functionality.
     */

    cout << "Stand by while building index..." << endl;                                                                 // Initial statement.

    map<string, set<string>> index;                                                                                     // Constructing an inverted index from the contents of the file "filename".
    int pages = buildIndex(filename, index);
    cout << "Indexed " << pages << " pages containing " << index.size() << " unique terms" << endl << endl;

    string querySentence;
    cout << "Enter query sentence (press enter to quit): ";
    getline(cin, querySentence);

    while (querySentence != "") {

        set<string> matches = findQueryMatches(index, querySentence);
        cout << "Found " << matches.size() << " matching pages" << endl;
        for (auto i=matches.begin(); i!=matches.end(); i++) {
            cout << *i << endl;
        }
        cout << endl;
        cout << "Enter query sentence (press enter to quit): ";
        getline(cin, querySentence);
    }

    cout << "Thank you for searching!" << endl;
}