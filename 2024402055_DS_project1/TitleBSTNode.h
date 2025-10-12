// Definition of the TitleBSTNode class.
#pragma once
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class TitleBST;

// Represents a single node in the TitleBST, corresponding to one song title.
class TitleBSTNode {
private:
	string title;           // The song's title (the key).
	vector<string> artists; // List of artists for this song.
	vector<string> run_times; // List of runtimes ("M:SS").
	vector<int> rt_seconds; // List of runtimes in seconds.
	int count;              // Number of artists with this song title.
	TitleBSTNode* left;     // Pointer to the left child.
	TitleBSTNode* right;    // Pointer to the right child.

public:
	// Constructor for a new title node.
	TitleBSTNode(const string& t, const string& a, const string& r, int r_sec) : 
		title(t), count(1), left(nullptr), right(nullptr) 
	{
		artists.push_back(a);
		run_times.push_back(r);
		rt_seconds.push_back(r_sec);
	}

	// Destructor.
	~TitleBSTNode() {}

	// Getter methods.
	string getTitle() const { return title; }
	int getCount() const { return count; }
	TitleBSTNode* getLeft() const { return left; }
	TitleBSTNode* getRight() const { return right; }

	// Setter methods.
	void setLeft(TitleBSTNode* node) { left = node; }
	void setRight(TitleBSTNode* node) { right = node; }
	
	// Data manipulation methods.
	void addArtist(const string& a, const string& r, int r_sec);
	bool removeSong(const string& a);

	// Grant access to TitleBST class.
	friend class TitleBST;
};