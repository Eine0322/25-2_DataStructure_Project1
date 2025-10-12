#include "Manager.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	// Program needs the command file name as an argument
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <command_file_name>" << endl;
		return 1;
	}

	Manager m;
	m.run(argv[1]);

	return 0;
}