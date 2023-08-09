#include "Ong.h"

// Declare constants
const int UPPERCASE_MIN = 65;
const int UPPERCASE_MAX = 90;
const int LOWERCASE_MIN = 97;
const int LOWERCASE_MAX = 122;
const int ONG_LENGTH = 3;
const string ONG = "ong";
const string DASH = "-";
const char DASH_CHAR = '-';

// Default constructor
Ong::Ong() : Cipher() {}

// Overloaded constructor 
Ong::Ong(string message, bool isEncrypted)
  : Cipher(message, isEncrypted)
{
}

// Ong Destructor
Ong::~Ong()
{
  // Left blank on purpose
}

// Returns true if vowel, space, or punctuation
bool Ong::IsVowel(char character)
{
  bool temp = false;
  if ((character >= 0) && (character <= UPPERCASE_MIN))
    temp = true;
  if ((character > UPPERCASE_MAX) && (character <= LOWERCASE_MIN))
    temp = true;
  if (character > LOWERCASE_MAX)
    temp = true;
  if ((character == 'e') || (character == 'E'))
    temp = true;
  if ((character == 'i') || (character == 'I'))
    temp = true;
  if ((character == 'o') || (character == 'O'))
    temp = true;
  if ((character == 'u') || (character == 'U'))
    temp = true;

 return temp;
}

// If vowel then vowel and dash displayed. dog = dong-o-gong            
// If consonant then consonant and ong and dash displayed. 
void Ong::Encrypt()
{
  if (!GetIsEncrypted())
  {
    string message1 = GetMessage();
    string message2;
    
    for (int i = 0; i < (int)message1.length(); i++)
    {
      if (!IsVowel(message1[i]))
      {
	message2 += message1[i];
	message2 += ONG;

	if  (((message1[i + 1] >= UPPERCASE_MIN)
          &&  (message1[i + 1] <= UPPERCASE_MAX))
          || ((message1[i + 1] >= LOWERCASE_MIN)
           && (message1[i + 1] <= LOWERCASE_MAX)))
	{
	  message2 += DASH;
	}
      }
      else
      {
	if  (((message1[i] >= UPPERCASE_MIN)
	   && (message1[i] <= UPPERCASE_MAX))
	  || ((message1[i] >= LOWERCASE_MIN)
	   && (message1[i] <= LOWERCASE_MAX)))
	{
	  message2 += message1[i];
	  if  (((message1[i + 1] >= UPPERCASE_MIN)
	    &&  (message1[i + 1] <= UPPERCASE_MAX))
	    || ((message1[i + 1] >= LOWERCASE_MIN)
	     && (message1[i + 1] <= LOWERCASE_MAX)))
	  {
	    message2 += DASH;
	  }
	}
	else
	{
	  message2 += message1[i];
	}
      }
    }
    SetMessage(message2);
    ToggleEncrypted();
  }
}

// Removes the dashes and "ong" when necessary cong-a-tong = cat
void Ong::Decrypt()
{
  if (GetIsEncrypted())
  {
    string message1 = GetMessage();
    string message2;

    for (int i = 0; i < (int)message1.length(); i++)
    {
      if (!IsVowel(message1[i]))
      {
	message2 += message1[i];
	i += ONG_LENGTH;
      }
      else
      {
	if  (((message1[i] >= UPPERCASE_MIN)
           && (message1[i] <= UPPERCASE_MAX))
          || ((message1[i] >= LOWERCASE_MIN)
           && (message1[i] <= LOWERCASE_MAX)))
	{
	  message2 += message1[i];
	}
	else if (message1[i] != DASH_CHAR)
	{
	  message2 += message1[i];
	}
      }
    }
    SetMessage(message2);
    ToggleEncrypted();
  }

}

// A function that returns the string of the object type
string Ong::ToString()
{
  return "Ong";
}

// A function that returns the formatted output for Output function
string Ong::FormatOutput()
{
  stringstream ss;
  ss << 'o' << DELIMITER << GetIsEncrypted() << DELIMITER << GetMessage()
     << DELIMITER << ' ' << endl;

  return ss.str();
}
