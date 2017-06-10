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

#include <locale.h>


#include<string.h>

#define BACKLOG 5     //完成三次握手但没有accept的队列的长度
#define CONCURRENT_MAX 8   //应用层同时可以处理的连接
#define QUIT_CMD ".quit"

#define SERVER_PORT 9897
#define BUFFER_SIZE 1024


const char *filename = "/home/hqm/桌面/Chinese_voice/results/result";

int main(int argc, const char * argv[]) {
    setlocale(LC_ALL,"zh_CN.GBK"); 
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
                                //printf("%s", str);
                            }

			    for (int i = 0; i < strlen(str)/4; i++) {
				printf("%c",((str[4*i + 1]-'0')*64 + (str[4*i + 2]-'0')*8 + (str[4*i + 3]-'0')));
			    }

                            printf("\n");

                            fclose(fp);
                      

    return 0;
}
