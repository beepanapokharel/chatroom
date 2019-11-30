/*
udp-recv: a simple udp server
	receive udp messages

        usage:  udp-recv
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
#include<regex>

#define BUFSIZE 2048
using namespace std;
std::vector<string> onlineusers;

void addtolist(string user){
	onlineusers.push_back(user);
}
void getnames(){
	for (int i = 0; i < onlineusers.size(); i++)
	   cout << onlineusers[i] << "\n";
	}
void deletefromlist(string user){
	//onlineusers.erase(user);
	std::vector<string>::iterator iter = onlineusers.begin();

         while (iter != onlineusers.end())
        {
                if(*iter == user)
                     {
                     	iter = onlineusers.erase(iter);
                     	break;
                     }
                else
                      iter++;
        }
}
int checklogin(string user){
	std::vector<string>::iterator iter = onlineusers.begin();

         while (iter != onlineusers.end())
        {
                if(*iter == user)
                      return 1;
                else
                      iter++;
        }
        return 0;
}

int main(int argc, char **argv)
{
	struct sockaddr_in myaddr;	/* our address */
	struct sockaddr_in remaddr;	/* remote address */
	socklen_t addrlen = sizeof(remaddr);		/* length of addresses */
	int recvlen;			/* # bytes received */
	int fd;
	string tempuser="";			/* our socket */
	int msgcnt = 0;			/* count # of messages we received */
	char buf[BUFSIZE];	/* receive buffer */

	/* create a UDP socket */
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		cerr << "cannot create socket" << endl;
		return 0;
	}

	/* bind the socket to any valid IP address and a specific port */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(SERVICE_PORT);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		cerr<< "bind failed \n";
		return 0;
	}

	/* now loop, receiving data and printing what we received */
	std::string Str="";
	while(1) {
		//printf("waiting on port %d\n", SERVICE_PORT);
		recvlen = recvfrom(fd, &buf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);

		if (recvlen > 0) {
			buf[recvlen] = 0;
			//printf("%s\" (%d bytes)\n", buf, recvlen);
			Str = std::string(buf);
			std::regex r("[_[:alnum:]]+:exit");
  			std::smatch m;
			if(std::regex_match(Str, m, r)) {
				tempuser="";
				tempuser = Str.substr(0, Str.find(":"));
				cout<<tempuser <<" exited chatroom. \n";
				deletefromlist(tempuser);
			}
			Str = std::string(buf);
			std::regex r1("[^:]");
  			std::smatch m1;
			if(std::regex_match(Str, m1, r1)){
				if(checklogin(Str))
				{
				tempuser = "duplicatelogin";
				strcpy(buf, tempuser.c_str());
			}
			else addtolist(Str);
			}

			cout<<buf <<"\n";
		}
		else
			cout <<"uh oh - something went wrong!\n";
		//sprintf(buf, "ack %d", msgcnt++);
		//printf("sending response \"%s\"\n", buf);
  		if(sendto(fd, &buf, strlen(buf), 0, (struct sockaddr *)&remaddr, addrlen) < 0)
				cerr<<"sendto";
		}
	/* never exits */

}
