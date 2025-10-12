#pragma once
#include "TitleBSTNode.h"
#include "MusicQueueNode.h" 
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class TitleBST {
private:
	TitleBSTNode* root;
	
	// Recursive helpers
	TitleBSTNode* insertRecursive(TitleBSTNode* node, MusicQueueNode* data);
	void printRecursive(TitleBSTNode* node, ostream& os) const;
	TitleBSTNode* searchRecursive(TitleBSTNode* node, const string& title_key) const;
	
	// Deletion helpers
	void deleteTree(TitleBSTNode* node);
	TitleBSTNode* findMin(TitleBSTNode* node);
	TitleBSTNode* deleteNodeRecursive(TitleBSTNode* node, const string& title_key, const string& artist_key);

public:
	TitleBST();
	~TitleBST();

	bool insert(MusicQueueNode* data);
	void search(const string& key, ostream& os) const;
	void searchSong(const string& artist, const string& title, ostream& os) const; 
	void print(ostream& os) const;
	bool delete_node(const string& title_key, const string& artist_key = "");
	bool exist(const string& title_key, const string& artist_key = "") const;

	vector<MusicQueueNode*> getSongs(const string& key) const;
	vector<MusicQueueNode*> getSongs(const string& title, const string& artist) const;
};