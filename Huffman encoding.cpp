#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};

Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();
  node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;
  return node;
}

struct comp{ //cmp object
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;  // visi prioritet ima vecu frekvenciju
	}
};

void encode(Node* root, string str, unordered_map<char, string> &huffmanCode) { //obilazak hafmanovog stabla, smjestanje koda u mapu
	if (root == nullptr)
		return;
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}
	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int &index, string str) {  //obilazak stabla, dekodovanje stringa
	if (root == nullptr) {
		return;
	}
 
	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] =='0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

void buildHuffmanTree(string text) {
	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	} 
  
	priority_queue<Node*, vector<Node*>, comp> pq; //prioritetni red za smjestanje koda

	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr)); // kreira cvor-list za svaki char i dodaje u prioritetni red
	}

	while (pq.size() != 1)
	{
		// brise dva cvojra najveceg prioriteta
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();

		// kreira cvor sa djecom prethodna dva, cija je frekvencija jednaka sumi frekv prethodna dva cvora
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}
  
	Node* root = pq.top();

  //obilazak i ispis
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Huffman Codes:\n" << '\n';
	for (auto pair: huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << "\nOriginal string:\n" << text << '\n';

	//ispis kodovanog stringa
	string str = "";
	for (char ch: text) {
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string:\n" << str << '\n';

	// obilazak hafmanovog stabla i dekodovanje kodovanog stringa
	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
}

int main()
{
	string text = "Huffman coding is a data compression algorithm.";

	buildHuffmanTree(text);

	return 0;
}
