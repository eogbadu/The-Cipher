#include "Cipher.h"

// Default constructor
// Description: Abstract class - cannot directly instantiate this class 
Cipher::Cipher()
{
  SetMessage("Not Encrypted");
  m_isEncrypted = false;
}

//Overloaded constructor
// Description: Abstract class - cannot directly instantiate this class 
Cipher::Cipher(string message, bool isEncrypted)
{
  SetMessage(message);
  m_isEncrypted = isEncrypted;
}

// Virtual Cipher destructor
Cipher::~Cipher()
{
  m_message = "";
  m_isEncrypted = false;
}

// Returns the message
string Cipher::GetMessage()
{
  return m_message;
}

// Returns isEncrypted (0 is not encrypted and 1 is encrypted)
bool Cipher::GetIsEncrypted()
{
  return m_isEncrypted;
}

// Updates a message
void Cipher::SetMessage(string message)
{
  m_message = message;
}

// Turns (true to false) or (false to true)
void Cipher::ToggleEncrypted()
{
  m_isEncrypted = (m_isEncrypted == true) ? false : true;
}

ostream &operator<<(ostream &output, Cipher &C)
{
  output << C.m_message << "(" << C.ToString() << ")" << endl;
  return output;
}
