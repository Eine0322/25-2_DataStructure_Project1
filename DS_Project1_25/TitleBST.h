// Definition of the TitleBST class, sorted by song title.
#pragma once
#include "TitleBSTNode.h"
#include "MusicQueueNode.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// A Binary Search Tree for music data, ordered by song title.
class TitleBST {
private:
	TitleBSTNode* root; // The root node of the BST.

	// Recursive helper functions.
	TitleBSTNode* insertRecursive(TitleBSTNode* node, MusicQueueNode* data);
	void printRecursive(TitleBSTNode* node, ostream& os) const;
	TitleBSTNode* searchRecursive(TitleBSTNode* node, const string& title_key) const;
	
	// Deletion helper functions.
	void deleteTree(TitleBSTNode* node);
	TitleBSTNode* findMin(TitleBSTNode* node);
	TitleBSTNode* deleteNodeRecursive(TitleBSTNode* node, const string& title_key, const string& artist_key);

public:
	// Constructor.
	TitleBST();
	// Destructor.
	~TitleBST();

	// Inserts a new song into the BST.
	bool insert(MusicQueueNode* data);
	// Searches for a title and prints all songs with that title.
	void search(const string& key, ostream& os) const;
	// Prints the entire BST in-order.
	void print(ostream& os) const;
	// Deletes a title or a specific artist's version.
	bool delete_node(const string& title_key, const string& artist_key = "");
	// Checks if a title or a specific song exists.
	bool exist(const string& title_key, const string& artist_key = "") const;
	// Retrieves all songs with a given title.
	vector<MusicQueueNode*> getSongs(const string& key) const;
};