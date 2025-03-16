#include "ladder.h"
#include <algorithm>

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
            else {
                int min1 = min(dp[i-1][j], dp[i][j-1]);
                dp[i][j] = 1 + min(min1, dp[i-1][j-1]);
            }
        }
    }
    
    return dp[str1.length()][str2.length()] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
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
    
    ladder_queue.push({begin_word});
    visited.insert(begin_word);
    
    set<string> filtered_words;
    for (const string& word : word_list) {
        if (abs((int)word.length() - (int)begin_word.length()) <= 1 &&
            abs((int)word.length() - (int)end_word.length()) <= 1) {
            filtered_words.insert(word);
        }
    }
    
    while (!ladder_queue.empty()) {
        vector<string> current_ladder = ladder_queue.front();
        ladder_queue.pop();
        
        string last_word = current_ladder.back();
        
        for (const string& word : filtered_words) {
            if (!visited.count(word) && is_adjacent(last_word, word)) {
                vector<string> new_ladder = current_ladder;
                new_ladder.push_back(word);
                
                if (word == end_word) {
                    return new_ladder;
                }
                
                visited.insert(word);
                ladder_queue.push(new_ladder);
            }
        }
    }
    
    return vector<string>();  // No ladder found
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
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i < ladder.size() - 1) cout << " ";
    }
    cout << " " << endl;
}
