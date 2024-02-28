
#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;

    void insertWord(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }

    void findWordsWithPrefix(TrieNode* node, string prefix, vector<string>& suggestions) {
        if (node->isEndOfWord) {
            suggestions.push_back(prefix);
        }

        for (auto& child : node->children) {
            findWordsWithPrefix(child.second, prefix + child.first, suggestions);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void buildTrie(const vector<string>& words) {
        for (const string& word : words) {
            insertWord(word);
        }
    }

    vector<string> autocomplete(const string& prefix) {
        TrieNode* current = root;
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return {};
            }
            current = current->children[c];
        }

        vector<string> suggestions;
        findWordsWithPrefix(current, prefix, suggestions);
        return suggestions;
    }
};

int main() {

    Trie trie;

    //я записал слова для каждой буквы английского алфавита, некоторых небывает, я придумал их сам
    vector<string> dictionary = { "apple", "banana", "orange", "grape", "pineapple", "cat", "quiq", "wolf", "eagle", "root", "torf",
    "yeard", "ufo", "ice", "opus", "put", "sad", "dad", "falcon", "google", "hood", "joker", "klan", "lemon", "zebra", "x-ray", "ven",
        "bamby", "nurse", "moon"
    };
    trie.buildTrie(dictionary);

    while (true) {
        cout << "Enter a prefix to autocomplete (or 'exit' to quit): ";
        string prefix;
        cin >> prefix;

        if (prefix == "exit") {
            break;
        }

        vector<string> suggestions = trie.autocomplete(prefix);
        if (suggestions.empty()) {
            cout << "No suggestions found." << endl;
        }
        else {
            cout << "Suggestions:" << endl;
            for (const string& word : suggestions) {
                cout << word << endl;
            }
        }
    }

    return 0;
}