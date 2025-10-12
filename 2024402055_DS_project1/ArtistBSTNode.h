// Definition of the ArtistBSTNode class.
#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class ArtistBST;

// Represents a single node in the ArtistBST, corresponding to one artist.
class ArtistBSTNode {
private:
	string artist;          // The artist's name (the key).
	vector<string> titles;  // List of song titles.
	vector<string> run_times; // List of runtimes ("M:SS").
	vector<int> rt_seconds; // List of runtimes in seconds.
	int count;              // Number of songs by this artist.
	ArtistBSTNode* left;    // Pointer to the left child.
	ArtistBSTNode* right;   // Pointer to the right child.

public:
	// Constructor for a new artist node.
	ArtistBSTNode(const string& a, const string& t, const string& r, int r_sec) : 
		artist(a), count(1), left(nullptr), right(nullptr) 
	{
		titles.push_back(t);
		run_times.push_back(r);
		rt_seconds.push_back(r_sec);
	}

	// Destructor.
	~ArtistBSTNode() {}

	// Getter methods.
	string getArtist() const { return artist; }
	int getCount() const { return count; }
	ArtistBSTNode* getLeft() const { return left; }
	ArtistBSTNode* getRight() const { return right; }
	
	// Setter methods.
	void setLeft(ArtistBSTNode* node) { left = node; }
	void setRight(ArtistBSTNode* node) { right = node; }
	
	// Data manipulation methods.
	void addSong(const string& t, const string& r, int r_sec);
	bool removeSong(const string& t);
	
	// Grant access to ArtistBST class.
	friend class ArtistBST;
};