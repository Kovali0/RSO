/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main (){
	int sockfd;
	socklen_t len;
	struct sockaddr_in address;
	int result;
	char number;

	/*  Create a socket for the client.  */

	sockfd = socket (AF_INET, SOCK_STREAM, 0);

	/*  Name the socket, as agreed with the server.  */

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr ("127.0.0.1");
	address.sin_port = htons (9734);
	len = sizeof (address);

	/*  Now connect our socket to the server's socket.  */

	result = connect (sockfd, (struct sockaddr *) &address, len);

	if (result == -1)
	{
		perror ("oops: netclient");
		exit (1);
	}

	/*  We can now read/write via sockfd.  */
	//printf("Podaj znak testowy:");
	//scanf("%c",&ch);
	cout<<"Podaj liczbe do spierwiastkowania: ";
	cin>>number;
	write (sockfd, &number, 1);
	read (sockfd, &number, 1);
	cout<<"Pierwiastek z podanej wartosci: ";
	cout<<number;
	close (sockfd);
	exit (0);
}