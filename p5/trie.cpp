#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

class TrieNode {
public:
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const std::string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }

    bool search(const std::string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return current->isEndOfWord;
    }

    bool startsWith(const std::string& prefix) {
        TrieNode* current = root;
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return true;
    }
};

int main() {
    // {
    // insert entries into the trie using insert from the unordere_map library
    // }

    // { @brief usage of "common" words in programming
    // @link https://stackoverflow.com/questions/34212049/meaning-of-foo-bar-baz-etc
    //}
    Trie trie;

    std::vector<std::string> dummies = {"foo", "bar", "qux", "buz"};

    for(std::string dummy : dummies) {
        trie.insert(dummy);
    }


    // {
    // use of ternary operator, makes the code cleaner
    // @link https://www.programiz.com/cpp-programming/ternary-operator
    // }
    std::cout << "\n\n### [search results] ###\n\n"
              << "[foo]: " << (trie.search("foo") ? "[found]" : "[not found]") 
              << std::endl
              << "[bar]: " << (trie.search("bar") ? "[found]" : "[not found]")
              << std::endl
              << "[golf]: " << (trie.search("golf") ? "[found]" : "[not found]") 
              << std::endl << std::endl;

    std::cout << "[starts w/ 'b']: " << (trie.startsWith("b") ? "[y]" : "[n]") 
              << std::endl
              << "[starts w/ 'bu']: " << (trie.startsWith("bu") ? "[y]" : "[n]") 
              << std::endl << std::endl;
              
    return EXIT_SUCCESS;
}
