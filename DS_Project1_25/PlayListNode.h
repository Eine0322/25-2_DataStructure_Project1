// Definition of the PlayListNode class.
#pragma once
#include <string>

using namespace std;

class PlayList;

// Represents a single node in the PlayList circular linked list.
class PlayListNode {
private:
	string artist;          // The artist's name.
	string title;           // The song's title.
	int runtime_sec;        // Runtime in seconds.
	string run_time_str;    // Runtime as "M:SS" string.
	PlayListNode* prev;     // Pointer to the previous node.
	PlayListNode* next;     // Pointer to the next node.

public:
	// Constructor.
	PlayListNode(const string& a, const string& t, const string& r_str, int r_sec) 
		: artist(a), title(t), runtime_sec(r_sec), run_time_str(r_str), prev(nullptr), next(nullptr) {}
	
	// Destructor.
	~PlayListNode(){}
	
	// Getter methods.
	string getArtist() const { return artist; }
	string getTitle() const { return title; }
	int getRuntimeSec() const { return runtime_sec; }
	string getRunTimeStr() const { return run_time_str; }
	PlayListNode* getPrev() const { return prev; }
	PlayListNode* getNext() const { return next; }

	// Setter methods.
	void setPrev(PlayListNode* p) { prev = p; }
	void setNext(PlayListNode* n) { next = n; }

	// Returns a formatted string representation of the song.
	string toString() const { return artist + "/" + title + "/" + run_time_str; }

	// Grant access to PlayList class.
	friend class PlayList;
};