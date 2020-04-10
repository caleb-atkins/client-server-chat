/*******************************
Caleb Atkins
server.cpp - spin up chat server
*******************************/

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

  cout << "Starting server..." << endl;

  /*----Initialize variables----*/

  const int port_number = 5000;
  char buffer[1024];

  // initialize server socket & make space
  struct sockaddr_in sock;
  memset((char *) &sock, 0, sizeof(sock));

  // initialize client socket & make space
  struct sockaddr_in clientSock;
  memset((char *) &clientSock, 0, sizeof(clientSock));

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
    sock.sin_port = htons(port_number);

    /*----Bind socket----*/

    int sockBindStatus =  bind(sockFD, (struct sockaddr *)&sock, sizeof(sock));

    // check for binding error
    if(sockBindStatus == -1)
    {
		  cout << "<--- ERROR: SOCKET BINDING FAILED --->" << endl;
	  }

    // pop open chat
    else
    {
      // wait for incoming client connections
	    int listenStatus = listen(sockFD, 10);

	    if(listenStatus != 0)
      {
	      cout << "<--- ERROR: LISTEN FAILED --->" << endl;
	    }

	    else
      {
	      cout << "Server started successfully! Awaiting client connection..." << endl;

        // fetch pending client connections
        socklen_t length_client = sizeof(clientSock);
	      sockFD =  accept(sockFD, (struct sockaddr *)&clientSock, &length_client);

	      if(sockFD == -1)
        {
          cout << "<--- ERROR: CLIENT SOCKET CONNECTION FAILED --->" << endl;
        }

        else
        {
          cout << "Client has connected! Enjoy!" << endl;

          while(true)
          {
            // make space for and receive client message
            memset(buffer, 0, 256);
            int readStatus = read(sockFD, buffer, 255);
            cout << buffer << endl;

            if(readStatus == -1)
            {
              cout << "<--- ERROR: SOCKET FD READ FAILED --->" << endl;
            }

            // make space for and receive server input to send to client
            memset(buffer, 0, 256);
            cin.getline(buffer, '\n');
            int writeStatus = write(sockFD, buffer, 12);

            if(writeStatus == -1)
            {
              cout << "<--- ERROR: SOCKET FD WRITE FAILED --->" << endl;
            }
          }
        }
      }
    }
  }
}
