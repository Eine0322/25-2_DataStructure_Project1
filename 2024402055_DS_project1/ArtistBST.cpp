#include "ArtistBST.h"

// --- ArtistBSTNode implementations ---

void ArtistBSTNode::addSong(const string& t, const string& r, int r_sec) {
    titles.push_back(t);
    run_times.push_back(r);
    rt_seconds.push_back(r_sec);
    count++;
}

bool ArtistBSTNode::removeSong(const string& t) {
	for (size_t i = 0; i < titles.size(); ++i) {
		if (titles[i] == t) {
			titles.erase(titles.begin() + i);
			run_times.erase(run_times.begin() + i);
			rt_seconds.erase(rt_seconds.begin() + i);
			count--;
			return true;
		}
	}
	return false;
}

// --- ArtistBST implementations ---

ArtistBST::ArtistBST() : root(nullptr) {}

ArtistBST::~ArtistBST() {
	deleteTree(root);
}

void ArtistBST::deleteTree(ArtistBSTNode* node) {
	if (node) {
		deleteTree(node->getLeft());
		deleteTree(node->getRight());
		delete node;
	}
}

ArtistBSTNode* ArtistBST::insertRecursive(ArtistBSTNode* node, MusicQueueNode* data) {
	if (node == nullptr) {
		return new ArtistBSTNode(data->getArtist(), data->getTitle(), data->getRunTime(), data->getRtSeconds());
	}
	
	if (data->getArtist() < node->getArtist()) {
		node->setLeft(insertRecursive(node->getLeft(), data));
	} else if (data->getArtist() > node->getArtist()) {
		node->setRight(insertRecursive(node->getRight(), data));
	} else {
		node->addSong(data->getTitle(), data->getRunTime(), data->getRtSeconds());
	}
	return node;
}

bool ArtistBST::insert(MusicQueueNode* data) {
	if (!data) return false;
	root = insertRecursive(root, data);
	return true;
}

void ArtistBST::printRecursive(ArtistBSTNode* node, ostream& os) const {
	if (node) {
		printRecursive(node->getLeft(), os);
		for (size_t i = 0; i < node->titles.size(); ++i) {
			os << node->getArtist() << "/" << node->titles[i] << "/" << node->run_times[i] << endl;
		}
		printRecursive(node->getRight(), os);
	}
}

void ArtistBST::print(ostream& os) const {
	os << "========PRINT========" << endl;
	os << "ArtistBST" << endl;
	printRecursive(root, os);
	os << "=====================" << endl;
}

ArtistBSTNode* ArtistBST::searchRecursive(ArtistBSTNode* node, const string& artist_key) const {
	if (node == nullptr || node->getArtist() == artist_key) {
		return node;
	}
	if (artist_key < node->getArtist()) {
		return searchRecursive(node->getLeft(), artist_key);
	} else {
		return searchRecursive(node->getRight(), artist_key);
	}
}

void ArtistBST::search(const string& key, ostream& os) const {
	os << "========SEARCH========" << endl;
	ArtistBSTNode* node = searchRecursive(root, key);
	if (node) {
		for (size_t i = 0; i < node->titles.size(); ++i) {
			os << node->getArtist() << "/" << node->titles[i] << "/" << node->run_times[i] << endl;
		}
	} else {
		os << "Error: Artist not found" << endl; // Should not happen if exist check is done
	}
	os << "======================" << endl;
}

void ArtistBST::searchSong(const string& artist, const string& title, ostream& os) const {
	os << "========SEARCH========" << endl;
	ArtistBSTNode* node = searchRecursive(root, artist);
	bool found = false;
	if (node) {
		for (size_t i = 0; i < node->titles.size(); ++i) {
			if (node->titles[i] == title) {
				os << node->getArtist() << "/" << node->titles[i] << "/" << node->run_times[i] << endl;
				found = true;
				break;
			}
		}
	}
	if (!found) {
		os << "Error: Song not found" << endl;
	}
	os << "======================" << endl;
}

bool ArtistBST::exist(const string& artist_key, const string& title_key) const {
	ArtistBSTNode* node = searchRecursive(root, artist_key);
	if (!node) return false;
	
	if (title_key.empty()) return true; // Artist exists
	
	// Check if the specific song exists
	for (const auto& title : node->titles) {
		if (title == title_key) return true;
	}
	return false;
}

ArtistBSTNode* ArtistBST::findMin(ArtistBSTNode* node) {
	ArtistBSTNode* current = node;
	while (current && current->getLeft() != nullptr) {
		current = current->getLeft();
	}
	return current;
}

ArtistBSTNode* ArtistBST::deleteNodeRecursive(ArtistBSTNode* node, const string& artist_key, const string& title_key) {
	if (node == nullptr) return nullptr;

	if (artist_key < node->getArtist()) {
		node->setLeft(deleteNodeRecursive(node->getLeft(), artist_key, title_key));
	} else if (artist_key > node->getArtist()) {
		node->setRight(deleteNodeRecursive(node->getRight(), artist_key, title_key));
	} else {
		// Found the Artist node
		bool delete_full_node = title_key.empty(); // Delete all songs (DELETE ARTIST)
		
		if (!delete_full_node) {
			node->removeSong(title_key);
			if (node->getCount() > 0) return node; // Song removed, but node remains
			// Last song removed, so fall through to delete the node
		} 
		
		// Delete the full node
		if (node->getLeft() == nullptr) {
			ArtistBSTNode* temp = node->getRight();
			delete node;
			return temp;
		} else if (node->getRight() == nullptr) {
			ArtistBSTNode* temp = node->getLeft();
			delete node;
			return temp;
		} else {
			// Two children case: Find successor
			ArtistBSTNode* temp = findMin(node->getRight());
			node->artist = temp->artist;
			node->titles = temp->titles;
			node->run_times = temp->run_times;
			node->rt_seconds = temp->rt_seconds;
			node->count = temp->count;

			// Delete the successor
			node->setRight(deleteNodeRecursive(node->getRight(), temp->getArtist(), ""));
		}
	}
	return node;
}


bool ArtistBST::delete_node(const string& artist_key, const string& title_key) {
	if (!exist(artist_key, title_key)) return false; // Should be checked by Manager
	
	// If it's a song deletion, we check if the song exists and delete it in the recursive function.
	// If it's an artist deletion, the recursive function handles the node removal.
	root = deleteNodeRecursive(root, artist_key, title_key);
	return true;
}

vector<MusicQueueNode*> ArtistBST::getSongs(const string& key) const {
	vector<MusicQueueNode*> songs;
	ArtistBSTNode* node = searchRecursive(root, key);
	if (node) {
		for (size_t i = 0; i < node->titles.size(); ++i) {
			string data = node->artist + "|" + node->titles[i] + "|" + node->run_times[i];
			songs.push_back(new MusicQueueNode(data));
		}
	}
	return songs;
}

MusicQueueNode* ArtistBST::getSong(const string& artist, const string& title) const {
	ArtistBSTNode* node = searchRecursive(root, artist);
	if (node) {
		for (size_t i = 0; i < node->titles.size(); ++i) {
			if (node->titles[i] == title) {
				string data = node->artist + "|" + node->titles[i] + "|" + node->run_times[i];
				return new MusicQueueNode(data);
			}
		}
	}
	return nullptr;
}