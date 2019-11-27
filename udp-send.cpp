/*
udp-send: a simple udp client
	send udp messages
	The messages are sent to a port defined in SERVICE_PORT

        usage:  udp-send
*/

#include "port.h"
#include<signal.h>
#include <errno.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include "login.h"

#define BUFLEN 2048
using namespace std;
int main(void)
{
	struct sockaddr_in myaddr, remaddr;
	int fd;
	socklen_t slen = sizeof(remaddr);
	char buf[BUFLEN];	/* message buffer */
	int recvlen;
	int choice;
	string start_message=" Enter your choice: \n 1 for sign in 2 for sign up\n";		/* # bytes in acknowledgement message */
	string  sender_message="";
	char server[11] = "127.0.0.1";	/* change this to use a different server */
	string users[10];
	const char *cmd = "open -n Terminal";
	string tempuser="";
	/* create a socket */

	if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
		cout<<"socket created\n";

	/* bind it to all local addresses and pick any port number */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(0);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		cerr<< "bind failed \n";
		return 0;
	}

	/* now define remaddr, the address to whom we want to send messages */
	/* For convenience, the host address is expressed as a numeric IP address */
	/* that we will convert to a binary format via inet_aton */

	memset((char *) &remaddr, 0, sizeof(remaddr));
	remaddr.sin_family = AF_INET;
	remaddr.sin_port = htons(SERVICE_PORT);
	if (inet_aton(server, &remaddr.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	cout<<start_message;
	cin>>choice;
	tempuser=userlogin(choice);
	if(tempuser == "error")
		{
			cerr <<"\n try again\n";
			exit(1);
		}
	else
		{
		for (int i=0;i<no_of_users+1;i++){
			cout<<users[i] <<"\n";
			if(users[i] == tempuser) {
				cout<<tempuser <<"is logged in already";
				exit(1);
			}
		}

		cout<<"no of users : " <<no_of_users;
		no_of_users++;
		users[no_of_users] = tempuser;
		sender_message = tempuser + " entered chatroom\n";
		cout<< sender_message;
		}
	cin.ignore();
	strcpy(buf, sender_message.c_str());
	/* now let's send the messages */
	while(1)
	{

		//printf("Sending packet %d to %s port %d\n", i, server, SERVICE_PORT);
		//sprintf(buf, "message :%d  %s", i,sender_message);
		if (sendto(fd, &buf, strlen(buf), 0, (struct sockaddr *)&remaddr, slen)==-1) {
			cerr<<"sendto";
			exit(1);
		}
		/* now receive an acknowledgement from the server */
		recvlen = recvfrom(fd, (char*)&buf, BUFLEN, 0, (struct sockaddr *)&remaddr, &slen);
        if (recvlen >= 0) {
            buf[recvlen] = 0;	/* expect a printable string - terminate it */
            //cout<<"received message:"<< buf;
        }
		cout<< tempuser <<" : " ;
		getline(cin, sender_message);

    	if(sender_message=="exit") {
    		strcpy(buf, sender_message.c_str());
    		sendto(fd, &buf, strlen(buf), 0, (struct sockaddr *)&remaddr, slen);
    		for(int i=0;i<no_of_users;i++)
    		{
    			if(users[i]==tempuser){
    				for(int j=i;j<no_of_users-1;j++){
    					users[j] = users[j+1];
    				}
    				no_of_users--;
    				break;
    			}
    		}
    		exit(0);
    	}
    	if(sender_message=="terminal")
    	{
    		system(cmd);
    	}
    	//system("gnome-terminal");
    	sender_message = tempuser + ": " + sender_message;
    	strcpy(buf, sender_message.c_str());
	}
	close(fd);
	return 0;
}
