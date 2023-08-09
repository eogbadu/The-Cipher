#include "Caesar.h"

// Declare constants
const int NUM_ALPHABETS = 26;
const int UPPERCASE_MIN = 65;
const int UPPERCASE_MAX = 90;
const int LOWERCASE_MIN = 97;
const int LOWERCASE_MAX = 122;
const int DEFAULT_SHIFT = 3;

// Default constructor
Caesar::Caesar()
  : Cipher()
{
  m_shift = DEFAULT_SHIFT;
}

// Overloaded constructor
Caesar::Caesar(string message, bool isEncrypted, int shift)
  : Cipher(message, isEncrypted)
{
  m_shift = shift;
}

// Caesar destructor
Caesar::~Caesar()
{
  // Left blank on purpose
}

// Shifts characters right based on shift (lower stay lower, upper stays upper)
void Caesar::Encrypt()
{
  // Check if message is not encrypted
  if (!GetIsEncrypted())
  {
    // Get the message
    string message = GetMessage();

    // Go through each character in the message
    for (int i = 0; i < (int)message.length(); i++)
    {
      // If the character is in uppercase perform shift
      if ((message[i] >= UPPERCASE_MIN) && (message[i] <= UPPERCASE_MAX))
      {
	message[i] = message[i] + (m_shift % NUM_ALPHABETS);

	// If shifting takes the letter out of bounds
	// adjust it  (Z - shifted forward by 2 = B)
	if (message[i] > UPPERCASE_MAX)
	{
	  message[i] = message[i] - UPPERCASE_MAX + UPPERCASE_MIN;
	  message[i]--;
	}
      }
      // If the character is in lowercase perform shift
      else if ((message[i] >= LOWERCASE_MIN) && (message[i] <= LOWERCASE_MAX))
      {
	// If shifting will take letter out of bounds
	// adjust the character
	if (int(message[i]) + (m_shift % NUM_ALPHABETS) > LOWERCASE_MAX)
	{
	  message[i] -= NUM_ALPHABETS;
	}

	// Then perform shift
	message[i] = message[i] + (m_shift % NUM_ALPHABETS);
      }
    }
    
    SetMessage(message);
    ToggleEncrypted();
  }
}

// Shifts characters left based on shift (lower stay lower, upper stay upper)
void Caesar::Decrypt()
{
  // Check if message is encrypted
  if (GetIsEncrypted())
  {
    // Get the message
    string message = GetMessage();

    // Go through each character in the message 
    for (int i = 0; i < (int)message.length(); i++)
    {
      // If the character is in uppercase perform shift 
      if ((message[i] >= UPPERCASE_MIN) && (message[i] <= UPPERCASE_MAX))
      {
        message[i] = message[i] - (m_shift % NUM_ALPHABETS);
        if (message[i] < UPPERCASE_MIN)
        {
	  message[i] = UPPERCASE_MIN - message[i];
          message[i] = UPPERCASE_MAX - message[i];
	  message[i]++;
        }
      }
      // If the character is in lowercase perform shift 
      else if ((message[i] >= LOWERCASE_MIN) && (message[i] <= LOWERCASE_MAX))
      {
        message[i] = message[i] - (m_shift % NUM_ALPHABETS);
        if (message[i] < LOWERCASE_MIN)
        {
	  message[i] = UPPERCASE_MIN - message[i];
          message[i] = UPPERCASE_MAX - message[i];
	  message[i]++;
        }
      }
    }
    SetMessage(message);
    ToggleEncrypted();
  }

}

// A function that returns the string of the object type
string Caesar::ToString()
{
  return "Caesar";
}

// A function that returns the formatted output for Output function
string Caesar::FormatOutput()
{
  stringstream ss;
  ss << 'c' << DELIMITER << GetIsEncrypted() << DELIMITER << GetMessage()
     << DELIMITER << m_shift << endl;
  
  return ss.str();
}
