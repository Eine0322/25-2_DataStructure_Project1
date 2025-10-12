// Definition of the ArtistBST class, sorted by artist name.
#pragma once
#include "ArtistBSTNode.h"
#include "MusicQueueNode.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// A Binary Search Tree for music data, ordered by artist name.
class ArtistBST {
private:
	ArtistBSTNode* root; // The root node of the BST.

	// Recursive helper functions.
	ArtistBSTNode* insertRecursive(ArtistBSTNode* node, MusicQueueNode* data);
	void printRecursive(ArtistBSTNode* node, ostream& os) const;
	ArtistBSTNode* searchRecursive(ArtistBSTNode* node, const string& artist_key) const;
	
	// Deletion helper functions.
	void deleteTree(ArtistBSTNode* node);
	ArtistBSTNode* findMin(ArtistBSTNode* node);
	ArtistBSTNode* deleteNodeRecursive(ArtistBSTNode* node, const string& artist_key, const string& title_key);

public:
	// Constructor.
	ArtistBST();
	// Destructor.
	~ArtistBST();

	// Inserts a new song into the BST.
	bool insert(MusicQueueNode* data);
	// Searches for an artist and prints all their songs.
	void search(const string& key, ostream& os) const;
	// Searches for a specific song by a specific artist.
	void searchSong(const string& artist, const string& title, ostream& os) const;
	// Prints the entire BST in-order.
	void print(ostream& os) const;
	// Deletes an artist or a specific song.
	bool delete_node(const string& artist_key, const string& title_key = "");
	// Checks if an artist or a specific song exists.
	bool exist(const string& artist_key, const string& title_key = "") const;
	// Retrieves all songs by a given artist.
	vector<MusicQueueNode*> getSongs(const string& key) const;
	// Retrieves a specific song by a given artist and title.
	MusicQueueNode* getSong(const string& artist, const string& title) const;
};