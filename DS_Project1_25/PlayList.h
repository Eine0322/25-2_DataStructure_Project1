#pragma once
#include "PlayListNode.h"
#include "MusicQueueNode.h"
#include <string>

using namespace std;

class PlayList {
private:
	PlayListNode* head;
	PlayListNode* cursor;
	int count;
	int time; // Total run time in seconds

public:
	PlayList() : head(nullptr), cursor(nullptr), count(0), time(0) {}
	~PlayList();

	int getCount() const { return count; }

	void clear();
	void insert_node(MusicQueueNode* data, ostream& os);
	bool delete_node(const string& artist, const string& title);
	bool empty() const;
	bool full() const;
	bool exist(const string& artist, const string& title) const;
	void print(ostream& os);
	int run_time() const { return time; }
};