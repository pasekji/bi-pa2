#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cctype>
#include <climits>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;

const uint16_t ENDIAN_LITTLE = 0x4949;
const uint16_t ENDIAN_BIG    = 0x4d4d;

#endif /* __PROGTEST__ */

struct THeader
{
    uint8_t ENDIAN_0;
    uint8_t ENDIAN_1;
    uint8_t SIRKA_0;
    uint8_t SIRKA_1;
    uint8_t VYSKA_0;
    uint8_t VYSKA_1;
    uint8_t FORMAT_0;
    uint8_t FORMAT_1;
};

struct THeader_copy
{
  uint16_t ENDIAN;
  uint16_t SIRKA;
  uint16_t VYSKA;
  uint16_t FORMAT;
};

struct TChannel_8_bit
{
  uint8_t PIXEL;
};

struct TChannel3_8_bit
{
  uint8_t PIXEL_0;
  uint8_t PIXEL_1;
  uint8_t PIXEL_2;
};

struct TChannel4_8_bit
{
  uint8_t PIXEL_0;
  uint8_t PIXEL_1;
  uint8_t PIXEL_2;
  uint8_t PIXEL_3;
};

void delete_TChannel_8_bit(TChannel_8_bit **point, int vyska){
  for(int i = 0; i < vyska; ++i)
    delete [] point[i];
  delete[] point;
}

void delete_TChannel3_8_bit(TChannel3_8_bit **point, int vyska){
  for(int i = 0; i < vyska; ++i)
    delete [] point[i];
  delete[] point;
}

void delete_TChannel4_8_bit(TChannel4_8_bit **point, int vyska){
  for(int i = 0; i < vyska; ++i)
    delete [] point[i];
  delete[] point;
}

