//  p5.cpp

#include <iostream>
#include "HuffmanTree.h"

using namespace std;


int main(int argc, const char * argv[])
{
  HuffmanTree hc;
  string fileName;
  string outName;
  

  cout << "Please enter a filename: ";
  cin >> fileName;
  cout << endl;

  hc.createCodeTree(fileName);

  cout << "Please enter the output filename: ";
  cin >> outName;
  cout << endl;

  hc.encodeFile(fileName, outName);

  cout << "Decoding File: " << endl;

  hc.decodeFile(outName);

  cout << hc;
 
	// create code tree
	//
	// encode file
	//
	// decode file
	//
		
	return 0;
}

























