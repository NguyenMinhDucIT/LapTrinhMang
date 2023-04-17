#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFF_SIZE 1024

typedef struct
{
    char mssv[10];
    char hoten[50];
    char ngaysinh[15];
    float diemtb;
} SinhVien;

int main(int argc, char *argv[])
{
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    int ret = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        perror("connect() failed");
        return 1;
    }

    char buf[BUFF_SIZE];
   
    while (1)
    {
        printf("Enter string:");
        fgets(buf, sizeof(buf), stdin);


        if (strncmp(buf, "q", 1) == 0)
            break;

        // Student Info
        SinhVien sv;
        printf("MSSV: ");
        fgets(sv.mssv, 10, stdin);
        printf("Name: ");
        fgets(sv.hoten, 50, stdin);
        printf("Date of Birth: ");
        fgets(sv.ngaysinh, 15, stdin);
        printf("CPA: ");
        scanf("%f", &sv.diemtb);
        getchar(); // Nhập vào kí tự '\n' ở cuối

        // Packaging data
        char buf[BUFF_SIZE];
        int offset = 0;
        memcpy(buf + offset, sv.mssv, strlen(sv.mssv));
        offset += strlen(sv.mssv);
        memcpy(buf + offset, sv.hoten, strlen(sv.hoten));
        offset += strlen(sv.hoten);
        memcpy(buf + offset, sv.ngaysinh, strlen(sv.ngaysinh));
        offset += strlen(sv.ngaysinh);
        memcpy(buf + offset, &sv.diemtb, sizeof(float));
        offset += sizeof(float);

        // Send to server
        if (send(client, buf, offset, 0) < 0)
        {
            perror("Failed to send data to server");
            return 1;
        }
    }

    close(client);
}
