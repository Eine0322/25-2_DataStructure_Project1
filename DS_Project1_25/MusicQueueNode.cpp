#include "MusicQueueNode.h"
#include <sstream>
#include <vector>
#include <stdexcept>

// Helper to convert M:SS to seconds
int stringToSeconds(const string& timeStr) {
	size_t colonPos = timeStr.find(':');
	if (colonPos == string::npos) return 0;
	
	try {
		int minutes = stoi(timeStr.substr(0, colonPos));
		int seconds = stoi(timeStr.substr(colonPos + 1));
		return minutes * 60 + seconds;
	} catch (const invalid_argument& e) {
		return 0;
	} catch (const out_of_range& e) {
		return 0;
	}
}

// Helper to split string
void split(const string& s, char delimiter, vector<string>& tokens) {
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
}

MusicQueueNode::MusicQueueNode(const string& data) : next(nullptr), rt_seconds(0) {
    vector<string> tokens;
    split(data, '|', tokens);

    if (tokens.size() == 3) {
        artist = tokens[0];
        title = tokens[1];
        run_time = tokens[2];
        rt_seconds = stringToSeconds(run_time);
    }
}