#pragma once
#include "ArtistBSTNode.h"
#include "MusicQueueNode.h" 
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class ArtistBST {
private:
	ArtistBSTNode* root;
	
	// Recursive helpers
	ArtistBSTNode* insertRecursive(ArtistBSTNode* node, MusicQueueNode* data);
	void printRecursive(ArtistBSTNode* node, ostream& os) const;
	ArtistBSTNode* searchRecursive(ArtistBSTNode* node, const string& artist_key) const;
	
	// Deletion helpers
	void deleteTree(ArtistBSTNode* node);
	ArtistBSTNode* findMin(ArtistBSTNode* node);
	ArtistBSTNode* deleteNodeRecursive(ArtistBSTNode* node, const string& artist_key, const string& title_key);

public:
	ArtistBST();
	~ArtistBST();

	bool insert(MusicQueueNode* data); 
	void search(const string& key, ostream& os) const; 
	void searchSong(const string& artist, const string& title, ostream& os) const; 
	void print(ostream& os) const; 
	bool delete_node(const string& artist_key, const string& title_key = ""); 
	bool exist(const string& artist_key, const string& title_key = "") const;

	vector<MusicQueueNode*> getSongs(const string& key) const;
	MusicQueueNode* getSong(const string& artist, const string& title) const;
};