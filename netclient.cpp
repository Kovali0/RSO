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
		perror ("oops: netclient");
		exit (1);
	}

	do{
		cout<<"Wybierz opcje\n1-Pierwiastek\n2-Data i godzina"<<endl;
		cin>>wyb;
		switch(wyb){
			case 1:
				write (sockfd, &wyb, sizeof(int));
				cout<<"Podaj liczbe do spierwiastkowania: ";
				cin>>number;
				write (sockfd, &number, sizeof(double));
				read (sockfd, &number, sizeof(double));
				cout<<"Pierwiastek z podanej wartosci: ";
				//printf("%f",number);
				cout<<number<<endl;
				cout<<"Chcesz zamknac program? (1-Tak, 2-Nie) ";
				cin>>wyb;
				write (sockfd, &wyb, sizeof(int));
				if(wyb==1){war=1;}
				else{war=0;}
			break;
			case 2:
				write (sockfd, &wyb, sizeof(int));
				read (sockfd, &ln, sizeof(int));
				cout << ln << endl;
				for(int i = 0; i<ln-1; i++){
					read (sockfd, &dt[i], 1);
					cout<<dt[i];
				}
				//read (sockfd, &dt, sizeof(string));
				cout<<"\n"<<dt<<endl;
				cout<<"Chcesz zamknac program? (1-Tak, 2-Nie) ";
				cin>>wyb;
				write (sockfd, &wyb, sizeof(int));
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