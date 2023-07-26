//
// Created by Yusuf Pisan on 4/18/18.
//

#include "maze.h"
#include <algorithm>
#include <cassert>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// print maze object
ostream &operator<<(ostream &out, const Maze &maze) {
  for (int row = 0; row < maze.height; ++row) {
    for (int col = 0; col < maze.width; ++col) {
      out << maze.field[row][col];
    }
    out << endl;
  }
  out << endl;
  return out;
}

// default constructor
Maze::Maze() = default;

// Load maze file from current directory
bool Maze::load(const string &fileName) {
  // file input stream that allows us to read any information contained in the
  // file
  ifstream inFile;

  inFile.open(fileName);
  if (!inFile.is_open()) {
    cerr << "Unable to open file: " << fileName << endl;
    // next line is just to satisfy clang-tidy
    // otherwise it complains saying function can be const
    width = height = 0;
    return false;
  }
  inFile >> width >> height;
  inFile >> exitRow >> exitColumn;
  inFile >> startRow >> startColumn;
  // ignore leftover charcaters up to newline
  inFile.ignore(INT_MAX, '\n');
  string line;

  // getline()is a standard library function that is used to read a string or a
  // line from an input stream.
  for (int row = 0; row < height; ++row) {
    getline(inFile, line); // read line by line
    field.push_back(line); // push the whole line into the vector
  }
  return true;
}

// // true if maze can be solved
bool Maze::solve() { return solve(startRow, startColumn); }

bool Maze::solve(int row, int col) {
  markAsPath(row, col);
  if (atExit(row, col)) {          // solved
    vector<string> visited(field); // clone the field, keep track of visited
    populatePath(startRow, startColumn, visited);
    return true;
  }
  // check neighbors
  bool ans = false;
  if (isInside(row - 1, col) && isClear(row - 1, col)) {
    ans = solve(row - 1, col);
    if (!ans) {
      // markAsVisited(row - 1, col);
    } else {
      return true; // sol found
    }
  }
  if (isInside(row + 1, col) && isClear(row + 1, col)) { // south
    ans = solve(row + 1, col);
    if (!ans) {
      // markAsVisited(row + 1, col);
    } else {
      return true;
    }
  }
  if (isInside(row, col + 1) && isClear(row, col + 1)) { // EAST
    ans = solve(row, col + 1);
    if (!ans) {
      // markAsVisited(row, col + 1);
    } else {
      return true;
    }
  }
  if (isInside(row, col - 1) && isClear(row, col - 1)) { // WEST
    ans = solve(row, col - 1);
    if (!ans) {
      // markAsVisited(row, col - 1);
    } else {
      return true;
    }
  }
  markAsVisited(row, col);
  return false;
  //
}

void Maze::populatePath(int row, int col, vector<string> &visited) {
  visited[row][col] = 'V';
  if (isInside(row - 1, col) && visited[row - 1][col] == PATH) {
    path += static_cast<char>(NORTH);
    populatePath(row - 1, col, visited);
  } else if (isInside(row + 1, col) && visited[row + 1][col] == PATH) { // south
    path += static_cast<char>(SOUTH);
    populatePath(row + 1, col, visited);
  } else if (isInside(row, col - 1) && visited[row][col - 1] == PATH) { // WEST
    path += static_cast<char>(WEST);
    populatePath(row, col - 1, visited);
  } else if (isInside(row, col + 1) && visited[row][col + 1] == PATH) { // EAST
    path += static_cast<char>(EAST);
    populatePath(row, col + 1, visited);
  }
}

// path to exit
string Maze::getPath() const { return path; }

// true if row, column is the exit
bool Maze::atExit(int row, int column) const {
  return row == exitRow && column == exitColumn;
}

// true if row, column is inside the maze
bool Maze::isInside(int row, int col) const {
  return row >= 0 && col >= 0 && row < field.size() && col < field[row].size();
}

// true if row, column is clear to move
bool Maze::isClear(int row, int col) const {
  assert(row >= 0 && col >= 0 && row < field.size() && col < field[row].size());
  return field[row][col] == CLEAR;
}

// mark location as part of the path to exit
void Maze::markAsPath(int row, int col) {
  assert(row >= 0 && col >= 0 && row < field.size() && col < field[row].size());
  field[row][col] = PATH;
}

// mark location as visited, not part of the path to exit
void Maze::markAsVisited(int row, int col) {
  assert(row >= 0 && col >= 0 && row < field.size() && col < field[row].size());
  field[row][col] = VISITED;
}
