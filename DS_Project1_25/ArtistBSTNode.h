#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

class ArtistBSTNode {
private:
	string artist;
	vector<string> titles; // List of titles by this artist
	vector<string> run_times; // M:SS string run times
	vector<int> rt_seconds; // Total seconds run times
	int count;
	ArtistBSTNode* left;
	ArtistBSTNode* right;

public:
	ArtistBSTNode(const string& a, const string& t, const string& r, int r_sec) : 
		artist(a), count(1), left(nullptr), right(nullptr) 
	{
		titles.push_back(t);
		run_times.push_back(r);
		rt_seconds.push_back(r_sec);
	}
	~ArtistBSTNode() {}

	// Getters
	string getArtist() const { return artist; }
	vector<string>& getTitles() { return titles; }
	vector<string>& getRunTimes() { return run_times; }
	vector<int>& getRtSeconds() { return rt_seconds; }
	int getCount() const { return count; }
	ArtistBSTNode* getLeft() const { return left; }
	ArtistBSTNode* getRight() const { return right; }
	
	// Setters
	void setLeft(ArtistBSTNode* node) { left = node; }
	void setRight(ArtistBSTNode* node) { right = node; }
	
	// Data manipulation
	void addSong(const string& t, const string& r, int r_sec);
	bool removeSong(const string& t);
	
	// Friendship for BST
	friend class ArtistBST;
};