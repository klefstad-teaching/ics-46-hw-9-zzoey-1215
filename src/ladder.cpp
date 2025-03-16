#include "ladder.h"
#include <algorithm>
#include <queue>
#include <set>
#include <vector>

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error with words '" << word1 << "' and '" << word2 << "': " << msg << endl;
}

vector<string> generate_neighbors(const string& word) {
    vector<string> neighbors;

    // Generate substitutions
    for (size_t i = 0; i < word.size(); ++i) {
        char original = word[i];
        for (char c = 'a'; c <= 'z'; ++c) {
            if (c == original) continue;
            string new_word = word;
            new_word[i] = c;
            neighbors.push_back(new_word);
        }
    }

    // Generate insertions
    for (size_t i = 0; i <= word.size(); ++i) {
        for (char c = 'a'; c <= 'z'; ++c) {
            string new_word = word.substr(0, i) + c + word.substr(i);
            neighbors.push_back(new_word);
        }
    }

    // Generate deletions
    for (size_t i = 0; i < word.size(); ++i) {
        string new_word = word.substr(0, i) + word.substr(i + 1);
        neighbors.push_back(new_word);
    }

    return neighbors;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return vector<string>();
    }

    if (word_list.find(end_word) == word_list.end()) {
        return vector<string>();
    }

    queue<vector<string>> ladder_queue;
    set<string> visited;

    vector<string> initial_ladder = {begin_word};
    ladder_queue.push(initial_ladder);
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = current_ladder.back();

        vector<string> neighbors = generate_neighbors(last_word);

        for (const string& neighbor : neighbors) {
            if (neighbor == end_word) {
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(neighbor);
                return new_ladder;
            }

            if (word_list.count(neighbor) && !visited.count(neighbor)) {
                visited.insert(neighbor);
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(neighbor);
                ladder_queue.push(new_ladder);
            }
        }
    }

    return vector<string>(); // No ladder found
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        throw runtime_error("Cannot open word file: " + file_name);
    }

    string word;
    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word_list.insert(word);
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }

    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
}