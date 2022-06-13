#ifndef __PROGTEST__
#include <cctype>
#include <cassert>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <set>
#include <list>
#include <forward_list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <deque>
#include <optional>
#include <variant>
#include <any>
#include <algorithm>
#include <functional>
#include <memory>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

template <typename _Type , typename _Comparator = std::equal_to<> /* todo */ >
class CSearch
{
private:
    _Comparator cmp;
public:
    // default constructor
    // constructor with comparator parameter
    // destructor (if needed)
    CSearch() : cmp(equal_to<>()) {}
    CSearch(_Comparator cmp) : cmp(cmp) {}

      vector<pair<int, _Type*>> dataToBeFound;
              CSearch ( const CSearch & src ) = delete;
    CSearch & operator = ( const CSearch & src ) = delete;
    void      Add(int           id,
        const _Type& needle)
    {
        dataToBeFound.push_back(make_pair(id, new _Type(needle)));
    }
    set<int>  Search(const _Type& hayHeap) const
    {
        set<int> res;
        for (auto& pair : dataToBeFound)
        {
            int index = pair.first;
            _Type& needle = *pair.second;
            typename _Type::const_iterator start = hayHeap.begin();
            while (start != hayHeap.end())
            {
                auto needlePosition = needle.begin();
                auto heapPosition = start;
                bool found = true;
                while (needlePosition != needle.end())
                {
                    if (!cmp(*needlePosition, *heapPosition))
                    //if (*needlePosition != *heapPosition)
                    {
                        found = false;
                        break;
                    }
                    ++heapPosition;
                    ++needlePosition;
                }
                if (found)
                {
                    res.insert(index);
                    break;
                }
                ++start;
            }
        }
        return res;
    }
    ~CSearch()
    {
        for (auto& pair : dataToBeFound)
        {
            delete pair.second;
        }
    }
};
//-------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
class CharComparator
{
  public:
               CharComparator ( bool caseSensitive = true )
      : m_CaseSensitive ( caseSensitive )
    {
    }
    bool       operator () ( const char & a, const char & b ) const
    {
      return m_CaseSensitive ? a == b : toupper (a) == toupper (b);
    }
  private:
    bool       m_CaseSensitive;
};
//-------------------------------------------------------------------------------------------------
bool upperCaseCompare ( const char & a, const char & b )
{
  return toupper ( a ) == toupper ( b );
}
//-------------------------------------------------------------------------------------------------
int main ( void )
{
  CSearch <string> test1;
  test1 . Add    ( 0, "hello" );
  test1 . Add    ( 1, "world" );
  test1 . Add    ( 2, "rld" );
  test1 . Add    ( 3, "ell" );
  test1 . Add    ( 4, "hell" );
  assert ( test1 . Search ( "hello world!" ) == (set<int> { 0, 1, 2, 3, 4 }) );
  assert ( test1 . Search ( "hEllo world!" ) == (set<int> { 1, 2 }) );

  CSearch <string, bool (*)(const char &, const char &)> test2 ( upperCaseCompare );
  test2 . Add    ( 0, "hello" );
  test2 . Add    ( 1, "world" );
  test2 . Add    ( 2, "rld" );
  test2 . Add    ( 3, "ell" );
  test2 . Add    ( 4, "hell" );
  assert ( test2 . Search ( "HeLlO WoRlD!" ) == (set<int> { 0, 1, 2, 3, 4 }) );
  assert ( test2 . Search ( "hallo world!" ) == (set<int> { 1, 2 }) );

  CSearch <string, CharComparator> test3 ( CharComparator ( false ) );
  test3 . Add    ( 0, "hello" );
  test3 . Add    ( 1, "world" );
  test3 . Add    ( 2, "rld" );
  test3 . Add    ( 3, "ell" );
  test3 . Add    ( 4, "hell" );
  assert ( test3 . Search ( "heLLo world!" ) == (set<int> { 0, 1, 2, 3, 4 }) );
  assert ( test3 . Search ( "Well, templates are hell" ) == (set<int> { 3, 4 }) );

  CSearch <vector<int> > test4;
  test4 . Add    ( 0, { 1, 6, 1, 6, 9, 12 } );
  test4 . Add    ( 1, { 9, 12, 7 } );
  assert ( test4 . Search ( vector<int> { 1, 6, 1, 6, 1, 6, 9, 12, 8 } ) == (set<int> { 0 }) );
  assert ( test4 . Search ( vector<int> { 1, 1, 6, 1, 6, 8, 12, 8 } ) == (set<int> {}) );

  CSearch <vector<string> > test5;
  test5 . Add    ( 0, { "Prague", "Bern", "Rome" } );
  test5 . Add    ( 1, { "London", "Prague", "Bern" } );
  test5 . Add    ( 2, { "London", "Rome" } );
  assert ( test5 . Search ( vector<string> { "Berlin", "London", "Prague", "Bern", "Rome", "Moscow" } ) == (set<int> { 0, 1 }) );

  CSearch <deque<int> > test6;
  test6 . Add    ( 0, { 1, 6, 1, 6, 9, 12 } );
  test6 . Add    ( 1, { 9, 12, 7 } );
  assert ( test6 . Search ( deque<int> { 1, 6, 1, 6, 1, 6, 9, 12, 8 } ) == (set<int> { 0 }) );

  CSearch <forward_list<int> > test7;
  test7 . Add    ( 0, { 1, 6, 1, 6, 9, 12 } );
  test7 . Add    ( 1, { 9, 12, 7 } );
  assert ( test7 . Search ( forward_list<int> { 1, 6, 1, 6, 1, 6, 9, 12, 8 } ) == (set<int> { 0 }) );

  CSearch <list<int> > test8;
  test8 . Add    ( 0, { 1, 6, 1, 6, 9, 12 } );
  test8 . Add    ( 1, { 9, 12, 7 } );
  assert ( test8 . Search ( list<int> { 1, 6, 1, 6, 1, 6, 9, 12, 8 } ) == (set<int> { 0 }) );


  return 0;
}
#endif /* __PROGTEST__ */
