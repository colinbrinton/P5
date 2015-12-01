//  HuffmanTree.cpp

#include "HuffmanTree.h"
//#include <algorithm>

const int ONE = 1;
const int ZERO = 0;

//bool myComp(CharFreq a, CharFreq b) { return( a.ascii < b.ascii);}

bool HuffmanTree::createCodeTree(string filename)
{
	std::priority_queue<BST<CharFreq>::BSTNode*,std::vector<BST<CharFreq>::BSTNode*>,BST<CharFreq>::FrequencyCompare > myPriorityQ;
	
	string str;
	string allText = "";
	ifstream infile;
	infile.open(filename.c_str());
	if( !infile.is_open() )
	{
		cout << "ERROR Loading file!\n";
		return false;
	}
	while(!infile.eof()) // To get you all the lines.
	{
		getline(infile,str); // Saves the line in STRING.
		allText += str + "\n";
	}
	infile.close();

	//	cout << allText;


	//	unsigned char testChar; //remove
	std::vector<CharFreq> chars;
	//CharFreq newChar;
  	unsigned n = ZERO;
	bool found = false;
	unsigned total = ZERO;
	
	//	if(chars.empty())
	// {
	CharFreq newChar;
	while(chars.empty())
	  {
		if((int)allText[n] >=0 && (int)allText[n] <=127)
		  {
			newChar.letter = allText[n];
			newChar.frequency = ONE;
			chars.push_back(newChar);
		  }
		//	chars.push_back(newChar);
		//stSize = ONE;
	  	++n;
		// }
	  }

	//	testChar = chars[n].letter;
	//	cout << endl << endl << testChar << endl;
	//	testChar = chars[n+ONE].letter;
	//	cout << endl << endl << testChar << endl;

	if (!chars.empty())
	  {
		while( n != allText.size())
		  {
			CharFreq newChar;
			for(unsigned i = ZERO; i < chars.size(); ++i)
			  {
				if(chars[i].letter == allText[n])
				  {
					found = true;
					chars[i].frequency += ONE;
				  }
			  }
			if (found == false)
			  {
				if((int)allText[n] >=0 && (int)allText[n] <=127)
			      {
			    	newChar.letter = allText[n];
			    	newChar.frequency = ONE;
			    	chars.push_back(newChar);
			      }
			  }
			found = false;

			//	if(!((int)allText[n] >=0 && (int)allText[n] <=127))
			//	cout <<(int)allText[n] << endl;
			++n;
		  }
	  }

	//for(unsigned x = ZERO; x != chars.size(); ++x)
	//chars[0].encoding = ""; 

	//	sort(chars.begin(), chars.end(), myComp);

	for(unsigned a = ZERO; a != chars.size(); ++a)
	 {
		cout << endl << "Letter: " << chars[a].letter << endl;
		cout << "Freq: " << chars[a].frequency << endl;
		//	cout << (int) chars[x].letter << endl;

		//	cout << endl << "Letter: " << chars[1].letter << endl;
		//	cout << "Freq: " << chars[1].frequency << endl;

		//	cout << endl << "Letter: " << chars[2].letter << endl;
		//	cout << "Freq: " << chars[2].frequency << endl;

		//	cout << endl << "Letter: " << chars[3].letter << endl;
		//	cout << "Freq: " << chars[3].frequency << endl;
		
		total += chars[a].frequency;
	 }

	cout << endl << total << endl;

	cout << chars.size() << endl;
	//CharFreq test;
	//BST<CharFreq>::BSTNode* node = new BST<CharFreq>::BSTNode(test);
	
	for(unsigned y = ZERO; y != chars.size(); ++y)
	  {
		BST<CharFreq>::BSTNode* nodePtr = new BST<CharFreq>::BSTNode(chars[y]);
		//BST<CharFreq>::BSTNode* node;
		nodePtr->data.letter = chars[y].letter;
		nodePtr->data.frequency = chars[y].frequency;
		myPriorityQ.push(nodePtr);
	  }

	//cout << endl << endl << myPriorityQ.size() << endl;

	//BST<CharFreq>::BSTNode* test;

	while(myPriorityQ.size() != ONE)
	  {
	CharFreq topTwoChar;
	BST<CharFreq>::BSTNode* topTwoPtr = new BST<CharFreq>::BSTNode(topTwoChar);

	topTwoPtr->left = myPriorityQ.top();
	myPriorityQ.pop();
	topTwoPtr->right = myPriorityQ.top();
	myPriorityQ.pop();
	topTwoPtr->data.frequency = topTwoPtr->left->data.frequency +
	  topTwoPtr->right->data.frequency;
	myPriorityQ.push(topTwoPtr);
	  }

	cout << endl << endl << myPriorityQ.size() << endl;
	cout << endl << endl << myPriorityQ.top()->data.frequency << endl;

	//cout << topTwoPtr->left->data.letter << endl;
	//cout << topTwoPtr->left->data.frequency << endl;

	//cout << endl;
	
	//cout << topTwoPtr->right->data.letter << endl;
	//cout << topTwoPtr->right->data.frequency << endl;

	
	this->root = myPriorityQ.top();
	
	cout << this->root->data.frequency << endl;

	if(!(setEncoding(this->root, "")))
	  {
		cout << "Generation of encoding bits failed." << endl;
		return false;
	  }
	
	//cout << this->root->left->left->left->data.encoding << endl;
   
	
   
	// **************************************************************
	// TODO: Fill in here
	// 1. Count occurences of every letter or sybmol that you care about in allText (consider spaces ' ', newlines '\n', periods, commas, question marks, quotation marks, etc.
	// 2. Use myPriorityQ to build a tree, as described in the assignment
	// 3. Set root (inherted from BST) to the final item in myPriorityQ
	
	
	// **************************************************************


	//cout << "Test Encoding:" << endl;
	//cout <<	getEncoding('q', this->root, "") << endl;
	
	return true;
}

