#include <sstream>
using namespace std;

/**
 * Cast integer to string
 * @brief IntToString
 * @param integer to cast
 * @return string of the cast integer
 */
string intToString ( int number ) {
    ostringstream oss;
    oss << number;
    return oss.str();
}
