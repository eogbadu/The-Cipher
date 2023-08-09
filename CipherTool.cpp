#include "CipherTool.h"

// Declare constants
const string    TEXT = ".txt"; // The end of a text file name
const int TXT_LENGTH = 4;   // The length of .txt
const int MIN = 1;
const int MAX = 5;
const int UPPER_LOWER_DIFFERENCE = 32;

// Default constructor
CipherTool::CipherTool(string fileName)
{
  m_filename = fileName;
}

// CipherTool destructor
CipherTool::~CipherTool()
{
   for (unsigned int i = 0; i < m_ciphers.size(); i++)
  {
    delete m_ciphers.at(i);
  }
}

// Opens file and reads in each Cipher. Each Cipher dynamically allocated
void CipherTool::LoadFile()
{
  // Declare variables
  char cipherType;
  bool isEncrypted;
  string message;
  int shift;
  string key;
  Cipher *tempCipher;
  ifstream inStream;

  // Open to file to read and perform check
  // to make sure it opened successfully
  inStream.open(m_filename);
  if(inStream.fail())
  {
    cout << "File failed to load.\n";
  }
  else
  {
    while (inStream >> cipherType)
    {
      inStream.ignore(256, DELIMITER);
      inStream >> isEncrypted;
      inStream.ignore(256, DELIMITER);
      getline(inStream, message, DELIMITER);

      if (cipherType == 'c')
      {
	inStream >> shift;
	tempCipher = new Caesar(message, isEncrypted, shift);
      }
      else if (cipherType == 'v')
      {
	inStream >> key;
	tempCipher = new Vigenere(message, isEncrypted, key);
      }
      else
      {
	tempCipher = new Ong(message, isEncrypted);
      }

      m_ciphers.push_back(tempCipher);
     
    }

    inStream.close();
  }
}

// Displays each of the ciphers in the m_ciphers
void CipherTool::DisplayCiphers()
{
  for (unsigned int i = 0; i < m_ciphers.size(); i++)
  {
    cout << i + 1 << ". " <<*m_ciphers.at(i) << endl;
  }
}

// Encrypts or decrypts each of the ciphers in the m_ciphers
void CipherTool::EncryptDecrypt(bool encrypt)
{
  int count = 0;
  
  if (encrypt)
  {
    for (unsigned int i = 0; i < m_ciphers.size(); i++)
    {
      if (!m_ciphers.at(i)->GetIsEncrypted())
      {
	m_ciphers.at(i)->Encrypt();
	count++;
      }
    }
    cout << count << " ciphers encrypted" << endl;
  }
  else
  {
    for (unsigned int i = 0; i < m_ciphers.size(); i++)
    {
      if (m_ciphers.at(i)->GetIsEncrypted())
      {
	m_ciphers.at(i)->Decrypt();
	count++;
      }
    }
    cout << count << " ciphers decrypted" << endl;
  }
}

// Exports each of the ciphers in the m_ciphers (so they can be reused)
void CipherTool::Export()
{
  // Declare variables
  string fileName;
  ofstream myFile;
  int fileNameLength;
  int position1;

  // Get file name from user and validate
  cout << "What would you like to call the export file?" << endl;
  cin >> fileName;
  fileNameLength = int(fileName.length());
  position1 = fileNameLength - TXT_LENGTH;

  // Check if filename is too short or doesn't end with .txt
  while ((fileNameLength <= TXT_LENGTH)
	 || (fileName.substr(position1) != TEXT))
  {
    cout << "       ****FILE NAME ERROR****" << endl;
    cout << "File name must be at least 5 characters"
	 << " and must be a text file (.txt)\n" << endl;
    cout << "What would you like to call the export file?" << endl;
    cin >> fileName;
    fileNameLength = int(fileName.length());
    position1 = fileNameLength - TXT_LENGTH;
  }
  
  // Open to file to read and perform check
  // to make sure it opened successfully   
  myFile.open(fileName);
  if(myFile.fail())
  {
    cout << "File failed to load.\n";
  }
  else
  {
    for (unsigned int i = 0; i < m_ciphers.size(); i++)
    {
      cout << m_ciphers.at(i)->FormatOutput();
      myFile << m_ciphers.at(i)->FormatOutput();
    }
    myFile.close();
  }
}

// Displays menu and returns choice
int CipherTool::Menu()
{
  // Declare variables
  int choice;

  // Show menu and validate input
  do
  {
  cout << "What would you like to do?" << endl;
  cout << "1. Display All Ciphers" << endl;
  cout << "2. Encrypt All Ciphers" << endl;
  cout << "3. Decrypt All Ciphers" << endl;
  cout << "4. Export All Ciphers"  << endl;
  cout << "5. Quit" << endl;
  cin >> choice;
  } while ((choice < MIN) || (choice > MAX));
  
  return choice;
}

// Pass it a cipher and it returns the char of the subtype
char CipherTool::GetType(Cipher *cipher)
{
  string type = cipher->ToString();
  char letter = type[0] + UPPER_LOWER_DIFFERENCE;
  return letter;
}

// Loads input file, allows user to choose what to do
void CipherTool::Start()
{
  LoadFile();
  int choice = Menu();
  bool encrypt = true;
  while (choice != MAX)
  {
    switch (choice)
    {
    case 1:
      DisplayCiphers();
      break;
    case 2:
      EncryptDecrypt(encrypt);
      break;
    case 3:
      EncryptDecrypt(!encrypt);
      break;
    case 4:
      Export();
      cout << m_ciphers.size() << " ciphers exported" << endl;
      break;
    default:
      cout << "I'm done!" << endl;
      exit(1);
    }
    choice = Menu();
  }
  cout << "Thanks for using UMBC Encryption" << endl;
}

