#include "huffman_tree.h"

map<char, string> huffman;
map<char, int> lettercount;


void huffman_tree::tree(Node *head, string null) const {
	string nullstring = "¢";
	if (head == NULL) {
		return;
	}
	if (head->letter != nullstring[0])
        huffman[head->letter] = null;
        tree(head->left, null + '0');
        tree(head->right, null + '1');

}

string huffman_tree::filenew(string file) const
{
	ifstream in(file);
	string string((istreambuf_iterator<char>(in)),
					   istreambuf_iterator<char>());
	return string;
}

/*
Preconditions: file_name is the name of (and possibly path to) a text file
Postconditions: Reads the contents of file_name and constructs a
				huffman tree based on the character frequencies of the file contents
*/
huffman_tree::huffman_tree(const string &file_name) {
	ifstream file;
	int count;
	file.open(file_name);
	string str = filenew(file_name);
	file.close();
	for (int i=0; i<str.length(); i++) {
		lettercount[str[i]]++;
	}
	if (lettercount.size() == 1){
		for (auto mapIterator = lettercount.begin(); mapIterator != lettercount.end(); mapIterator++) {
			Node* heapHead = new Node;
			heapHead->letter = mapIterator->first;
			count = mapIterator->second;
			heapHead->count = count;
			huffTree.push(heapHead);
		}
		tree(huffTree.top(), "0");

	}
	if (lettercount.size() > 1){
		for (auto mapIterator = lettercount.begin(); mapIterator != lettercount.end(); mapIterator++) {
			Node* heapHead = new Node;
			heapHead->letter = mapIterator->first;
            count = mapIterator->second;
            heapHead->count = count;
			huffTree.push(heapHead);
		}
		while (huffTree.size() > 1) {
		    string check = "¢";
			Node* heapHead = new Node;
			Node* zero = huffTree.top();
			huffTree.pop();
			Node* one = huffTree.top();
			huffTree.pop();
            count = zero->count + one->count;
            heapHead->count = count;
			heapHead->letter = check[0];
			heapHead->left = zero;
			heapHead->right = one;
			huffTree.push(heapHead);
		}
		tree(huffTree.top(), "");

	}}
huffman_tree::~huffman_tree(){
	huffman.clear();
	lettercount.clear();
	while (!huffTree.empty()){
	    huffTree.pop();
	}
}

/*
Preconditions: Character is a character with an ASCII value
				between 0 and 127 (inclusive).
Postconditions: Returns the Huffman code for character if character is in the tree
				and an empty string otherwise.
*/
string huffman_tree::get_character_code(char character) const {
	auto mapIterator = huffman.find(character);
	if ( mapIterator != huffman.end()) {
		return huffman[character];
	}
	else {
		return "";
	}
}

/*
Preconditions: file_name is the name of (and possibly path to) a text file
Postconditions: Returns the Huffman encoding for the contents of file_name
				if file name exists and an empty string otherwise.
				If the file contains letters not present in the huffman_tree,
				return an empty string
*/
string huffman_tree::encode(const string &file_name) const {
	ifstream file;
	file.open(file_name);
	string str = filenew(file_name);
	string encodedString = "";
	if (lettercount.size() <= 1){
		encodedString += huffman[str[0]];
		return encodedString;
	}
	for (int i=0; i < str.length(); i++) {
		if(lettercount.count(str[i]) > 0){
			encodedString += huffman[str[i]];
		}
		else{
			return "";
		}
	}
	file.close();
	return encodedString;
}


/*
Preconditions: string_to_decode is a string containing Huffman-encoded text
Postconditions: Returns the plaintext represented by the string if the string
				is a valid Huffman encoding and an empty string otherwise
*/
string huffman_tree::decode(const string &string_to_decode) const {
	string decodedString = "";
	Node* head = huffTree.top();
	if (lettercount.size() == 1){
		decodedString = huffTree.top()->letter;
		return decodedString;
	}
	for (int i = 0; i < string_to_decode.length(); i++) {
		if (string_to_decode[i] == '0') {
			head = head->left;
		}
		else if (string_to_decode[i] == '1') {
			head = head->right;
		}

		if (head->left == NULL && head->right == NULL) {
			decodedString += head->letter;
			head = huffTree.top();
		}
	}
	return decodedString;
}
//Sources
//I worked on this project with Keanu Budham and Americos Perez
//http://www.cplusplus.com/reference/map/map/find/
//https://github.com/JKomskis/COP3530-S19-Huffman-Algorithm
//https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
//https://www.geeksforgeeks.org/huffman-decoding/
//https://stackoverflow.com/questions/18398167/how-to-copy-a-txt-file-to-a-char-array-in-c