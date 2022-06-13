#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;
#endif /* __PROGTEST__ */


ifstream input;
static int positionInByte = -1;
static uint8_t byte = '\0';
static unsigned char letterFind = '\0';
bool ok;

struct utfLetter
{
  uint8_t firstByte;
  uint8_t secondByte;
  uint8_t thirdByte;
  uint8_t fourthByte;
};

struct TreeNode
{
  struct TreeNode* left;
  struct TreeNode* right;
  unsigned char letter;
  bool isList;
};

uint8_t readByte()
{
  uint8_t resByte = '\0';
  if (!input.read((char*)&resByte, sizeof ( resByte ) ))
    ok = false;
  return resByte;
}


bool readBit()
{
  if (positionInByte < 0)
  {
    byte = readByte();
    positionInByte = 7;
  }

  bool out = (byte >> positionInByte) & 1;

  positionInByte--;
  return out;
}


void writeTree(struct TreeNode* node, int indent)
{
  for (int i = 0; i < 2*indent; i++)
    cout << ' ';
  if (node->left)
  {
    cout << '0' << endl;
    writeTree(node->left, indent + 1);
    for (int i = 0; i < 2*indent; i++)
      cout << ' ';
    cout << '1' << endl;
    writeTree(node->right, indent + 1);
  }
  else
    cout << node->letter;
}


void writeTree2(struct TreeNode* node, int index, char* tmp)
{
  if (node->left)
  {
    tmp[index] = '0';
    writeTree2(node->left, index + 1, tmp);
    tmp[index] = '1';
    writeTree2(node->right, index + 1, tmp);
  }
  else
  {
    tmp[index] = 0;
    cout << node->letter << ' ' << tmp << endl;
  }
}


unsigned char ToByte(bool b[8])
{
  unsigned char result = '\0';
  result = b[0]<<7 | b[1]<<6 | b[2]<<5 | b[3]<<4 | b[4] <<3 | b[5]<<2 | b[6]<<1 | b[7];
  return result;
}



int toChunkLength(bool b[12])
{
  int result = '\0';
  result = b[0]<<11 | b[1]<<10 | b[2]<<9 | b[3]<<8 | b[4] <<7 | b[5]<<6 | b[6]<<5 | b[7]<<4 | b[8]<<3 | b[9]<<2 | b[10]<<1 | b[11];
  return result;
}



unsigned char readLetter()
{
  bool* b = new bool[8];

  for(int i = 0; i < 8; i++)
  {
    b[i] = readBit();
  }

  unsigned char letter = ToByte(b);
  delete [] b;
  return letter;
}




struct TreeNode* readTree()
{
  struct TreeNode* res = new TreeNode();
  res->left = nullptr;
  res->right = nullptr;
  if ((readBit() == false) && ok)
  {
    res->left = readTree();
    (*res).right = readTree();
    res->isList = false;
  }
  else
  {
    res->letter = readLetter();
    res->isList = true;
  }
  return res;
}


void deleteTree(struct TreeNode* node)
{
  if (node == NULL) return;

  deleteTree(node->left);
  deleteTree(node->right);

  free(node);
}


void walkTree(struct TreeNode* node)
{
  if(node->isList == false)
  {
    bool move = readBit();
    if (move == false)
    {
      if(node->isList == false)
      {
        //cout << move << endl;
        if(node->left != nullptr)
          walkTree(node->left);
        else
          letterFind = node->letter;
      }
      else
      {
        //cout << move << endl;
        letterFind = node->letter;
      }
    }
    else
    {
      if(node->isList == false)
      {
        //cout << move << endl;
        if(node->right != nullptr)
          walkTree(node->right);
        else
          letterFind = node->letter;
      }
      else
      {
        //cout << move << endl;
        letterFind = node->letter;
      }
    }
  }
  else
  {
    letterFind = node->letter;
  }
}

int varChunk()
{
  int length = '\0';
  bool* b = new bool[12];
  for(int i = 0; i < 12; i++)
    b[i] = readBit();
  length = toChunkLength(b);

  delete [] b;
  return length;
}


bool isLastChunk(int& chunkLength)
{
  if(readBit())
  {
    chunkLength = 4096;
    return false;
  }
  else
  {
    chunkLength = varChunk();
    return true;
  }
}

bool decompressFile ( const char * inFileName, const char * outFileName )
{
  input.open(inFileName, ios::in | ios::binary);
  ofstream output;
  output.open(outFileName, std::ofstream::out);
  if (!input.is_open())
    ok = false;
  positionInByte = -1;
  ok = true;
  struct TreeNode * root = nullptr;

  root = readTree();

  int chunkLength;
  bool last;

  do {
    last = isLastChunk(chunkLength);
    if (!ok) break;
    letterFind = '\0';

    for(int i = 0; i < chunkLength; i++)
    {
      if (!ok) break;
      walkTree(root);
      if(output)
        output << letterFind;
      else
        ok = false;
      if(output.bad())
        ok = false;
      cout << "ok: " << ok << endl;
      cout << "current letter: " << letterFind << endl;
    }
  } while (!last);

  if (ok)
  {
    cout << "Navic obsahuje:" << (char)readByte() << endl;
    ok = !ok;
  }

  deleteTree(root);
  root = NULL;
  input.close();
  output.close();
  return ok;
}


bool compressFile ( const char * inFileName, const char * outFileName )
{
  // keep this dummy implementation (no bonus) or implement the compression (bonus)
  return false;
}


#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1, const char * fileName2 )
{
  ifstream file1;
  ifstream file2;
  file1.open(fileName1, ios::in | ios::binary);
  file2.open(fileName2, ios::in | ios::binary);
  bool identical = true;
  while (true)
  {
    int res1 = file1.get();
    int res2 = file2.get();
    if (res1 != res2)
    {
      identical = false;
      break;
    }
    if (res1 < 0)
      break;
  }
  file1.close();
  file2.close();
  // todo
  return identical;
}

int main ( void )
{
  assert ( decompressFile ( "tests/test0.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test0.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/test1.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test1.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/test2.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test2.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/test3.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test3.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/test4.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test4.orig", "tempfile" ) );

  assert ( ! decompressFile ( "tests/test5.huf", "tempfile" ) );


  assert ( decompressFile ( "tests/extra0.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra0.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra1.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra1.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra2.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra2.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra3.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra3.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra4.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra4.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra5.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra5.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra6.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra6.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra7.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra7.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra8.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra8.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra9.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra9.orig", "tempfile" ) );

  return 0;
}
#endif /* __PROGTEST__ */
