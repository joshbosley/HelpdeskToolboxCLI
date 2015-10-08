#ifndef HDTB_DATATYPES
#define HDTB_DATATYPES

#include <map>
#include <stack>
#include <string>
#include <vector>

/*
        Map Items
*/

// Standard map item
typedef std::pair<std::string, int> HDTBMapItem;

// Standard-use map
typedef std::map<std::string, int> HDTBStandardMap;

// Standard map iterator
typedef std::map<std::string, int>::iterator HDTBMapIterator;

/*
        Stack items
*/

// History stack
typedef std::stack< std::vector<std::string> > HDTBHistory;

typedef std::vector<std::string>::iterator HDTBProcessIterator;

/*
        Other
*/
#define HDTB_UNUSED(expr) do { (void)(expr); } while (0)


#endif // HDTB_DATATYPES

