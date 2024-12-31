#include "iostream"
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h>
using namespace std;

void initializePatterns(vector<string> & words, unordered_map<string, bool> & patterns) {
    for (auto word : words) {
        patterns[word] = false;
    }
}

void getLen(vector<string> & words, int & total_word_len) {
    for (auto word : words) {
        total_word_len += word.size();
    }
}

int main() {
    string s = "barfoofoobarthefoobarman";
    vector<string> words = {"bar","foo","the"};
    string temp;
    vector<int> ans;
    int left = 0, right = 0, total_word_len = 0, wordlen = words[0].size();
    unordered_map<string, bool> patterns;
    getLen(words, total_word_len);
    initializePatterns(words, patterns);
    

    int i = 0;
    for (; right < s.size(); right++) {
        if (temp.size() == wordlen) {
            if (patterns.find(temp) != patterns.end() && patterns[temp] == false) {
                patterns[temp] = true;
            }
            else {
                initializePatterns(words, patterns);
            }
            int word_visited_len = 1;
            for (auto word_visited : patterns) {
                if (!word_visited.second) {
                    break;
                }
                if (word_visited_len == words.size()) {
                    left = right - total_word_len;
                    ans.push_back(left);
                    initializePatterns(words, patterns);
                }
                word_visited_len += 1;
            }
            temp = "";
            i += 1;
            right = i;
        }
        temp += s[right];
    }

    for (auto j : ans) {
        cout << j << ", ";
    }

    return 0;
}