bool HuffmanTree::encodeFile(string originalFilename, string outputFilename)
{
	string str;
	string allText = "";
	ifstream infile;
	infile.open(originalFilename.c_str());
	if( !infile.is_open() )
	{
		cout << "ERROR Loading file!\n";
		return false;
	}
	while(!infile.eof()) // To get you all the lines.
	{
		getline(infile,str); // Saves the line in STRING.
		allText += str + "\n";
	}
	infile.close();
	
	std::ofstream outStream(outputFilename.c_str(), std::ios::binary);
	
	if( !outStream.is_open() )
	{
		cout << "ERROR creating output file!\n";
		return false;
	}
	
	string currentStream="";
	//string test = "";
	
	const int WRITE_SIZE = 8;
	
	for(int i=0;i<(int)allText.length();i++)
	{
		// **************************************************************
		// TODO: add the appropriate encoding for allText[i] to currentStream
	  
	  
	  currentStream += getEncoding(allText[i], this->root, "");
		
	  // **************************************************************

	  //cout << currentStream << endl;


	  //test += currentStream;
		while((int)currentStream.length() > WRITE_SIZE)
		{
			string byte = currentStream.substr(0, WRITE_SIZE);
			bitset<8> set(byte);
			const char toWrite = (unsigned char)((unsigned int)set.to_ulong());
			outStream.write(&toWrite,sizeof(char));
			currentStream = currentStream.substr(WRITE_SIZE, currentStream.length()-WRITE_SIZE);
		}
	}

	//cout << test << "end" << endl;
	
	outStream.close();
	return false;
}

bool HuffmanTree::decodeFile(string filename)
{
	ifstream encodedfile;
	encodedfile.open(filename.c_str(), ios::binary);
	if( !encodedfile.is_open() )
	{
		cout << "ERROR opening encoded file!\n";
		return false;
	}
	
	encodedfile >> std::noskipws;	
	
	string bitStream = "";
	while(!encodedfile.eof())
	{
		unsigned char readMe;
		encodedfile >> readMe;
		bitset<8> set((unsigned long)readMe);
		bitStream += set.to_string();
	}
	
	encodedfile.close();
	
	int i=0;
	while(i != -1)
	{
		i = traverseAndPrint(bitStream, i);
	}
	return false;
}


int HuffmanTree::traverseAndPrint(string &bits, int i, BSTNode *cur)
{
  if(i >= (int)bits.length())
		return -1;
	// **************************************************************
	// TODO: Write this function using recursion.
	//  This is essentially your decode function.  You need to step through the tree based on reading 0 or 1 and when you 
        //      reach a leaf, print (using cout) the appropriate character.
	// i represents your current location in the string
	// cur represents the cur node in your tree
	// Don't forget that you need to keep going after printing out a character (which means restarting at the top of the tree)
	
	return -1;
	// **************************************************************
}

void HuffmanTree::displayCode(ostream &out)
{
	// **************************************************************
	// TODO: print out each letter and its code, you might want to check for special cases (space, newline, etc.)
	
	// **************************************************************
}

ostream& operator<<(ostream &out, HuffmanTree &code)
{
	code.displayCode(out);
	return out;
}



bool HuffmanTree::setEncoding(BST<CharFreq>::BSTNode *nodePtr, string encode)
{
  if(nodePtr == nullptr)
	return false;
  else
	{
	  if(nodePtr->left == nullptr && nodePtr->right == nullptr)
		nodePtr->data.encoding = encode;
	  if(nodePtr->left)
		setEncoding(nodePtr->left, (encode += "0"));
      if(nodePtr->right)
		setEncoding(nodePtr->right, (encode += "1"));
	  return true;
	}
  return false;
}

string HuffmanTree::getEncoding(unsigned char input, BSTNode* nodePtr, string output)
{
  if(nodePtr)
	{
	  if(nodePtr->data.letter == input)
		if((nodePtr->left == nullptr) && (nodePtr->right == nullptr))
		output = nodePtr->data.encoding;
	  
	  if(nodePtr->left)
		output = getEncoding(input, nodePtr->left, output);

	  if(nodePtr->right)
		output = getEncoding(input, nodePtr->right, output);
	}

  else
	{
	  cout << "Error accessing Huffman Tree." << endl;
	}
  
  return output;
}
  