bool flipImage ( const char  * srcFileName,
                 const char  * dstFileName,
                 bool          flipHorizontal,
                 bool          flipVertical )
{

  ifstream stream_in_0(srcFileName, ios::in | ios::binary);
  ifstream stream_in_1(srcFileName, ios::in | ios::binary);

	if(!stream_in_0)
		return false;

	if(!stream_in_1)
		return false;

  if(!stream_in_0.is_open())
    return false;

  if(!stream_in_1.is_open())
    return false;

  if(stream_in_0.fail())
    return false;

  if(stream_in_1.fail())
    return false;

  THeader head;
  THeader_copy head_copy;

  if ( !(stream_in_0 . read ( (char*)&head, sizeof ( head ) ) ) || stream_in_0.fail() )
    return false;

  if ( !(stream_in_1 . read ( (char*)&head_copy, sizeof ( head_copy ) ) ) || stream_in_1.fail() )
    return false;

  if ( head_copy.ENDIAN != ENDIAN_LITTLE )
    return false;

  if (!(head_copy.FORMAT == 12 || head_copy.FORMAT == 14 || head_copy.FORMAT == 15)){
    return false;
  }

  if (!(head_copy.SIRKA > 0))
    return false;

  if(!(head_copy.VYSKA > 0))
    return false;

  ofstream stream_out_0(dstFileName, ios::out | ios::binary);

  if(!stream_out_0)
    return false;

  if(!stream_out_0.is_open())
    return false;

  if(stream_out_0.fail())
    return false;

  if(head_copy.FORMAT == 12){
    TChannel_8_bit c18;

    TChannel_8_bit** display = new TChannel_8_bit*[head_copy.VYSKA];
    for(int i = 0; i < head_copy.VYSKA; ++i)
        display[i] = new TChannel_8_bit[head_copy.SIRKA];

    for(int i = 0; i < head_copy.VYSKA; ++i ){
      for(int j = 0; j < head_copy.SIRKA; ++j){
        if(!stream_in_0.eof() && !stream_in_0.fail() && stream_in_0.is_open()){
          stream_in_0.read( (char*)&display[i][j], sizeof ( c18 ) );
        }
        else{
          delete_TChannel_8_bit(display, head_copy.VYSKA);
          return false;
        }
      }
    }

  if(!stream_out_0.fail()){
    stream_out_0 << head.ENDIAN_0 << head.ENDIAN_1 << head.SIRKA_0 << head.SIRKA_1 << head.VYSKA_0 << head.VYSKA_1 << head.FORMAT_0 << head.FORMAT_1;
    if(stream_out_0.fail())
      return false;
  }

  if(flipHorizontal == true && flipVertical == false){
    for(int i = 0; i < head_copy.VYSKA; ++i){
      for(int j = head_copy.SIRKA - 1; j >= 0; --j ){
        if(!stream_out_0.fail()){
          stream_out_0 << display[i][j].PIXEL;
          if(stream_out_0.fail())
            return false;
        }
      }
    }
  }

  if(flipHorizontal == false && flipVertical == true){
    for(int i = head_copy.VYSKA - 1; i >= 0; --i){
      for(int j = 0; j < head_copy.SIRKA; ++j){
        if(!stream_out_0.fail()){
          stream_out_0 << display[i][j].PIXEL;
          if(stream_out_0.fail())
            return false;
        }
      }
    }
  }

  if(flipHorizontal == true && flipVertical == true){
    for(int i = head_copy.VYSKA - 1; i >= 0; --i){
      for(int j = head_copy.SIRKA - 1; j >= 0; --j){
        if(!stream_out_0.fail()){
          stream_out_0 << display[i][j].PIXEL;
          if(stream_out_0.fail())
            return false;
        }
      }
    }
  }

  if(flipHorizontal == false && flipVertical == false){
    for(int i = 0; i < head_copy.VYSKA; ++i){
      for(int j = 0; j < head_copy.SIRKA; ++j){
        if(!stream_out_0.fail()){
          stream_out_0 << display[i][j].PIXEL;
          if(stream_out_0.fail())
            return false;
        }
      }
    }
  }

  delete_TChannel_8_bit(display, head_copy.VYSKA);
}

  if(head_copy.FORMAT == 14){
    TChannel3_8_bit c38;

    TChannel3_8_bit** display = new TChannel3_8_bit*[head_copy.VYSKA];
    for(int i = 0; i < head_copy.VYSKA; ++i)
        display[i] = new TChannel3_8_bit[head_copy.SIRKA];

    for(int i = 0; i < head_copy.VYSKA; ++i ){
      for(int j = 0; j < head_copy.SIRKA; ++j){
        if(!stream_in_0.eof() && !stream_in_0.fail() && stream_in_0.is_open()){
          stream_in_0.read( (char*)&display[i][j], sizeof ( c38 ) );
        }
        else{
          delete_TChannel3_8_bit(display, head_copy.VYSKA);
          return false;
        }
      }
    }

  if(!stream_out_0.fail()){
    stream_out_0 << head.ENDIAN_0 << head.ENDIAN_1 << head.SIRKA_0 << head.SIRKA_1 << head.VYSKA_0 << head.VYSKA_1 << head.FORMAT_0 << head.FORMAT_1;
    if(stream_out_0.fail())
      return false;
  }
  if(flipHorizontal == true && flipVertical == false){
    for(int i = 0; i < head_copy.VYSKA; ++i){
      for(int j = head_copy.SIRKA - 1; j >= 0; --j ){
        if(!stream_out_0.fail()){
          stream_out_0 << display[i][j].PIXEL_0 << display[i][j].PIXEL_1 << display[i][j].PIXEL_2;
          if(stream_out_0.fail())
            return false;
        }
      }
    }
  }

  if(flipHorizontal == false && flipVertical == true){
    for(int i = head_copy.VYSKA - 1; i >= 0; --i){
      for(int j = 0; j < head_copy.SIRKA; ++j){
        if(!stream_out_0.fail()){
          stream_out_0 << display[i][j].PIXEL_0 << display[i][j].PIXEL_1 << display[i][j].PIXEL_2;
          if(stream_out_0.fail())
            return false;
        }
      }
    }
  }

  if(flipHorizontal == true && flipVertical == true){
    for(int i = head_copy.VYSKA - 1; i >= 0; --i){
      for(int j = head_copy.SIRKA - 1; j >= 0; --j){
        if(!stream_out_0.fail()){
          stream_out_0 << display[i][j].PIXEL_0 << display[i][j].PIXEL_1 << display[i][j].PIXEL_2;
          if(stream_out_0.fail())
            return false;
        }
      }
    }
  }

  if(flipHorizontal == false && flipVertical == false){
    for(int i = 0; i < head_copy.VYSKA; ++i){
      for(int j = 0; j < head_copy.SIRKA; ++j){
        if(!stream_out_0.fail()){
          stream_out_0 << display[i][j].PIXEL_0 << display[i][j].PIXEL_1 << display[i][j].PIXEL_2;
          if(stream_out_0.fail())
            return false;
        }
      }
    }
  }
  delete_TChannel3_8_bit(display, head_copy.VYSKA);

  }

  if(head_copy.FORMAT == 15){
    TChannel4_8_bit c48;

    TChannel4_8_bit** display = new TChannel4_8_bit*[head_copy.VYSKA];
    for(int i = 0; i < head_copy.VYSKA; ++i)
        display[i] = new TChannel4_8_bit[head_copy.SIRKA];

    for(int i = 0; i < head_copy.VYSKA; ++i ){
      for(int j = 0; j < head_copy.SIRKA; ++j){
        if(!stream_in_0.eof() && !stream_in_0.fail() && stream_in_0.is_open()){
          stream_in_0.read( (char*)&display[i][j], sizeof ( c48 ) );
        }
        else{
          delete_TChannel4_8_bit(display, head_copy.VYSKA);
          return false;
        }
      }
    }

  if(!stream_out_0.fail()){
    stream_out_0 << head.ENDIAN_0 << head.ENDIAN_1 << head.SIRKA_0 << head.SIRKA_1 << head.VYSKA_0 << head.VYSKA_1 << head.FORMAT_0 << head.FORMAT_1;
    if(stream_out_0.fail())
      return false;
  }
  if(flipHorizontal == true && flipVertical == false){
    for(int i = 0; i < head_copy.VYSKA; ++i){
      for(int j = head_copy.SIRKA - 1; j >= 0; --j ){
        if(!stream_out_0.fail()){
          stream_out_0 << display[i][j].PIXEL_0 << display[i][j].PIXEL_1 << display[i][j].PIXEL_2 << display[i][j].PIXEL_3;
          if(stream_out_0.fail())
            return false;
        }
      }
    }
  }

  if(flipHorizontal == false && flipVertical == true){
    for(int i = head_copy.VYSKA - 1; i >= 0; --i){
      for(int j = 0; j < head_copy.SIRKA; ++j){
        if(!stream_out_0.fail()){
          stream_out_0 << display[i][j].PIXEL_0 << display[i][j].PIXEL_1 << display[i][j].PIXEL_2 << display[i][j].PIXEL_3;
          if(stream_out_0.fail())
            return false;
        }
      }
    }
  }

  if(flipHorizontal == true && flipVertical == true){
    for(int i = head_copy.VYSKA - 1; i >= 0; --i){
      for(int j = head_copy.SIRKA - 1; j >= 0; --j){
        if(!stream_out_0.fail()){
          stream_out_0 << display[i][j].PIXEL_0 << display[i][j].PIXEL_1 << display[i][j].PIXEL_2 << display[i][j].PIXEL_3;
          if(stream_out_0.fail())
            return false;
        }
      }
    }
  }

  if(flipHorizontal == false && flipVertical == false){
    for(int i = 0; i < head_copy.VYSKA; ++i){
      for(int j = 0; j < head_copy.SIRKA; ++j){
        if(!stream_out_0.fail()){
          stream_out_0 << display[i][j].PIXEL_0 << display[i][j].PIXEL_1 << display[i][j].PIXEL_2 << display[i][j].PIXEL_3;
          if(stream_out_0.fail())
            return false;
        }
      }
    }
  }
  delete_TChannel4_8_bit(display, head_copy.VYSKA);
  }

  stream_in_0.close();
  stream_in_1.close();
  stream_out_0.close();

  return true;
}

