#include <iostream>

#include "maze.h"

using namespace std;

void test(const string &mazeFile) {
  Maze myMaze;
  cout << "*** Solving " << mazeFile << endl;
  if (!myMaze.load(mazeFile)) {
    cerr << "Failed to load " << mazeFile << endl;
    return;
  }
  if (myMaze.solve()) {
    cout << "Path: " << myMaze.getPath() << endl;
  } else {
    cout << "Failed to solve: " << mazeFile << endl;
  }
  cout << myMaze << endl;
}

// accepts multiple maze files from command line
// ./a.out maze0.txt maze1.txt maze2.txt maze3.txt badfile.txt
int main(int argc, char *argv[]) {
  if (argc >= 1) {
    for (int i = 1; i < argc; ++i) {
      string mazeFile = argv[i];
      test(mazeFile);
    }
  }
  cout << "Done!" << endl;
  return 0;
}