#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	
	// Check input
	if (argc != 3){
		printf("Missing parameter!\n");
		printf("%d", argc);
		return 1;
	}


	int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(argv[1]);
	uint16_t dstPort = strtoul(argv[2], NULL, 10);
	addr.sin_port = htons(dstPort);

	int ret = connect(client, (struct sockaddr*)&addr, sizeof(addr));
	if (ret == -1){
		perror("Connect() failed");
		return 1;
	}

	char *msg = "Hello Server\n";
	send(client, msg, strlen(msg), 0);

	char buf[256];
	while (1){
		printf("Enter message:\n");
		fgets(buf, sizeof(buf), stdin);
		send(client, buf, strlen(buf), 0);

		if (strncmp(buf, "q", 1) == 0)	break;

	}			

	

	close(client);


}



