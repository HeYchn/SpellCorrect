#include "func.h"

//设置非阻塞模式//
void SetNonblock(int fd){
	int status = fcntl(fd, F_GETFL);
	status = status | O_NONBLOCK;
	fcntl(fd, F_SETFL, status);
}

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
	//注册epoll监听sfd//
	event.events = EPOLLIN | EPOLLET;
	event.data.fd = sfd;
	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &event);
	if(-1 == ret){
		perror("epoll_ctl_sfd");
		return -1;
	}
	SetNonblock(sfd);
	//注册epoll监听stdin//
	event.events = EPOLLIN;
	event.data.fd = 0;
	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &event);
	if(-1 == ret){
		perror("epoll_ctl_stdin");
		return -1;
	}
	char buf[128] = {0};
	char word[64] = {0};
	int rdyNum;
	while(1){
		rdyNum = epoll_wait(epfd, evs, 2, -1);
		if(-1 == rdyNum){
			perror("epoll_wait");
			return -1;
		}
		for(int i = 0; i < rdyNum; i++){
			if(0 == evs[i].data.fd){
				//SEND//
				bzero(buf, sizeof(buf));
				read(0, buf, sizeof(buf));
				ret = send(sfd, buf, strlen(buf) - 1, 0);
				if(-1 == ret){
					perror("send");
					return -1;
				}
			}
			if(sfd == evs[i].data.fd){
				while(1){
					//RECV//
					bzero(buf, sizeof(buf));
					ret = recv(sfd, buf, sizeof(buf) - 1, 0);
					if(0 == ret){
						close(sfd);
						return 0;
					}
					else if(-1 == ret){
						break;
					}
					else{
						int j = 0;
						printf("--------\n");
						for(size_t i = 0; i < strlen(buf); i++){
							if(buf[i] != ' '){
								word[j++] = buf[i];
							}
							else{
								printf("%s\n", word);
								j = 0;
								bzero(word, sizeof(word));
							}
						}
					//	printf("%s\n", word);
						printf("--------\n");
					}
				}
			}
		}
	}
	close(sfd);

	return 0;
}
