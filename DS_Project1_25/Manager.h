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

// Utility functions (implemented in MusicQueueNode.cpp)
// int stringToSeconds(const string& timeStr); 
// void split(const string& s, char delimiter, vector<string>& tokens);

class Manager {
private:
	MusicQueue q;
	ArtistBST ab;
	TitleBST tb;
	PlayList pl;
	ifstream fcmd;
	ofstream flog;
	bool opened_log = false; // Flag for destructor

	// Utility to format seconds to Mmin SSsec
	string formatTime(int totalSeconds);
	
	// Command handlers
	void handleSearch(const vector<string>& tokens);
	void handleMakePL(const vector<string>& tokens);
	void handlePrint(const vector<string>& tokens);
	void handleDelete(const vector<string>& tokens);

	// Error logging
	void logError(int code);

public:
	Manager();
	~Manager();

	void run(const char* command);

	void LOAD();
	void ADD(const string& data);
	void QPOP();
	void SEARCH(const string& type, const string& key); // Generalized
	void MAKEPL(const string& type, const string& key1, const string& key2 = ""); // Generalized
	void PRINT(const string& type); // Generalized
	void DELETE(const string& type, const string& key1, const string& key2 = ""); // Generalized
	void EXIT();

};