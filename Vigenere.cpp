#include "Vigenere.h"

// Declare constants
const int NUM_ALPHABETS = 26;
const int UPPERCASE_MIN = 65;
const int UPPERCASE_MAX = 90;
const int LOWERCASE_MIN = 97;
const int LOWERCASE_MAX = 122;
const int UPPER_LOWER_DIFFERENCE = 32;

// Default constructor
Vigenere::Vigenere() : Cipher()
{
  m_key = "test";
}

// Overloaded constructor
Vigenere::Vigenere(string message, bool isEncrypted, string key)
  : Cipher(message, isEncrypted)
{
  m_key = key;
}

// Vigenere destructor
Vigenere::~Vigenere()
{
  // Left blank on purpose
}

// Encrypts using key (See project document for details) 
void Vigenere::Encrypt()
{
  // Declare variables
  string key;
  int keyLength = (int)key.length();
  int initialKeyLength = (int)m_key.length();
  int shift;
  
  if (!GetIsEncrypted())
  {
    // More local variables
    string message = GetMessage();
    int msgLength = (int)message.length();
    int i = 0;
    int j = 0;

    // Match key to message...preserving punctuation
    while (keyLength < msgLength)
    {
      if (((message[j] >= LOWERCASE_MIN) && (message[j] <= LOWERCASE_MAX))
	  || ((message[j] >= UPPERCASE_MIN) && (message[j] <= UPPERCASE_MAX)))
      {
	key += m_key[i];
	i++;
      }
      else
      {
	key += message[j];
      }
      j++;
      if (i >= initialKeyLength)
      {
	i = 0;
      }
      keyLength++;
    }
    
    // Encrypt the message - 4 cases
    for (int i = 0; i < (int)message.length(); i++)
    {
      // If the letter is in UPPER CASE
      if ((message[i] >= UPPERCASE_MIN) && (message[i] <= UPPERCASE_MAX))
      {
	// And the key is in UPPER CASE
	if ((key[i] >= UPPERCASE_MIN) && (key[i] <= UPPERCASE_MAX))
	{
	  shift = key[i] - UPPERCASE_MIN;
	  message[i] += shift;
	  
	  // Adjust to ensure message is in UPPER CASE
	  if (message[i] > UPPERCASE_MAX)
	  {
	    message[i] = message[i] - UPPERCASE_MAX + UPPERCASE_MIN;
	    message[i]--;
	  }
	}
	// And the key is in LOWER CASE
	else if ((key[i] >= LOWERCASE_MIN) && (key[i] <= LOWERCASE_MAX))
	{
	  // Change key to UPPER CASE
	  key[i] -= UPPER_LOWER_DIFFERENCE;
	  
	  shift = key[i] - UPPERCASE_MIN;
          message[i] += shift;

	  // Adjust to ensure message is in UPPER CASE
          if (message[i] > UPPERCASE_MAX)
          {
            message[i] = message[i] - UPPERCASE_MAX + UPPERCASE_MIN;
            message[i]--;
          }

	}
      }
      // If the letter is in LOWER CASE
      else if ((message[i] >= LOWERCASE_MIN) && (message[i] <= LOWERCASE_MAX))
      {
	// And the key is in UPPER CASE
	if ((key[i] >= UPPERCASE_MIN) && (key[i] <= UPPERCASE_MAX))
        {
	  // Change key to LOWER CASE
	  key[i] += UPPER_LOWER_DIFFERENCE;	  
          shift = key[i] - LOWERCASE_MIN;

	  // Adjust to ensure message is in LOWER CASE
	  if (( int(message[i]) + shift) > LOWERCASE_MAX)
	  {
	    message[i] -= NUM_ALPHABETS;
	  }

          message[i] += shift;
        }
	// And the key is in LOWER CASE
        else if ((key[i] >= LOWERCASE_MIN) && (key[i] <= LOWERCASE_MAX))
        {
          shift = key[i] - LOWERCASE_MIN;

	  // Adjust to ensure message is in LOWER CASE
	  if (( int(message[i]) + shift) > LOWERCASE_MAX)
          {
            message[i] -= NUM_ALPHABETS;
          }
	  
          message[i] += shift;
	}
      }
    }    
    SetMessage(message);
    ToggleEncrypted();
  }
}

