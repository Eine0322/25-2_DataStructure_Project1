// Definition of the Manager class, which orchestrates the program's operations.
#pragma once
#include "MusicQueue.h"
#include "TitleBST.h"
#include "ArtistBST.h"
#include "PlayList.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

// Manages all data structures and command processing.
class Manager {
private:
	MusicQueue q;        // Queue for loaded music data.
	ArtistBST ab;       // BST sorted by artist name.
	TitleBST tb;        // BST sorted by song title.
	PlayList pl;        // Circular linked list for the playlist.
	ifstream fcmd;      // Input file stream for commands.
	ofstream flog;      // Output file stream for logs.
	bool opened_log = false; // Flag to check if the log file is open.

	// Helper function to format seconds into "Mmin SSsec".
	string formatTime(int totalSeconds);
	
	// Command handler functions.
	void handleSearch(const vector<string>& tokens);
	void handleMakePL(const vector<string>& tokens);
	void handlePrint(const vector<string>& tokens);
	void handleDelete(const vector<string>& tokens);

	// Logs an error code to the log file.
	void logError(int code);

public:
	// Constructor.
	Manager();
	// Destructor.
	~Manager();
	// Runs the program by processing commands from a file.
	void run(const char* command_file);

	// Command functions.
	void LOAD();
	void ADD(const string& data);
	void QPOP();
	void EXIT();
};