#ifndef __PROGTEST__
bool identicalFiles ( const char * fileName1,
                      const char * fileName2 )
{
  // DIY
  ifstream stream_in0(fileName1, ios::in | ios::binary);
  ifstream stream_in1(fileName2, ios::in | ios::binary);

  while((!stream_in0.eof()) && (!stream_in1.eof())){
    uint8_t byte_0, byte_1;
    stream_in0.read( (char*)&byte_0, sizeof ( byte_0 ) );
    stream_in1.read( (char*)&byte_1, sizeof ( byte_1 ) );

    if(!(byte_0 == byte_1)){
      return false;
    }
  }

  return true;
}

int main ( void )
{
  assert (flipImage ( "input_00.img", "output_00.img", true, false )
              && identicalFiles ( "output_00.img", "ref_00.img" ) );

  assert (flipImage ( "input_01.img", "output_01.img", false, true )
              && identicalFiles ( "output_01.img", "ref_01.img" ) );

  assert ( flipImage ( "input_02.img", "output_02.img", true, true )
              && identicalFiles ( "output_02.img", "ref_02.img" ) );

  assert ( flipImage ( "input_03.img", "output_03.img", false, false )
              && identicalFiles ( "output_03.img", "ref_03.img" ) );

  assert ( flipImage ( "input_04.img", "output_04.img", true, false )
              && identicalFiles ( "output_04.img", "ref_04.img" ) );

  assert ( flipImage ( "input_05.img", "output_05.img", true, true )
              && identicalFiles ( "output_05.img", "ref_05.img" ) );

  assert ( flipImage ( "input_06.img", "output_06.img", false, true )
              && identicalFiles ( "output_06.img", "ref_06.img" ) );

  assert ( flipImage ( "input_07.img", "output_07.img", true, false )
              && identicalFiles ( "output_07.img", "ref_07.img" ) );

  assert ( flipImage ( "input_08.img", "output_08.img", true, true )
              && identicalFiles ("output_08.img", "ref_08.img"));

  assert (!flipImage ( "input_09.img", "output_09.img", true, false ));

  // // extra inputs (optional & bonus tests)
  // assert ( flipImage ( "extra_input_00.img", "extra_out_00.img", true, false )
  //          && identicalFiles ( "extra_out_00.img", "extra_ref_00.img" ) );
  // assert ( flipImage ( "extra_input_01.img", "extra_out_01.img", false, true )
  //          && identicalFiles ( "extra_out_01.img", "extra_ref_01.img" ) );
  // assert ( flipImage ( "extra_input_02.img", "extra_out_02.img", true, false )
  //          && identicalFiles ( "extra_out_02.img", "extra_ref_02.img" ) );
  // assert ( flipImage ( "extra_input_03.img", "extra_out_03.img", false, true )
  //          && identicalFiles ( "extra_out_03.img", "extra_ref_03.img" ) );
  // assert ( flipImage ( "extra_input_04.img", "extra_out_04.img", true, false )
  //          && identicalFiles ( "extra_out_04.img", "extra_ref_04.img" ) );
  // assert ( flipImage ( "extra_input_05.img", "extra_out_05.img", false, true )
  //          && identicalFiles ( "extra_out_05.img", "extra_ref_05.img" ) );
  // assert ( flipImage ( "extra_input_06.img", "extra_out_06.img", true, false )
  //          && identicalFiles ( "extra_out_06.img", "extra_ref_06.img" ) );
  // assert ( flipImage ( "extra_input_07.img", "extra_out_07.img", false, true )
  //          && identicalFiles ( "extra_out_07.img", "extra_ref_07.img" ) );
  // assert ( flipImage ( "extra_input_08.img", "extra_out_08.img", true, false )
  //          && identicalFiles ( "extra_out_08.img", "extra_ref_08.img" ) );
  // assert ( flipImage ( "extra_input_09.img", "extra_out_09.img", false, true )
  //          && identicalFiles ( "extra_out_09.img", "extra_ref_09.img" ) );
  // assert ( flipImage ( "extra_input_10.img", "extra_out_10.img", true, false )
  //          && identicalFiles ( "extra_out_10.img", "extra_ref_10.img" ) );
  // assert ( flipImage ( "extra_input_11.img", "extra_out_11.img", false, true )
  //          && identicalFiles ( "extra_out_11.img", "extra_ref_11.img" ) );
  return 0;
}
#endif /* __PROGTEST__ */
