// Write a C++ program to implement Huffman coding text compression algorithm. Build the Huffman Tree using characters and their frequencies input from user. Encode a given string by using codes generated from Huffman tree and decode the bit sequence entered by the user

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

// A Huffman tree node
class Node {
public:
    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = nullptr;
        right = nullptr;
    }
};

// Comparison object to be used to order the heap
class Compare {
public:
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// Function to build the Huffman tree and return the root
Node* buildHuffmanTree(unordered_map<char, int>& freq) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto& pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        pq.push(top);
    }

    return pq.top();
}

// Function to generate the Huffman codes
void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '$') {
        huffmanCode[root->data] = code;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// Function to encode the input string
string encode(string str, unordered_map<char, string>& huffmanCode) {
    string encodedString = "";

    for (char c : str) {
        encodedString += huffmanCode[c];
    }

    return encodedString;
}

// Function to decode the input bit sequence
string decode(string str, Node* root) {
    string decodedString = "";
    Node* curr = root;

    for (char c : str) {
        if (c == '0') {
            curr = curr->left;
        } else {
            curr = curr->right;
        }

        if (curr->left == nullptr && curr->right == nullptr) {
            decodedString += curr->data;
            curr = root;
        }
    }

    return decodedString;
}

int main() {
    string str;
    cout << "Enter the string to be encoded: ";
    getline(cin, str);

    unordered_map<char, int> freq;
    for (char c : str) {
        freq[c]++;
    }

    Node* root = buildHuffmanTree(freq);

    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    cout << "Huffman Codes:\n";
    for (auto& pair : huffmanCode) {
        cout << pair.first << " : " << pair.second << endl;
    }

    string encodedString = encode(str, huffmanCode);
    cout << "Encoded string: " << encodedString << endl;

    string decodedString = decode(encodedString, root);
    cout << "Decoded string: " << decodedString << endl;

    return 0;
}

// Time complexity: O(n log n) where n is the number of unique characters in the input string
