// Implementation of the TitleBST and TitleBSTNode classes.
#include "TitleBST.h"

// --- TitleBSTNode implementations ---

// Adds an artist's version of a song to this node.
void TitleBSTNode::addArtist(const string& a, const string& r, int r_sec) {
    artists.push_back(a);
    run_times.push_back(r);
    rt_seconds.push_back(r_sec);
    count++;
}

// Removes an artist's version of a song from this node.
bool TitleBSTNode::removeSong(const string& a) {
	for (size_t i = 0; i < artists.size(); ++i) {
		if (artists[i] == a) {
			artists.erase(artists.begin() + i);
			run_times.erase(run_times.begin() + i);
			rt_seconds.erase(rt_seconds.begin() + i);
			count--;
			return true;
		}
	}
	return false;
}


// --- TitleBST implementations ---

// Constructor.
TitleBST::TitleBST() : root(nullptr) {}

// Destructor.
TitleBST::~TitleBST() {
	deleteTree(root);
}

// Recursively deletes all nodes in the tree.
void TitleBST::deleteTree(TitleBSTNode* node) {
	if (node) {
		deleteTree(node->getLeft());
		deleteTree(node->getRight());
		delete node;
	}
}

// Recursive helper to insert a new node.
TitleBSTNode* TitleBST::insertRecursive(TitleBSTNode* node, MusicQueueNode* data) {
	if (node == nullptr) {
		return new TitleBSTNode(data->getTitle(), data->getArtist(), data->getRunTime(), data->getRtSeconds());
	}
	
	if (data->getTitle() < node->getTitle()) {
		node->setLeft(insertRecursive(node->getLeft(), data));
	} else if (data->getTitle() > node->getTitle()) {
		node->setRight(insertRecursive(node->getRight(), data));
	} else {
		node->addArtist(data->getArtist(), data->getRunTime(), data->getRtSeconds());
	}
	return node;
}

// Public method to insert a song.
bool TitleBST::insert(MusicQueueNode* data) {
	if (!data) return false;
	root = insertRecursive(root, data);
	return true;
}

// Recursive helper to print the tree in-order.
void TitleBST::printRecursive(TitleBSTNode* node, ostream& os) const {
	if (node) {
		printRecursive(node->getLeft(), os);
		for (size_t i = 0; i < node->artists.size(); ++i) {
			os << node->artists[i] << "/" << node->getTitle() << "/" << node->run_times[i] << endl;
		}
		printRecursive(node->getRight(), os);
	}
}

// Public method to print the entire BST.
void TitleBST::print(ostream& os) const {
	if (root == nullptr) {
		os << "========ERROR========" << endl;
		os << "600" << endl;
		os << "=====================" << endl;
		return;
	}
	os << "========PRINT========" << endl;
	os << "TitleBST" << endl;
	printRecursive(root, os);
	os << "=====================" << endl;
}

// Recursive helper to search for a node by song title.
TitleBSTNode* TitleBST::searchRecursive(TitleBSTNode* node, const string& title_key) const {
	if (node == nullptr || node->getTitle() == title_key) {
		return node;
	}
	if (title_key < node->getTitle()) {
		return searchRecursive(node->getLeft(), title_key);
	} else {
		return searchRecursive(node->getRight(), title_key);
	}
}

// Public method to search for a title.
void TitleBST::search(const string& key, ostream& os) const {
	TitleBSTNode* node = searchRecursive(root, key);
	if (node) {
		os << "========SEARCH========" << endl;
		for (size_t i = 0; i < node->artists.size(); ++i) {
			os << node->artists[i] << "/" << node->getTitle() << "/" << node->run_times[i] << endl;
		}
		os << "======================" << endl;
	} else {
		os << "========ERROR========" << endl;
		os << "400" << endl;
		os << "=====================" << endl;
	}
}

// Checks for the existence of a title or a specific song.
bool TitleBST::exist(const string& title_key, const string& artist_key) const {
	TitleBSTNode* node = searchRecursive(root, title_key);
	if (!node) return false;
	if (artist_key.empty()) return true;
	
	for (const auto& artist : node->artists) {
		if (artist == artist_key) return true;
	}
	return false;
}

// Finds the node with the minimum key in a subtree.
TitleBSTNode* TitleBST::findMin(TitleBSTNode* node) {
	TitleBSTNode* current = node;
	while (current && current->getLeft() != nullptr) {
		current = current->getLeft();
	}
	return current;
}

// Recursive helper to delete a node.
TitleBSTNode* TitleBST::deleteNodeRecursive(TitleBSTNode* node, const string& title_key, const string& artist_key) {
	if (node == nullptr) return nullptr;

	if (title_key < node->getTitle()) {
		node->setLeft(deleteNodeRecursive(node->getLeft(), title_key, artist_key));
	} else if (title_key > node->getTitle()) {
		node->setRight(deleteNodeRecursive(node->getRight(), title_key, artist_key));
	} else {
		bool delete_full_node = artist_key.empty();
		
		if (!delete_full_node) {
			node->removeSong(artist_key);
			if (node->getCount() > 0) return node;
		}
		
		if (node->getLeft() == nullptr) {
			TitleBSTNode* temp = node->getRight();
			delete node;
			return temp;
		} else if (node->getRight() == nullptr) {
			TitleBSTNode* temp = node->getLeft();
			delete node;
			return temp;
		}
		
		TitleBSTNode* temp = findMin(node->getRight());
		node->title = temp->title;
		node->artists = temp->artists;
		node->run_times = temp->run_times;
		node->rt_seconds = temp->rt_seconds;
		node->count = temp->count;
		node->setRight(deleteNodeRecursive(node->getRight(), temp->getTitle(), ""));
	}
	return node;
}

// Public method to delete a title or a specific song.
bool TitleBST::delete_node(const string& title_key, const string& artist_key) {
	if (!exist(title_key, artist_key)) return false;
	root = deleteNodeRecursive(root, title_key, artist_key);
	return true;
}

// Retrieves all songs with a given title.
vector<MusicQueueNode*> TitleBST::getSongs(const string& key) const {
	vector<MusicQueueNode*> songs;
	TitleBSTNode* node = searchRecursive(root, key);
	if (node) {
		for (size_t i = 0; i < node->artists.size(); ++i) {
			string data = node->artists[i] + "|" + node->title + "|" + node->run_times[i];
			songs.push_back(new MusicQueueNode(data));
		}
	}
	return songs;
}