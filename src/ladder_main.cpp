#include "ladder.h"
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    try {
        set<string> word_list;
        load_words(word_list, "words.txt");  // Load dictionary

        string start_word, end_word;
        cout << "Enter start word: ";
        cin >> start_word;
        cout << "Enter end word: ";
        cin >> end_word;

        transform(start_word.begin(), start_word.end(), start_word.begin(), ::tolower);
        transform(end_word.begin(), end_word.end(), end_word.begin(), ::tolower);

        if (start_word == end_word) {
            error(start_word, end_word, "Start and end words must be different");
            return 1;
        }

        if (word_list.find(end_word) == word_list.end()) {
            error(start_word, end_word, "End word must be in dictionary");
            return 1;
        }

        vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
        print_word_ladder(ladder);

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}