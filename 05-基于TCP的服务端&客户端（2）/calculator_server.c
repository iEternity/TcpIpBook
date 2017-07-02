#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

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

void calculateResult(const CalculatorReq& req, CalculatorRsp& rsp){
    rsp.result = req.operand[0];

    int operandCount = (int)req.operandCount;
    char ope = req.operator_;

    printf("OperandCount: %d \n", operandCount);
    printf("Operator: %c \n", ope);

    switch(ope){
        case '+':
                for(int i=1;i<operandCount;i++) rsp.result = rsp.result + req.operand[i];
                break;
        case '-':
                for(int i=1;i<operandCount;i++) rsp.result = rsp.result - req.operand[i];
                break;
        case '*':
                for(int i=1;i<operandCount;i++) rsp.result = rsp.result * req.operand[i];
                break;
        default:break;
    }
}

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }

    int sockServ = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));

    if(-1 == bind(sockServ, (struct sockaddr*)&servAddr, sizeof(servAddr))){
        errorHandling("bind() error!");
    }

    if(-1 == listen(sockServ, 5)){
        errorHandling("listen() error!");
    }

    while(1){
        int sockClient = accept(sockServ, 0, 0);
        if(-1 == sockClient){
            errorHandling("accept() error!");
        }
        else{
            puts("New client connected...");
        }

        CalculatorReq req;
        memset(&req, 0, sizeof(req));
        int readLen = read(sockClient, (void*)&req, sizeof(req));
        if(readLen == 0){
            puts("Client disconnected...");
            close(sockClient);
            continue;
        }

        CalculatorRsp rsp;
        calculateResult(req, rsp);

        write(sockClient, (void*)&rsp, sizeof(rsp));
    }

    close(sockServ);
    return 0;
}