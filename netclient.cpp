/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <ctime>  
#include <string.h>
#include <stdlib.h>
#include "Message.hpp"
#include "endianlib.h"

using namespace std;

int main (){
	int sockfd;
	socklen_t len;
	struct sockaddr_in address;
	int result, war, wyb, ln;
	double number;
	char* dt = new char[25];
	//string dt;

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
		cout << strerror(errno) << endl;
		// perror ("oops: netclient");
		exit (1);
	}

	cout<<"Wielkosc wiadomosci: "<<sizeof(Message)<<endl;
	do{
		Message msg;
		cout<<"Wybierz opcje\n1-Pierwiastek\n2-Data i godzina\n3-Zamknij program"<<endl;
		cin>>wyb;
		msg.setChoice(swap_endian(wyb));
		switch(wyb){
			case 1:
				cout<<"Podaj liczbe do spierwiastkowania: ";
				cin>>number;
				cout<<swap_endian(number);
				msg.setValue(swap_endian(number));
				cout << "test" << endl;
				write (sockfd, &msg, sizeof(Message));
				read (sockfd, &msg, sizeof(Message));
				cout<<"Pierwiastek z podanej wartosci: ";
				//printf("%f",number);
				msg.setValue(swap_endian(msg.getValues()));
				cout<<msg.getValues()<<endl;
				cout<<"Chcesz zamknac program? (1-Tak, 2-Nie) ";
				cin>>wyb;
				msg.setChoice(swap_endian(wyb));
				write (sockfd, &msg, sizeof(Message));
				if(wyb==1){war=1;}
				else{war=0;}
			break;
			case 2:
				write (sockfd, &msg, sizeof(Message));
				read (sockfd, &msg, sizeof(Message));
				//ln = strlen(msg.getDT());
				// for(int i = 0; i<ln-1; i++){
				// 	read (sockfd, &dt[i], 1);
				// 	cout<<dt[i];
				// }
				//read (sockfd, &dt, sizeof(Message));
				cout<<"Data:"<<msg.getDT()<<endl;
				cout<<"Chcesz zamknac program? (1-Tak, 2-Nie) ";
				cin>>wyb;
				msg.setChoice(swap_endian(wyb));
				write (sockfd, &msg, sizeof(Message));
				if(wyb==1){war=1;}
				else{war=0;}
			break;
			case 3:
				war=1;
			break;
			default:
				cout<<"Wprowadzono niepoprawna opcje. Sprobuj jeszcze raz."<<endl;
				war=0;
			break;
			if(war==1){cout<<"Program zostanie zamkniety.";}

		}
	}while(war==0);
	close (sockfd);
	exit (0);
}
