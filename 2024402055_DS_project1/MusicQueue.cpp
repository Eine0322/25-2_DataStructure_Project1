// Implementation of the MusicQueue class.
#include "MusicQueue.h"
#include "MusicQueueNode.h"

// Constructor.
MusicQueue::MusicQueue() : head(nullptr), rear(nullptr), size(0) {}

// Destructor.
MusicQueue::~MusicQueue() {
	clear();
}

// Removes all nodes from the queue.
void MusicQueue::clear() {
	while (!empty()) {
		MusicQueueNode* temp = pop();
		delete temp;
	}
}

// Checks if the queue is empty.
bool MusicQueue::empty() const {
	return size == 0;
}

// Checks if a song exists in the queue.
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

// Adds a new element to the end of the queue.
void MusicQueue::push(const string& data, ostream& os, bool is_load) {
	MusicQueueNode* newNode = new MusicQueueNode(data);
	
	// Check for duplicates on ADD command.
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

	// Print to log based on command type.
	if (is_load) {
		os << newNode->toString() << endl;
	} else {
		os << "========ADD========" << endl;
		os << newNode->toString() << endl;
		os << "===================" << endl;
	}
}

// Removes the element from the front of the queue.
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

// Prints all elements in the queue.
void MusicQueue::printAll(ostream& os) const {
	MusicQueueNode* current = head;
	while (current != nullptr) {
		os << current->toString() << endl;
		current = current->getNext();
	}
}