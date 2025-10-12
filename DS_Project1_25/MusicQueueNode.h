#pragma once
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Helper to convert M:SS to seconds
int stringToSeconds(const string& timeStr);

// Helper to split string by delimiter
void split(const string& s, char delimiter, vector<string>& tokens);

class MusicQueueNode {
private:
	string artist;
	string title;
	string run_time; // M:SS string
	int rt_seconds; // Total seconds

	MusicQueueNode* next;

public:
	// Constructor to parse data and initialize node
	MusicQueueNode(const string& data);
	~MusicQueueNode() {}

	// Getters
	string getArtist() const { return artist; }
	string getTitle() const { return title; }
	string getRunTime() const { return run_time; }
	int getRtSeconds() const { return rt_seconds; }
	MusicQueueNode* getNext() const { return next; }

	// Setter
	void setNext(MusicQueueNode* node) { next = node; }

	// Utility
	string toString() const { return artist + "/" + title + "/" + run_time; }

	friend class MusicQueue;
};