// Main entry point for the music playlist management program.
#include "Manager.h"
#include <iostream>

using namespace std;

// Main function to start the program.
int main(int argc, char* argv[]) {
	// Check for the correct number of command-line arguments.
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <command_file_name>" << endl;
		return 1;
	}

	// Create a Manager instance and run the program.
	Manager m;
	m.run(argv[1]);

	return 0;
}