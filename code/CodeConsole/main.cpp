#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include "handle.h"

void welcome();
void inputFromScreen(long *n, int *h);
long strToInt(char str[], int length);
int checkN(int n);
int checkH(int h);
void outputArrayToConsole(long a[], int num, int maxPerLine);

int main()
{
    long n;
    int h;
    long *ans = (long*)malloc(1000000*sizeof(long));
    int num;
    int doesContinue;
    char fileName[100];
    welcome();
    // input data
    do {
        printf("\nChon phuong thuc nhap du lieu: \n1.Nhap tu file\n2.Nhap tu ban phim\n");
        printf("Lua chon cua ban: ");
        int selection = getche();
        while (selection != '1' && selection != '2'){
            printf("\nLua chon sai, vui long chon lai: ");
            selection = getche();
        }
        if (selection == '2') inputFromScreen(&n, &h);
        else {
            printf("\nNhap ten file dau vao: ");
            gets(fileName);
            while (!read2NumberFromFile(fileName, &n, &h)){
                printf("\nDoc file khong thanh cong. Nhap lai ten file dau vao: ");
                gets(fileName);
            };

        }

        // sieve prime
        char A[n];
        sievePrime(A, n);
        // solve
        handle(n, h, ans, &num);
        // output
        printf("\nChon phuong xuat du lieu: \n1.Xuat ra file\n2.Xuat ra man hinh\n");
        printf("Lua chon cua ban: ");
        selection = getche();
        while (selection != '1' && selection != '2'){
            printf("\nLua chon sai, vui long chon lai: ");
            selection = getche();
        }
        if (selection == '2') outputArrayToConsole(ans, num, 5);
        else {
            printf("\nNhap ten file xuat du lieu: ");
            gets(fileName);
            while (!writeArrayToFile(fileName, ans, num)){
                printf("\nGhi file khong thanh cong. Nhap lai ten file: ");
                gets(fileName);
            };
        }

        printf("\nEnter de tiep tuc!");
        doesContinue = getche();
    } while (doesContinue == 13);



    return 0;
}

void welcome(){
    printf("+--------------Khoa Cong nghe Thong tin - Dai hoc Bach Khoa Da Nang--------------+\n");
    printf("|________De tai: Liet ke cac so nguyen to khong vuot qua n co chieu cao h________|\n");
    printf("+---------------Sinh vien: Nguyen Huy Tuong - GVHD: ThS. Nguyen Van Nguyen------------+\n\n\n\n");
}
long strToInt(char str[], int length){
    long ans = 0;
    for (int i = 0;i < length;i++){
        if (str[i] < '0' || str[i] > '9') return -1;
        ans = ans*10 + (str[i] - 48);
    }
    return ans;
}
int checkN(long n){
    return n >= 10 && n <= 1000000;
};
int checkH(int h){
    return h >= 1 && h <= 54;
};
void inputFromScreen(long *n, int *h){
    char str[100];
    printf("\nNhap n: ");
    gets(str);
    while (strlen(str) > 7 || (*n = strToInt(str, strlen(str))) == -1 || !checkN(*n)){
        printf("\nKhong hop le. Nhap lai n: ");
        gets(str);
    }
    printf("\nNhap h: ");
    gets(str);
    while (strlen(str) > 2 || (*h = strToInt(str, strlen(str))) == -1 || !checkH(*h)){
        printf("\nKhong hop le. Nhap lai h: ");
        gets(str);
    }
}
void outputArrayToConsole(long a[], int num, int maxPerLine){
    printf("\n");
    if (num == 0){
        printf("Khong co phan tu nao!\n");
        return;
    } else {
        printf("Co tong cong %d phan tu!\n", num);
    }
    int line = maxPerLine;
    for (int i = 0;i < num;i++){
        if (line == 0){
            line = maxPerLine;
            printf("\n");
        }
        line--;
        printf("%10d", a[i]);
    };
}
