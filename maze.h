//
// Created by Yusuf Pisan on 4/18/18.
//

#ifndef ASS3_MAZE_H
#define ASS3_MAZE_H

#include <ostream>
#include <string>
#include <vector>

using namespace std;

enum CELL { CLEAR = ' ', WALL = 'X', PATH = '*', VISITED = '+' };

class Maze {
  friend ostream &operator<<(ostream &out, const Maze &maze);

public:
  // default constructor
  Maze();

  // Load maze file from current directory
  bool load(const string &fileName);

  // true if maze can be solved
  bool solve();

  // path to exit
  string getPath() const;

private:
  enum DIRECTION { NORTH = 'N', SOUTH = 'S', EAST = 'E', WEST = 'W' };
  bool solve(int row, int col);

  void populatePath(
      int row, int col,
      vector<string> &visited); // created this helper method, use recursion

  // path to exit
  string path;

  // array to hold the maze structure
  vector<string> field;

  // visited

  // width and height of maze
  int width{0}, height{0};

  // location of exit row and column
  int exitRow{0}, exitColumn{0};

  // location of start row and column
  int startRow{0}, startColumn{0};

  // true if row, column is inside the maze
  bool isInside(int row, int col) const;

  // true if row, column is clear to move
  bool isClear(int row, int col) const;

  // mark location as part of the path to exit
  void markAsPath(int row, int col);

  // mark location as visited, not part of the path to exit
  void markAsVisited(int row, int col);

  // true if row, column is the exit
  bool atExit(int row, int column) const;
};

#endif // ASS3_MAZE_H
