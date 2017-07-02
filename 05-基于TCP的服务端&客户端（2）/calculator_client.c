#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

typedef struct CalculatorReq{
    char operandCount;  //操作数的个数
    char operator_;      //操作符
    int  operand[16];   //操作数 
}CalculatorReq;

typedef struct CalculatorRsp{
    int result; //计算结果
}CalculatorRsp;

void errorHandling(const char* message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char* argv[]){
    if(argc!=3){
        printf("Usage: %s <ip> <port> \n", argv[0]);
        exit(1);
    }

    int sock = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(argv[1]);
    servAddr.sin_port = htons(atoi(argv[2]));

    if(-1 == connect(sock, (struct sockaddr*)&servAddr, sizeof(servAddr))){
        errorHandling("connect() error!");
    }
    else{
        puts("Connected...");
    }

    puts("Please input operand count: ");
    
    CalculatorReq req;
    memset(&req, 0, sizeof(req));

    scanf("%d", (int*)&req.operandCount);

    for(int i=0;i<req.operandCount;i++){
        printf("Operand %d: \n", i+1);
        scanf("%d", &req.operand[i]);
    }

    puts("Please input operator:");
    fgetc(stdin);//由于59行需要输入字符，因此在此之前需要将缓存区中的'\n'清掉
    scanf("%c", &req.operator_);

    write(sock, (void*)&req, sizeof(req));

    CalculatorRsp rsp;
    memset(&rsp, 0, sizeof(rsp));

    read(sock,(void*)&rsp, sizeof(rsp));

    printf("Calculate result: %d \n", rsp.result);

    return 0;
}