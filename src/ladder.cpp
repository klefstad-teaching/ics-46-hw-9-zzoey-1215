#include "ladder.h"
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include <climits>

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error with words '" << word1 << "' and '" << word2 << "': " << msg << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    if (abs((int)str1.length() - (int)str2.length()) > d) return false;
    
    vector<vector<int>> dp(str1.length() + 1, vector<int>(str2.length() + 1));
    
    for (size_t i = 0; i <= str1.length(); i++)
        dp[i][0] = i;
    for (size_t j = 0; j <= str2.length(); j++)
        dp[0][j] = j;
        
    for (size_t i = 1; i <= str1.length(); i++) {
        for (size_t j = 1; j <= str2.length(); j++) {
            if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }
    return dp[str1.length()][str2.length()] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_neighbors(const string& word) {
    vector<string> neighbors;
    const string letters = "abcdefghijklmnopqrstuvwxyz";

    for (size_t i = 0; i <= word.size(); ++i) {
        for (char c : letters) {
            neighbors.push_back(word.substr(0, i) + c + word.substr(i));
        }
    }

    for (size_t i = 0; i < word.size(); ++i) {
        neighbors.push_back(word.substr(0, i) + word.substr(i + 1));
    }

    for (size_t i = 0; i < word.size(); ++i) {
        for (char c : letters) {
            if (c == word[i]) continue;
            string neighbor = word;
            neighbor[i] = c;
            neighbors.push_back(neighbor);
        }
    }

    return neighbors;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) return {};

    if (!word_list.count(end_word)) {
        return {};
    }

    queue<vector<string>> ladder_queue;
    set<string> visited;

    ladder_queue.push({begin_word});
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        auto current_ladder = ladder_queue.front();
        ladder_queue.pop();

        string last_word = current_ladder.back();
        vector<string> neighbors = generate_neighbors(last_word);

        for (const string& neighbor : neighbors) {
            if (neighbor == end_word) {
                current_ladder.push_back(neighbor);
                return current_ladder;
            }

            if (word_list.count(neighbor) && !visited.count(neighbor)) {
                visited.insert(neighbor);
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(neighbor);
                ladder_queue.push(new_ladder);
            }
        }
    }

    return {};  // No ladder found
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) throw runtime_error("Cannot open file: " + file_name);

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

    cout << "Word ladder found:";
    for (const auto& word : ladder) {
        cout << " " << word;
    }
    cout << endl;
}