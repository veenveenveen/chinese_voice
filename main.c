//
//  main.cpp
//  socket_linux_c++
//
//  Created by 黄启明 on 2017/6/7.
//  Copyright © 2017年 黄启明. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include<string.h>

#define SERVER_IP "192.168.18.132"
#define SERVER_PORT 61000


const char *filename = "/home/hqm/桌面/Chinese_voice/results/result";

int main(int argc, const char * argv[]) {
    
    int server_sockfd;//服务器socket
    struct sockaddr_in server_addr;//服务器网络地址结构体
    server_addr.sin_family = AF_INET;//设为IP通讯
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);//服务器IP地址，允许连接到所有本地地址上
    server_addr.sin_port = htons(SERVER_PORT);//服务器端口号
    bzero(&(server_addr.sin_zero), 8);
    
    /*创建服务器端套接字--IPv4协议，面向连接通信，udp协议*/
    if ((server_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("server error");
        return 1;
    }
    
    FILE *fp;
    
    ///从文件中读取数据
    int N = 100;
    char str[N+1];
    memset(str, 0, N+1);
    if( (fp=fopen(filename,"rt")) == NULL ){
        printf("Cannot open file, press any key to exit!\n");
        exit(1);
    }
    
    while(fgets(str, N, fp) != NULL){
        printf("%s", str);
    }
    
    for (int i = 0; i < strlen(str)/4; i++) {
        printf("%c",((str[4*i + 1]-'0')*64 + (str[4*i + 2]-'0')*8 + (str[4*i + 3]-'0')));
    }
    
    printf("\n");
    
    fclose(fp);
    
    char buffer[12]={0};
    
    //检查是否存在 “开” 或 “关”
    
    
    if (strstr(str, "\\345\\274\\200") != NULL) {
	printf("in here kai\n");
        strcpy(buffer, "OF1T00000a#");
    }else if (strstr(str, "\\345\\205\\263") != NULL) {
        strcpy(buffer, "OF0T00000b#");
	printf("in here guan\n");
    }else {
	printf("in here none\n");
    }
    
    sendto(server_sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    close(server_sockfd);
    
    return 0;
}
