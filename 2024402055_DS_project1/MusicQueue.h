// Definition of the MusicQueue class.
#pragma once
#include "MusicQueueNode.h"
#include <iostream>

// A simple linked-list based queue for songs.
class MusicQueue {
private:
	MusicQueueNode* head; // Pointer to the front of the queue.
	MusicQueueNode* rear; // Pointer to the back of the queue.
	int size;             // Current number of elements.

public:
	// Constructor.
	MusicQueue();
	// Destructor.
	~MusicQueue();

	// Checks if the queue is empty.
	bool empty() const;
	// Checks if a specific song exists.
	bool exist(const string& artist, const string& title) const;
	// Adds a new song to the back of the queue.
	void push(const string& data, ostream& os, bool is_load = false);
	// Removes and returns the song from the front.
	MusicQueueNode* pop();
	// Prints all songs in the queue.
	void printAll(ostream& os) const;
	// Removes all elements.
	void clear();
};