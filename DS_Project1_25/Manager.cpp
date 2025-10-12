#include "Manager.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

Manager::Manager() {
	flog.open("log.txt", ios::out);
	if (flog.is_open()) {
		opened_log = true;
	}
}

Manager::~Manager() {
	if (opened_log) {
		flog.close();
	}
}

string Manager::formatTime(int totalSeconds) {
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    stringstream ss;
    ss << minutes << "min " << setfill('0') << setw(2) << seconds << "sec";
    return ss.str();
}

void Manager::logError(int code) {
	flog << "========ERROR========" << endl;
	flog << code << endl;
	flog << "=====================" << endl;
}

void Manager::run(const char* command_file) {
	fcmd.open(command_file, ios::in);
	if (!fcmd.is_open()) {
		cerr << "Error: Could not open command file: " << command_file << endl;
		return;
	}

	string line;
	while (getline(fcmd, line)) {
		if (line.empty()) continue;
		
		vector<string> tokens;
		split(line, ' ', tokens);

		if (tokens.empty()) continue;

		string cmd = tokens[0];

		if (cmd == "LOAD") {
			LOAD();
		} else if (cmd == "ADD" && tokens.size() == 2) {
			ADD(tokens[1]);
		} else if (cmd == "QPOP") {
			QPOP();
		} else if (cmd == "SEARCH" && tokens.size() >= 3) {
			handleSearch(tokens);
		} else if (cmd == "MAKEPL" && tokens.size() >= 3) {
			handleMakePL(tokens);
		} else if (cmd == "PRINT" && tokens.size() == 2) {
			handlePrint(tokens);
		} else if (cmd == "DELETE" && tokens.size() >= 3) {
			handleDelete(tokens);
		} else if (cmd == "EXIT") {
			EXIT();
			break;
		}
	}
	fcmd.close();
}

void Manager::LOAD() {
	ifstream fmusic("Music_List.txt", ios::in);
	flog << "========LOAD========" << endl;
	if (fmusic.is_open()) {
		string line;
		while (getline(fmusic, line)) {
			q.push(line, flog, true); // true for is_load to change print format
		}
		fmusic.close();
	} else {
		flog << "Error: Music_List.txt not found." << endl;
	}
	flog << "====================" << endl;
}

void Manager::ADD(const string& data) {
	q.push(data, flog, false);
}

void Manager::QPOP() {
	flog << "========QPOP========" << endl;
	int count = 0;
	while (!q.empty()) {
		MusicQueueNode* data = q.pop();
		if (data) {
			ab.insert(data);
			tb.insert(data);
			delete data;
			count++;
		}
	}
	if (count > 0) {
		flog << "Success" << endl;
	} else {
		flog << "Queue is empty." << endl;
	}
	flog << "====================" << endl;
}

void Manager::handleSearch(const vector<string>& tokens) {
	string type = tokens[1];
	string key1 = tokens[2];
	
	if (type == "ARTIST") {
		ab.search(key1, flog);
	} else if (type == "TITLE") {
		tb.search(key1, flog);
	} else if (type == "SONG" && tokens.size() == 3) {
		vector<string> song_tokens;
		split(key1, '|', song_tokens);
		if (song_tokens.size() == 2) {
			ab.searchSong(song_tokens[0], song_tokens[1], flog);
		}
	}
}

void Manager::handleMakePL(const vector<string>& tokens) {
	string type = tokens[1];
	string key1 = tokens[2];
	
	if (pl.full()) {
		logError(500);
		return;
	}

	vector<MusicQueueNode*> songs_to_add;

	if (type == "ARTIST") {
		songs_to_add = ab.getSongs(key1);
	} else if (type == "TITLE") {
		songs_to_add = tb.getSongs(key1);
	} else if (type == "SONG" && tokens.size() == 3) {
		vector<string> song_tokens;
		split(key1, '|', song_tokens);
		if (song_tokens.size() == 2) {
			MusicQueueNode* song = ab.getSong(song_tokens[0], song_tokens[1]);
			if (song) songs_to_add.push_back(song);
		}
	}
	
	if (songs_to_add.empty()) return; // No songs found

	for (MusicQueueNode* song : songs_to_add) {
		if (pl.getCount() < 10) {
			pl.insert_node(song, flog); // insert_node handles internal exist check
		} else {
			// Log 500 error and break the loop if the list becomes full during insertion
			if (!pl.full()) {
				logError(500);
			}
			break; 
		}
	}

	// Clean up temp MusicQueueNodes created by BST getSongs
	for (MusicQueueNode* song : songs_to_add) {
		delete song;
	}
}

void Manager::handlePrint(const vector<string>& tokens) {
	string type = tokens[1];
	if (type == "ARTIST") {
		ab.print(flog);
	} else if (type == "TITLE") {
		tb.print(flog);
	} else if (type == "LIST") {
		pl.print(flog);
	}
}

void Manager::handleDelete(const vector<string>& tokens) {
	string type = tokens[1];
	string key1 = tokens[2];
	string key2 = (tokens.size() > 3) ? tokens[3] : "";
	bool success = false;
	
	if (type == "ARTIST") {
		if (ab.exist(key1)) {
			// Get all songs by artist from BST for TitleBST/PlayList deletion
			vector<MusicQueueNode*> songs = ab.getSongs(key1); 
			
			// 1. Delete from ArtistBST
			ab.delete_node(key1);
			
			// 2. Delete from TitleBST and PlayList for each song
			for (MusicQueueNode* song : songs) {
				tb.delete_node(song->getTitle(), song->getArtist());
				pl.delete_node(song->getArtist(), song->getTitle());
				delete song;
			}
			success = true;
		}
	} else if (type == "TITLE") {
		if (tb.exist(key1)) {
			// Get all songs with title from BST for ArtistBST/PlayList deletion
			vector<MusicQueueNode*> songs = tb.getSongs(key1); 
			
			// 1. Delete from TitleBST
			tb.delete_node(key1);
			
			// 2. Delete from ArtistBST and PlayList for each song
			for (MusicQueueNode* song : songs) {
				ab.delete_node(song->getArtist(), song->getTitle());
				pl.delete_node(song->getArtist(), song->getTitle());
				delete song;
			}
			success = true;
		}
	} else if (type == "SONG" && tokens.size() == 3) {
		vector<string> song_tokens;
		split(key1, '|', song_tokens);
		if (song_tokens.size() == 2) {
			string artist = song_tokens[0];
			string title = song_tokens[1];
			
			if (ab.exist(artist, title)) {
				// 1. Delete from ArtistBST
				ab.delete_node(artist, title);
				// 2. Delete from TitleBST
				tb.delete_node(title, artist);
				// 3. Delete from PlayList
				pl.delete_node(artist, title);
				success = true;
			}
		}
	} else if (type == "LIST" && tokens.size() == 3) {
		vector<string> song_tokens;
		split(key1, '|', song_tokens);
		if (song_tokens.size() == 2) {
			string artist = song_tokens[0];
			string title = song_tokens[1];
			
			if (pl.exist(artist, title)) {
				// Only delete from PlayList
				pl.delete_node(artist, title);
				success = true;
			}
		}
	}

	if (success) {
		flog << "========DELETE========" << endl;
		flog << "Success" << endl;
		flog << "======================" << endl;
	} else {
		logError(700); // Data not found
	}
}

void Manager::EXIT() {
	flog << "=======EXIT========" << endl;
	// Destructors will handle memory cleanup
	flog << "Success" << endl;
	flog << "===================" << endl;
}