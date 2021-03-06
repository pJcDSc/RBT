/*
 * Author: Peter Jin
 * Date: 2/24/20
 * RBT demo main clas
 */

#include <iostream>
#include <cstring>
#include <fstream>
#include "Node.h"
#include "RBT.h"

using namespace std;

bool parse(char*, RBT*); //Parse input and call commands
void printHelp();        //Prints the help
void addNode(RBT*);      //Add a node to the rbt
void display(RBT*);      //Display the rbt
void addFile(RBT*);      //Add from file
int strToInt(char*);     //Convert char* to int

int main() {
  RBT* rbt = new RBT();  //Red black tree that does the stuff
  bool running = true;   //While var
  char* in = new char(); //in char

  cout << "Welcome to Red-Black Tree demo" << endl;
  cout << "Commands are ADD, READ, PRINT, and QUIT. HELP for more info." << endl;

  while (running) {
    cin.get(in, 37);          //read input
    cin.clear(); 
    cin.ignore(999, '\n');

    running = parse(in, rbt); //parse input
  }

  delete rbt;

  cout << "Bye!" << endl;
}

//parse input call functions
bool parse(char* in, RBT* rbt) {
  for (int i = 0 ; i < strlen(in); i++) {
    in[i] = toupper(in[i]);
  }

  if (strcmp(in, "HELP") == 0) {
    printHelp();
  }
  else if (strcmp(in, "ADD") == 0) {
    addNode(rbt);
  }
  else if (strcmp(in, "PRINT") == 0) {
    display(rbt);
  }
  else if (strcmp(in, "READ") == 0) {
    addFile(rbt);
  }
  else if (strcmp(in, "QUIT") == 0) {
    return false;
  }
  else {
    cout << "Command not recognized" << endl;
  }
  return true;
}

//Print help stuff
void printHelp() {
  cout << "RBT command help" << endl;
  cout << "ADD: add a node to the red black tree" << endl;
  cout << "READ: add numbers to red black tree from file" << endl;
  cout << "PRINT: display red black tree" << endl;
  cout << "QUIT: exit the program" << endl;
}

//Call addnode in RBT class
void addNode(RBT* rbt) {
  cout << "What number to add?" << endl;
  int n;
  cin >> n;
  cin.clear();
  cin.ignore(999, '\n');
  rbt -> addNode(n);
  cout << "Added " << n << " to tree" << endl;
}

//Read from file, split by space, call addnode on each
void addFile(RBT* rbt) {
  char* line = new char(); //input line from file

  cout << "Input file name" << endl;
  char* fileName = new char();
  cin.getline(fileName, 80);
  cin.clear();
  cout << "Reading from \"" << fileName << "\"" << endl;
  ifstream fileStream(fileName);
  if (fileStream.is_open()) {
    fileStream.getline(line,999);
  } else {
    cout << "Could not read from file" << endl;
    return;
  }

  cout << "Added numbers to tree" << endl;
  fileStream.close();

  char* build = new char[strlen(line)+1]();
  int ind = 0;
  for (int i = 0; i < strlen(line); i++) {
    if (line[i] == ' ') {
      if (strlen(build) > 0) rbt -> addNode(strToInt(build));
      build = new char[strlen(line)+1]();
      ind = 0;
    } else {
      if (isdigit(line[i])) build[ind++] = line[i];
    }
  }
  return;
}

int strToInt(char* str) {
  int num = 0;
  for (int i = 0; i < strlen(str); i++) {
    if (!isdigit(str[i])) continue;
    num *= 10;
    num += str[i]-'0';
  }
  return num;
}

void display (RBT* rbt) {
  rbt -> displayTree();
}
