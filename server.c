//
//  main.c
//  socket_Linux
//
//  Created by 黄启明 on 2017/6/2.
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

#define BUFFER_SIZE 1024

#define SERVER_PORT 9897

#define kQUEUE 20

const char *filename = "/home/hqm/桌面/Chinese_voice/results/result";
const char *writeFilePath = "/home/hqm/桌面/Chinese_voice/receivedAudio/receivedAudioFile/voice.wav";

int main(int argc, const char * argv[]) {

    int server_sockfd;//服务器socket
    int client_sockfd;//客户端socket
    char buf[BUFFER_SIZE];
    
    struct sockaddr_in server_addr;//服务器网络地址结构体
    struct sockaddr_in client_addr;//服务器网络地址结构体
    unsigned int sin_size;
    
    server_addr.sin_family = AF_INET;//设为IP通讯
    server_addr.sin_addr.s_addr = INADDR_ANY;//服务器IP地址，允许连接到所有本地地址上
    server_addr.sin_port = htons(SERVER_PORT);//服务器端口号
    
    
    sin_size = sizeof(struct sockaddr_in);
    
    /*创建服务器端套接字--IPv4协议，面向连接通信，TCP协议*/
    if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("server error");
        return 1;
    }
    
    /*将套接字绑定到服务器的网络地址上*/
    if ((bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))) < 0) {
        perror("bind error");
        return 1;
    }
    
    /*监听连接请求--监听队列长度*/
    if (listen(server_sockfd, kQUEUE) < 0) {
        perror("listen error");
        return 1;
    }
    while(1) {
    /*等待客户端连接请求到达*/
    if ((client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &sin_size)) < 0) {
        perror("accept error");
        return 1;
    }
    
    printf("accept client %s\n",inet_ntoa(client_addr.sin_addr));
    
    if (send(client_sockfd, "welcome to my server\n", 21, 0) < 0) {//发送欢迎信息
        perror("send error");
        return 1;
    }
    
    // 打开文件，准备写入
    FILE *fp = fopen(writeFilePath, "w+");
    if(NULL == fp)
    {
        printf("File:\t%s Can Not Open To Write\n", writeFilePath);
        exit(1);
    }
    
    // 从服务器接收数据到buffer中
    // 每接收一段数据，便将其写入文件中，循环直到文件接收完并写完为止
    bzero(buf, BUFFER_SIZE);
    long int length = 0;
    while((length = recv(client_sockfd, buf, BUFFER_SIZE, 0)) > 0)
    {
        if(fwrite(buf, sizeof(char), length, fp) < length)
        {
            printf("File:\t%s Write Failed\n", writeFilePath);
            break;
        }
        bzero(buf, BUFFER_SIZE);
    }
    
    /*接收客户端的数据并将其发送给客户端--recv返回接收到的字节数，send返回发送的字节数*/
//    while ((len = recv(client_sockfd, buf, kBUFFER_SIZE, 0)) > 0) {
//        buf[len]='\0';
//        printf("%s\n",buf);
//        if (send(client_sockfd,buf,len,0) <0) {
//            perror("send error");
//            return 1;
//        }
//    }
    fclose(fp);
    printf("operation Failed\n");
    system("./voice_recognized.sh");
    close(client_sockfd);
}
    close(server_sockfd);
    
    
    return 0;
}
