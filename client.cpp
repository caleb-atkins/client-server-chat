/***************************************************
Caleb Atkins
client.cpp - set up client connection to chat server
***************************************************/

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>

using namespace std;

int main()
{
  cout << "Connecting client..." << endl;

  /*----Initialize variables----*/

  const int portNumber = 5000;
  char buffer[1024];

  // initialize socket & make space
  struct sockaddr_in sock;
  memset((char *) &sock, 0, sizeof(sock));

  /*----Create socket (file descriptor)----*/

  // IPv4 stream socket file descriptor
	int sockFD = socket(PF_INET, SOCK_STREAM, 0);

  // check for socket error
  if(sockFD == -1)
  {
		cout << "<--- ERROR: SOCKET CREATION FAILED --->" << endl;
	}

  // good to go!
  else
  {
    /*----Create socket structure----*/

    // set to IPv4
   	sock.sin_family = AF_INET;

    // localhost IP
  	sock.sin_addr.s_addr = inet_addr("127.0.0.1");

    // port 5000 in NBO
   	sock.sin_port = htons(portNumber);

    /*----Connect socket----*/

   	int sockConnStatus = connect(sockFD, (struct sockaddr*)&sock, sizeof(sock));

    // check for socket connectivity failure
   	if(sockConnStatus == -1)
    {
   		cout << "<--- ERROR: SOCKET CONNECTION FAILED --->" << endl;
   	}

    // connection successfull
   	else
    {
      cout << "Connected! Enjoy!" << endl;

      // enter chat
      while(true)
      {
        // make space for and receive client input to send to server
        memset(buffer, 0, 1024);
    	  cin.getline(buffer, '\n');

        // write to socket file descriptor
				int writeStatus = write(sockFD, buffer, 20);

				if(writeStatus == -1)
        {
				  cout << "<--- ERROR: SOCKET FD WRITE FAILED --->" << endl;
				}

        // make space for and receive server message
        memset(buffer, 0, 256);
				int readStatus = read(sockFD, buffer, 255);
				cout << buffer << endl;

				if(readStatus == -1)
        {
					cout << "<--- ERROR: SOCKET FD READ FAILED --->" << endl;
				}
   		}
   	}
	}
}
