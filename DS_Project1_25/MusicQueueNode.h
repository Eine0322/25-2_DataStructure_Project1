// Definition of the MusicQueueNode class and utility functions.
#pragma once
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Utility function declarations.
int stringToSeconds(const string& timeStr);
void split(const string& s, char delimiter, vector<string>& tokens);

class MusicQueue;

// Represents a single node in the MusicQueue.
class MusicQueueNode {
private:
	string artist;       // The artist's name.
	string title;        // The song's title.
	string run_time;     // Runtime as "M:SS" string.
	int rt_seconds;      // Runtime in seconds.
	MusicQueueNode* next; // Pointer to the next node.

public:
	// Constructor: parses a data string.
	MusicQueueNode(const string& data);
	// Destructor.
	~MusicQueueNode() {}

	// Getter methods.
	string getArtist() const { return artist; }
	string getTitle() const { return title; }
	string getRunTime() const { return run_time; }
	int getRtSeconds() const { return rt_seconds; }
	MusicQueueNode* getNext() const { return next; }

	// Setter method.
	void setNext(MusicQueueNode* node) { next = node; }

	// Returns a formatted string of the song data.
	string toString() const { return artist + "/" + title + "/" + run_time; }

	// Grant access to MusicQueue class.
	friend class MusicQueue;
};