/*
Name: Aaryan Sharma
CS 251 (Fall 2023) - Prof Drishika Dey
Project - 2 (Search)
*/

#include "search.h"
using namespace std;


bool testCleanToken() {
    /*
     * This function tests the cleanToken function against the string "ans", containing the correct cleaned token.
     */
    string ans = "hello";
    int pass = 0, fail = 0;

    ans == cleanToken(".hello") ? ++pass : ++fail;
    ans == cleanToken("...hello") ? ++pass : ++fail;

    return 0 == fail;
}


bool testGatherToken() {
    /*
     * This function tests the gatherToken function against the set "ans", containing all of the correct cleaned tokens.
     */
    set<string> ans ({"eggs", "milk", "fish", "bread", "cheese"});
    set<string> test = gatherTokens("EGGS! milk, fish,      @  bread cheese");

    if (ans == test) {                                                                                                  // Prints out a statement and returns true.
        return true;
    }

    else {                                                                                                              // Prints the set difference in case function doesn't work perfectly.
        set<string> diff;
        set_difference(test.begin(), test.end(),ans.begin(), ans.end(), inserter(diff, diff.end()));

        cout << "The following elements are missing from the set:"<< endl;
        for (auto i=diff.begin(); i!=diff.end(); i++) {
            cout << *i << endl;
        }
        return false;
    }
}


bool testBuildIndex() {
    /*
     * This function tests the buildIndex function, by calling it for the "tiny.txt" file.
     */
    map<string, set<string>> ansIndex;

    ansIndex["eggs"].insert("www.shoppinglist.com");
    ansIndex["milk"].insert("www.shoppinglist.com");
    ansIndex["fish"].insert("www.shoppinglist.com");
    ansIndex["bread"].insert("www.shoppinglist.com");
    ansIndex["cheese"].insert("www.shoppinglist.com");

    ansIndex["red"].insert("www.rainbow.org");
    ansIndex["green"].insert("www.rainbow.org");
    ansIndex["orange"].insert("www.rainbow.org");
    ansIndex["yellow"].insert("www.rainbow.org");
    ansIndex["blue"].insert("www.rainbow.org");
    ansIndex["indigo"].insert("www.rainbow.org");
    ansIndex["violet"].insert("www.rainbow.org");

    ansIndex["one"].insert("www.dr.seuss.net");
    ansIndex["fish"].insert("www.dr.seuss.net");
    ansIndex["two"].insert("www.dr.seuss.net");
    ansIndex["red"].insert("www.dr.seuss.net");
    ansIndex["blue"].insert("www.dr.seuss.net");

    ansIndex["i'm"].insert("www.bigbadwolf.com");
    ansIndex["not"].insert("www.bigbadwolf.com");
    ansIndex["trying"].insert("www.bigbadwolf.com");
    ansIndex["to"].insert("www.bigbadwolf.com");
    ansIndex["eat"].insert("www.bigbadwolf.com");
    ansIndex["you"].insert("www.bigbadwolf.com");

    map<string, set<string>> testIndex;
    buildIndex("tiny.txt", testIndex);

    if (testIndex == ansIndex) {                                                                                        // comparing the two maps "testIndex" and "ansIndex".
        return true;
    }

    cout << "The inverted index map is built incorrectly." << endl;
    return false;
}


bool testFindQuery() {
    /*
     * This function is used to test the findQuery function, where the sentence is "green +eggs".
     */
    map<string, set<string>> testIndex;
    buildIndex("tiny.txt", testIndex);

    set<string> matches = findQueryMatches(testIndex, "green +eggs");

    if (matches.empty()) {
        return true;
    }


    cout << "Query 'green +eggs' returned some matches." << endl;
    return false;

}


int main() {

    string filename;
    cout << "Enter the filename: " << endl;
    getline(cin, filename);
    searchEngine(filename);

    cout << "\n<<< Testing >>>" << endl;

    cout << "  Testing cleanToken:" << endl;
    if (testCleanToken()) {
        cout << "    Test case passed." << endl;
    }
    else {
        cout << "    Test case failed." << endl;
    }

    cout << "\n  Testing gatherToken:" << endl;
    if (testGatherToken()) {
        cout << "    Test case passed." << endl;
    }
    else {
        cout << "    Test case failed." << endl;
    }

    cout << "\n  Testing buildIndex:" << endl;
    if (testBuildIndex()) {
        cout << "    Test case passed." << endl;
    }
    else {
        cout << "    Test case failed." << endl;
    }

    cout << "\n  Testing findQuery:" << endl;

    if (testFindQuery()) {
        cout << "    Test case passed." << endl;
    }

    else {
        cout << "    Test case failed." << endl;
    }




    return 0;
}

