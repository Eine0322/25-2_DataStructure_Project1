// Implementation of the Manager class.
#include "Manager.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

// Constructor: opens the log file in append mode.
Manager::Manager() {
	flog.open("log.txt", ios::app);
	if (flog.is_open()) {
		opened_log = true;
	}
}

// Destructor: closes the log file.
Manager::~Manager() {
	if (opened_log) {
		flog.close();
	}
}

// Formats total seconds into a "Mmin SSsec" string.
string Manager::formatTime(int totalSeconds) {
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    stringstream ss;
    ss << minutes << "min " << setfill('0') << setw(2) << seconds << "sec";
    return ss.str();
}

// Writes a formatted error message to the log.
void Manager::logError(int code) {
	flog << "========ERROR========" << endl;
	flog << code << endl;
	flog << "=====================" << endl;
}

// Main loop to read and execute commands from the command file.
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

		// Command dispatcher.
		if (cmd == "LOAD") {
			LOAD();
		} else if (cmd == "ADD" && tokens.size() == 2) {
			ADD(tokens[1]);
		} else if (cmd == "QPOP") {
			QPOP();
		} else if (cmd == "SEARCH" && tokens.size() >= 2) {
			handleSearch(tokens);
		} else if (cmd == "MAKEPL" && tokens.size() >= 3) {
			handleMakePL(tokens);
		} else if (cmd == "PRINT" && tokens.size() == 2) {
			handlePrint(tokens);
		} else if (cmd == "DELETE" && tokens.size() >= 2) {
			handleDelete(tokens);
		} else if (cmd == "EXIT") {
			EXIT();
			break;
		}
	}
	fcmd.close();
}

// Handles the LOAD command: reads songs from Music_List.txt into the queue.
void Manager::LOAD() {
	ifstream fmusic("Music_List.txt", ios::in);
	flog << "========LOAD========" << endl;
	if (fmusic.is_open()) {
		string line;
		while (getline(fmusic, line)) {
			q.push(line, flog, true); // true for special LOAD formatting.
		}
		fmusic.close();
	} else {
		logError(100);
	}
	flog << "====================" << endl;
}

// Handles the ADD command: adds a single song to the queue.
void Manager::ADD(const string& data) {
	q.push(data, flog, false);
}

// Handles the QPOP command: moves all songs from the queue to the BSTs.
void Manager::QPOP() {
	flog << "========QPOP========" << endl;
	int count = 0;
	if (q.empty()) {
		logError(300);
	} else {
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
		}
	}
	flog << "====================" << endl;
}

// Handles the SEARCH command by dispatching to the correct data structure.
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

// Handles the MAKEPL command: adds songs from BSTs to the PlayList.
void Manager::handleMakePL(const vector<string>& tokens) {
	string type = tokens[1];
	string key1 = tokens[2];
	
	vector<MusicQueueNode*> songs_to_add;

	// Retrieve songs from the appropriate BST.
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
	
	if (songs_to_add.empty()) return;

	// Check for space before adding.
	if (pl.getCount() + songs_to_add.size() > 10) {
		logError(500);
	} else {
		pl.insert_nodes(songs_to_add, flog);
	}

	// Clean up temporary nodes.
	for (MusicQueueNode* song : songs_to_add) {
		delete song;
	}
}

// Handles the PRINT command for a specified data structure.
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

// Handles the DELETE command, removing data from specified structures.
void Manager::handleDelete(const vector<string>& tokens) {
	string type = tokens[1];
	string key1 = tokens[2];
	bool success = false;

	if (type == "ARTIST") {
		if (ab.exist(key1)) {
			vector<MusicQueueNode*> songs = ab.getSongs(key1);
			ab.delete_node(key1); // Delete from ArtistBST.
			
			// Delete from TitleBST and PlayList.
			for (MusicQueueNode* song : songs) {
				tb.delete_node(song->getTitle(), song->getArtist());
				pl.delete_node(song->getArtist(), song->getTitle());
				delete song;
			}
			success = true;
		}
	} else if (type == "TITLE") {
		if (tb.exist(key1)) {
			vector<MusicQueueNode*> songs = tb.getSongs(key1);
			tb.delete_node(key1); // Delete from TitleBST.
			
			// Delete from ArtistBST and PlayList.
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
				ab.delete_node(artist, title); // Delete from ArtistBST.
				tb.delete_node(title, artist); // Delete from TitleBST.
				pl.delete_node(artist, title); // Delete from PlayList.
				success = true;
			}
		}
	} else if (type == "LIST" && tokens.size() == 3) {
		vector<string> song_tokens;
		split(key1, '|', song_tokens);
		if (song_tokens.size() == 2) {
			string artist = song_tokens[0];
			string title = song_tokens[1];
			if (pl.delete_node(artist, title)) { // Only delete from PlayList.
				success = true;
			}
		}
	}

	if (success) {
		flog << "========DELETE========" << endl;
		flog << "Success" << endl;
		flog << "======================" << endl;
	} else {
		logError(700);
	}
}

// Handles the EXIT command.
void Manager::EXIT() {
	flog << "=======EXIT========" << endl;
	flog << "Success" << endl;
	flog << "===================" << endl;
}