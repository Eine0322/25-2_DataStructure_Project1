#pragma once
#include "MusicQueueNode.h"
#include <iostream>

class MusicQueue {
private:
	MusicQueueNode* head;
	MusicQueueNode* rear;
	int size;
public:
	MusicQueue();
	~MusicQueue();

	bool empty() const;
	bool exist(const string& artist, const string& title) const;
	void push(const string& data, ostream& os, bool is_load = false);
	MusicQueueNode* pop();
	
	void printAll(ostream& os) const;
	void clear();
};