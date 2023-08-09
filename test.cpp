#include <iostream>
#include <string>
using namespace std;


int main()
{

  const int NUM_ALPHABETS = 26;
  const int UPPERCASE_MIN = 65;
  const int UPPERCASE_MAX = 90;
  const int LOWERCASE_MIN = 97;
  const int LOWERCASE_MAX = 122;
  
  char message = 'b';
  
  
  cout << message << endl;
  if (message <= UPPERCASE_MIN)
    cout << "It's true" << endl;
  else
    cout << "It's false" << endl;
  return 0;
}
