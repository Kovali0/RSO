#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include <ctime>  
#include <string.h>
#include <stdlib.h>
#include "Message.hpp"

using namespace std;

int main(){
    
    int server_sockfd, client_sockfd;
	socklen_t server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	server_sockfd = socket (AF_INET, SOCK_STREAM, 0);

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl (INADDR_ANY);
	server_address.sin_port = htons (9734);
	server_len = sizeof (server_address);
	bind (server_sockfd, (struct sockaddr *) &server_address, server_len);

	/*  Create a connection queue and wait for clients.  */

	listen (server_sockfd, 5);

	while (1)
	{
		double number;
		int choice, war = 0, w;
		Message msg =  Message();

		printf ("server waiting for next client\n");

		/*	Accepting connection	*/

		client_len = sizeof (client_address);
		client_sockfd = accept (server_sockfd,(struct sockaddr *) &client_address,&client_len);
		
		//
		do{
			read (client_sockfd, &msg, sizeof(Message));
			choice=msg.getChoice();
			if(choice==1){
				number = msg.getValues();
				cout << number << endl;
				number = sqrt(number);
				//message = (char)number;
				cout << number << endl;
				msg.setValue(number);
				write (client_sockfd, &msg, sizeof(Message));
				read (client_sockfd, &msg, sizeof(Message));
				choice=msg.getChoice();
				if(w==1){war=1;}
				else{war=0;}
			}else{
				if(choice==2){
					time_t now = time(0);
					char* dt = ctime(&now);
					//string dt = ctime(&now);
					msg.setDT(dt);
					cout<<"Data: "<<msg.getDT();
					write (client_sockfd, &msg, sizeof(Message));
					// for(int i = 0; i<ln-1; i++){
					// 	cout<<dt[i];
					// 	write (client_sockfd, &dt[i], 1);
					// }
					//write (client_sockfd, &dt, sizeof(string));
					read (client_sockfd, &msg, sizeof(Message));
					choice=msg.getChoice();
					if(w==1){war=1;}
					else{war=0;}
				}
			}
		}while(war==0);
		close (client_sockfd);
	}
}