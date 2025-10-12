#pragma once
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class TitleBSTNode {
private:
	string title;
	vector<string> artists; // List of artists with this title
	vector<string> run_times;
	vector<int> rt_seconds;
	int count;
	TitleBSTNode* left;
	TitleBSTNode* right;

public:
	TitleBSTNode(const string& t, const string& a, const string& r, int r_sec) : 
		title(t), count(1), left(nullptr), right(nullptr) 
	{
		artists.push_back(a);
		run_times.push_back(r);
		rt_seconds.push_back(r_sec);
	}
	~TitleBSTNode() {}

	// Getters
	string getTitle() const { return title; }
	vector<string>& getArtists() { return artists; }
	vector<string>& getRunTimes() { return run_times; }
	vector<int>& getRtSeconds() { return rt_seconds; }
	int getCount() const { return count; }
	TitleBSTNode* getLeft() const { return left; }
	TitleBSTNode* getRight() const { return right; }

	// Setters
	void setLeft(TitleBSTNode* node) { left = node; }
	void setRight(TitleBSTNode* node) { right = node; }
	
	// Data manipulation
	void addArtist(const string& a, const string& r, int r_sec);
	bool removeSong(const string& a);

	// Friendship for BST
	friend class TitleBST;
};