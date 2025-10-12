#include "PlayList.h"
#include <iostream>
#include <iomanip>

PlayList::~PlayList() {
	clear();
}

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

bool PlayList::empty() const {
	return head == nullptr;
}

bool PlayList::full() const {
	return count >= 10;
}

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

void PlayList::insert_node(MusicQueueNode* data, ostream& os) {
	if (full()) {
		os << "========ERROR========" << endl;
		os << "500" << endl;
		os << "=====================" << endl;
		return;
	}
	
	if (exist(data->getArtist(), data->getTitle())) {
		return; // Already exists, skip insertion
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

	// Print all current songs in the list
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

void PlayList::print(ostream& os) {
	os << "========PRINT========" << endl;
	if (empty()) {
		os << "Count : 0 / 10" << endl;
		os << "Time : 0min 00sec" << endl;
		os << "=====================" << endl;
		return;
	}

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