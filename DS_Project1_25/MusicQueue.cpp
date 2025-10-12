#include "MusicQueue.h"
#include "MusicQueueNode.h"

MusicQueue::MusicQueue() : head(nullptr), rear(nullptr), size(0) {}

MusicQueue::~MusicQueue() {
	clear();
}

void MusicQueue::clear() {
	while (!empty()) {
		MusicQueueNode* temp = pop();
		delete temp;
	}
}

bool MusicQueue::empty() const {
	return size == 0;
}

bool MusicQueue::exist(const string& artist, const string& title) const {
	MusicQueueNode* current = head;
	while (current != nullptr) {
		if (current->getArtist() == artist && current->getTitle() == title) {
			return true;
		}
		current = current->getNext();
	}
	return false;
}

void MusicQueue::push(const string& data, ostream& os, bool is_load) {
	MusicQueueNode* newNode = new MusicQueueNode(data);
	
	if (!is_load && exist(newNode->getArtist(), newNode->getTitle())) {
		delete newNode;
		os << "========ERROR========" << endl;
		os << "200" << endl;
		os << "=====================" << endl;
		return;
	}

	if (empty()) {
		head = rear = newNode;
	} else {
		rear->setNext(newNode);
		rear = newNode;
	}
	size++;
	
	if (is_load) {
		os << newNode->toString() << endl;
	} else {
		os << "========ADD========" << endl;
		os << newNode->toString() << endl;
		os << "===================" << endl;
	}
}

MusicQueueNode* MusicQueue::pop() {
	if (empty()) {
		return nullptr;
	}
	MusicQueueNode* temp = head;
	head = head->getNext();
	temp->setNext(nullptr);
	
	if (head == nullptr) {
		rear = nullptr;
	}
	size--;
	return temp;
}

void MusicQueue::printAll(ostream& os) const {
	MusicQueueNode* current = head;
	while (current != nullptr) {
		os << current->toString() << endl;
		current = current->getNext();
	}
}