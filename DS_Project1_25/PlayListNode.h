#pragma once
#include <string>

using namespace std;

class PlayListNode {
private:
	string artist;
	string title;
	int runtime_sec; 
	string run_time_str; 

	PlayListNode* prev;
	PlayListNode* next;

public:
	PlayListNode(const string& a, const string& t, const string& r_str, int r_sec) 
		: artist(a), title(t), runtime_sec(r_sec), run_time_str(r_str), prev(nullptr), next(nullptr) {}
	~PlayListNode(){}
	
	// Getters
	string getArtist() const { return artist; }
	string getTitle() const { return title; }
	int getRuntimeSec() const { return runtime_sec; }
	string getRunTimeStr() const { return run_time_str; }
	PlayListNode* getPrev() const { return prev; }
	PlayListNode* getNext() const { return next; }

	// Setters
	void setPrev(PlayListNode* p) { prev = p; }
	void setNext(PlayListNode* n) { next = n; }

	string toString() const { return artist + "/" + title + "/" + run_time_str; }

	friend class PlayList;
};