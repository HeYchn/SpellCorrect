#include "func.h"

int main(int argc, char** argv){
	ISARGS_ERROR(3);
	//SOCKET//
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sfd){
		perror("socket");
		return -1;
	}
	//CONNECT//
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(struct sockaddr_in));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
	serverAddr.sin_port = htons(atoi(argv[2]));
	int ret;
	ret = connect(sfd, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr));
	if(-1 == ret){
		perror("connect");
		return -1;
	}
	printf("Connect successfully.\nServer IP : %s, PORT : %d\n", argv[1], atoi(argv[2]));
	int epfd = epoll_create(1);
	struct epoll_event event, evs[2];
	//注册epoll监听stdin//
	event.events = EPOLLIN;
	event.data.fd = 0;
	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &event);
	if(-1 == ret){
		perror("epoll_ctl_stdin");
		return -1;
	}
	char buf[1024] = {0};
	int rdyNum;
	while(1){
		rdyNum = epoll_wait(epfd, evs, 1, -1);
		if(-1 == rdyNum){
			perror("epoll_wait");
			return -1;
		}
		for(int i = 0; i < rdyNum; i++){
			//发送查询单词//
			if(0 == evs[i].data.fd){
				bzero(buf, sizeof(buf));
				read(0, buf, sizeof(buf));
				ret = send(sfd, buf, strlen(buf), 0);
				if(-1 == ret){
					perror("send query word");
					return -1;
				}
			}

			int resultSize = 0;
			ret = recv(sfd, &resultSize, sizeof(resultSize), 0);
			if(-1 == ret){
				perror("recv size");
				return -1;
			}
			
			bzero(buf, sizeof(buf));
			ret = recv(sfd, buf, resultSize, 0);
			if(-1 == ret){
				perror("recv result");
				return -1;
			}
			
			printf("--------\n");
			printf("%s\n", buf);
			printf("--------\n");
		}
	}
	
	close(sfd);
	return 0;
}
