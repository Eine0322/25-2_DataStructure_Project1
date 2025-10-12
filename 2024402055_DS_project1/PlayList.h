// Definition of the PlayList class, a circular doubly linked list.
#pragma once
#include "PlayListNode.h"
#include "MusicQueueNode.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Manages a circular doubly linked list of songs.
class PlayList {
private:
	PlayListNode* head;   // Pointer to the head of the list.
	PlayListNode* cursor; // Cursor for playback controls.
	int count;            // Number of songs in the playlist.
	int time;             // Total runtime in seconds.

public:
	// Constructor.
	PlayList() : head(nullptr), cursor(nullptr), count(0), time(0) {}
	// Destructor.
	~PlayList();

	// Getter methods.
	int getCount() const { return count; }
	int run_time() const { return time; }

	// Removes all nodes from the playlist.
	void clear();
	// Inserts multiple nodes and prints the result once.
	void insert_nodes(const vector<MusicQueueNode*>& songs, ostream& os);
	// Deletes a specific song from the playlist.
	bool delete_node(const string& artist, const string& title);
	// Checks if the playlist is empty.
	bool empty() const;
	// Checks if the playlist is full.
	bool full() const;
	// Checks if a specific song exists.
	bool exist(const string& artist, const string& title) const;
	// Prints all songs in the playlist.
	void print(ostream& os);
};