// Decrypts using key (See project document for details)
void Vigenere::Decrypt()
{
  // Declare variables
  string key;
  int keyLength = (int)key.length();
  int initialKeyLength = (int)m_key.length();
  int shift;
  
  if (GetIsEncrypted())
  {
    // More local variables
    string message = GetMessage();
    int msgLength = (int)message.length();
    int i = 0;
    int j = 0;
    
    // Match key to message...preserving punctuation
    while (keyLength < msgLength)
    {
      if (((message[j] >= LOWERCASE_MIN) && (message[j] <= LOWERCASE_MAX))
          || ((message[j] >= UPPERCASE_MIN) && (message[j] <= UPPERCASE_MAX)))
      {
        key += m_key[i];
        i++;
      }
      else
      {
        key += message[j];
      }
      j++;
      if (i >= initialKeyLength)
      {
        i = 0;
      }
      keyLength++;
    }

    // Decrypt the message - 4 cases
    for (int i = 0; i < (int)message.length(); i++)
    {
      // If the letter is in UPPER CASE
      if ((message[i] >= UPPERCASE_MIN) && (message[i] <= UPPERCASE_MAX))
      {
	// And the key is in UPPER CASE                      
        if ((key[i] >= UPPERCASE_MIN) && (key[i] <= UPPERCASE_MAX))
        {
          shift = key[i] - UPPERCASE_MIN;
          message[i] -= shift;

          // Adjust to ensure message is in UPPER CASE
          if (message[i] < UPPERCASE_MIN)
          {
	    message[i] = UPPERCASE_MIN - message[i];
	    message[i] = UPPERCASE_MAX - message[i];
	    message[i]++;
          }
        }
	// And the key is in LOWER CASE
        else if ((key[i] >= LOWERCASE_MIN) && (key[i] <= LOWERCASE_MAX))
        {
          // Change key to UPPER CASE                      
          key[i] -= UPPER_LOWER_DIFFERENCE;

          shift = key[i] - UPPERCASE_MIN;
          message[i] -= shift;

          // Adjust to ensure message is in UPPER CASE
          if (message[i] < UPPERCASE_MIN)
          {
	    message[i] = UPPERCASE_MIN - message[i];
            message[i] = UPPERCASE_MAX - message[i];
            message[i]++;
          }
        }
      }
      // If the letter is in LOWER CASE 
      else if ((message[i] >= LOWERCASE_MIN) && (message[i] <= LOWERCASE_MAX))
      {
	// And the key is in UPPER CASE
        if ((key[i] >= UPPERCASE_MIN) && (key[i] <= UPPERCASE_MAX))
        {
          // Change key to LOWER CASE
          key[i] += UPPER_LOWER_DIFFERENCE;
	  
          shift = key[i] - LOWERCASE_MIN;
	  message[i] -= shift;
          // Adjust to ensure message is in LOWER CASE
	  if (message[i] < LOWERCASE_MIN)
	  {
	    message[i] = UPPERCASE_MIN - message[i];
	    message[i] = UPPERCASE_MAX - message[i];
	    message[i]++;
	  }
        }
	// And the key is in LOWER CASE
        else if ((key[i] >= LOWERCASE_MIN) && (key[i] <= LOWERCASE_MAX))
        {
	  shift = key[i] - LOWERCASE_MIN;
	  message[i] -= shift;
	  
	  if (message[i] < LOWERCASE_MIN)
	  {
	    message[i] = UPPERCASE_MIN - message[i];
	    message[i] = UPPERCASE_MAX - message[i];
	    message[i]++;
	  }
	}
      }
    }
    
    SetMessage(message);
    ToggleEncrypted();
  }
}

// A function that returns the string of the object type
string Vigenere::ToString()
{
  return "Vigenere";
}

// A function that returns the formatted output for Output function
string Vigenere::FormatOutput()
{
  stringstream ss;
  ss << 'v' << DELIMITER << GetIsEncrypted() << DELIMITER << GetMessage()
     << DELIMITER << m_key << endl;
  
  return ss.str();
}
