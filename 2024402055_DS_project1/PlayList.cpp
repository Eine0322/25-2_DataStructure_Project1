// Implementation of the PlayList class.
#include "PlayList.h"
#include <iostream>
#include <iomanip>

// Destructor.
PlayList::~PlayList() {
	clear();
}

// Deletes all nodes and resets the list state.
void PlayList::clear() {
	if (empty()) return;
	
	PlayListNode* current = head->getNext();
	while (current != head) {
		PlayListNode* temp = current;
		current = current->getNext();
		delete temp;
	}
	delete head;
	head = cursor = nullptr;
	count = 0;
	time = 0;
}

// Checks if the playlist is empty.
bool PlayList::empty() const {
	return head == nullptr;
}

// Checks if the playlist is full (max 10 songs).
bool PlayList::full() const {
	return count >= 10;
}

// Checks if a song exists in the playlist.
bool PlayList::exist(const string& artist, const string& title) const {
	if (empty()) return false;
	
	PlayListNode* current = head;
	do {
		if (current->getArtist() == artist && current->getTitle() == title) {
			return true;
		}
		current = current->getNext();
	} while (current != head);
	return false;
}

// Inserts multiple songs and prints the final state once.
void PlayList::insert_nodes(const vector<MusicQueueNode*>& songs, ostream& os) {
	bool inserted = false;
	for (MusicQueueNode* data : songs) {
		if (exist(data->getArtist(), data->getTitle())) {
			continue;
		}

		PlayListNode* newNode = new PlayListNode(data->getArtist(), data->getTitle(), data->getRunTime(), data->getRtSeconds());
		
		if (empty()) {
			head = newNode;
			head->setNext(head);
			head->setPrev(head);
			cursor = head;
		} else {
			PlayListNode* rear = head->getPrev();
			rear->setNext(newNode);
			newNode->setPrev(rear);
			newNode->setNext(head);
			head->setPrev(newNode);
		}
		
		count++;
		time += newNode->getRuntimeSec();
		inserted = true;
	}

	if (inserted) {
		// Print the final state after all additions.
		os << "========MAKEPL========" << endl;
		PlayListNode* current = head;
		for(int i = 0; i < count; ++i) {
			os << current->toString() << endl;
			current = current->getNext();
		}
		
		int total_min = time / 60;
		int total_sec = time % 60;
		os << "Count " << count << "/10" << endl;
		os << "Time " << total_min << "min " << setfill('0') << setw(2) << total_sec << "sec" << endl;
		os << "======================" << endl;
	}
}


// Deletes a single song from the playlist.
bool PlayList::delete_node(const string& artist, const string& title) {
	if (empty()) return false;
	
	PlayListNode* target = nullptr;
	PlayListNode* current = head;
	do {
		if (current->getArtist() == artist && current->getTitle() == title) {
			target = current;
			break;
		}
		current = current->getNext();
	} while (current != head);

	if (target == nullptr) return false;

	time -= target->getRuntimeSec();
	count--;

	if (count == 0) {
		delete target;
		head = cursor = nullptr;
	} else {
		target->getPrev()->setNext(target->getNext());
		target->getNext()->setPrev(target->getPrev());
		if (target == head) {
			head = target->getNext();
		}
		if (target == cursor) {
			cursor = target->getNext();
		}
		delete target;
	}
	
	return true;
}

// Prints the contents of the playlist.
void PlayList::print(ostream& os) {
	if (empty()) {
		os << "========ERROR========" << endl;
		os << "600" << endl;
		os << "=====================" << endl;
		return;
	}
	
	os << "========PRINT========" << endl;
	PlayListNode* current = head;
	for(int i = 0; i < count; ++i) {
		os << current->toString() << endl;
		current = current->getNext();
	}
	
	int total_min = time / 60;
	int total_sec = time % 60;
	os << "Count : " << count << " / 10" << endl;
	os << "Time : " << total_min << "min " << setfill('0') << setw(2) << total_sec << "sec" << endl;
	os << "=====================" << endl;
}