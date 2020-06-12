#include "GUI.h"
#include <graphics.h>
#include <dos.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define HEIGHT 700
#define WIDTH 900
int min(int a, int b){
    return a > b ? b : a;
}
char* intToString(long n){
    if (n == 0) return "0";
    char *str = (char*)malloc(18*sizeof(char));
    long tmp = n;
    int length = 0;
    while (tmp != 0){
        str[length++] = ' ';
        tmp /= 10;
    }
    str[length] = '\0';
    while (n != 0){
        str[--length] = n%10 + 48;
        n /=10;
    }
    return str;
}
void outputTop(char str[], char str2[]){
    setcolor(4);
    outtextxy(WIDTH/2 - textwidth(str)/2, 160, str);
    outtextxy(WIDTH/2 - textwidth(str2)/2, 180, str2);
}
void createHeader(){
    char school[] = "Faculty of IT - Da Nang University of Technology";
    char title[] = "BASIC PROJECT";
    char info[] = "Full name: Nguyen Huy Tuong | Student code: 102190197";
    char nameProject[] = "LIST PRIMES LESS THAN OR EQUAL TO N, WHOSE HEIGHT EQUAL TO H";
    char advisor[] = "Advisor: Nguyen Van Nguyen";
    setcolor(12);
    rectangle(10, 10, WIDTH-10 ,150);
    settextstyle(0,0,2);
    setcolor(5);
    outtextxy(WIDTH/2 - textwidth(school)/2, 20, school);
    settextstyle(0,0,15);
    setcolor(10);
    outtextxy(WIDTH/2 - textwidth(title)/2, 40, title);
    settextstyle(0,0,2);
    setcolor(15);
    outtextxy(WIDTH/2 - textwidth(nameProject)/2, 80, nameProject);
    setcolor(11);
    outtextxy(WIDTH/2 - textwidth(info)/2, 100, info);
    setcolor(11);
    outtextxy(WIDTH/2 - textwidth(advisor)/2, 120, advisor);
    setcolor(15);
}
int getSelection(char menu[][100], int n){
    cleardevice();
    createHeader();
    char titleMenu[] = "Select option using arrow keys and enter key";
    settextstyle(4,0,2);
    setcolor(6);
    outtextxy(WIDTH/2 - textwidth(titleMenu)/2, 200, titleMenu);
    setcolor(7);
    int xOrigin = 300;
    int yOrigin = 300;
    for (int i = 0;i < n;i++){
        outtextxy(xOrigin, yOrigin + 50*i, menu[i]);
    }
    int selection = 0;
    setcolor(2);
    outtextxy(xOrigin - 50, yOrigin, "->");
    while (getch() == 0){
        int tmp = getch();
        outtextxy(xOrigin - 50, yOrigin + selection*50, "    ");
        selection = tmp == 72 ? selection - 1 : selection + 1;
        if (selection == -1) selection = n-1;
        if (selection == n) selection = 0;
        printf("\a");
        outtextxy(xOrigin - 50, yOrigin + selection*50, "->");
    }
    printf("\a \a");
    return selection;
}
void inputDataFromScreen(long *n, int *h, char title[]){
    //setup UI
    cleardevice();
    createHeader();
    outtextxy(WIDTH/2 - textwidth(title)/2, 250, title);
    outtextxy(230, 300, "Value of n:");
    rectangle(380, 290, 730 ,325);
    moveto(380, 290);
    outtextxy(230, 350, "Value of h:");
    rectangle(380, 340, 730 ,375);
    moveto(380, 290);
    // read input
    int c;
    char str1[18] = "_";
    char str2[18] = "_";
    outtextxy(390, 300, str1);
    int length = 0;
    do {
        c = getch();
        if (c == 13) break;
        if (c == 8){
            if (length == 0){
                printf("\a");
                continue;
            }
            str1[length - 1] = '_';
            str1[length] = ' ';
            outtextxy(390, 300, str1);
            str1[--length] = '\0';
            continue;
        }
        if (c < '0' || c > '9' || length >= 10){
            printf("\a");
            continue;
        }
        str1[length++] = c;
        str1[length] = '_';
        outtextxy(390, 300, str1);
    } while (1);
    *n = 0;
    //parse to int
    for (int i = 0;i < length;i++) *n = (*n)*10 + (str1[i] - 48);
    //get inpot
    outtextxy(390, 350, str2);
    length = 0;
    do {
        c = getch();
        if (c == 13) break;
        if (c == 8){
            if (length == 0){
                printf("\a");
                continue;
            }
            str2[length - 1] = '_';
            str2[length] = ' ';
            outtextxy(390, 350, str2);
            str2[--length] = '\0';
            continue;
        }
        if (c < '0' || c > '9'){
            printf("\a");
            continue;
        }
        str2[length++] = c;
        str2[length] = '_';
        outtextxy(390, 350, str2);
    } while (1);
    //parse to int
    *h = 0;
    for (int i = 0;i < length;i++) *h = (*h)*10 + (str2[i] - 48);
}
char* getStringFromScreen(char title[]){
    char *str = (char*)malloc(18);
    str[0] = '_';
    str[1] = '\0';
    int length = 0;
    cleardevice();
    createHeader();
    outtextxy(WIDTH/2 - strlen(title)*8, 200, title);
    while (1){
        outtextxy(WIDTH/2 - textwidth(str)/2, 250, str);
        str[length] = '\0';
        char c = getch();
        if (c == 13){
            if (length == 0){
                printf("\a");
                continue;
            } else {
                break;
            }
        }
        if (c == 8){
            if (length == 0){
                printf("\a");
                continue;
            }
            str[length - 1] = '_';
            str[length] = '\0';
            outtextxy(WIDTH/2 - textwidth(str)/2, 250, str);
            str[length--] = '\0';
            cleardevice();
            createHeader();
            outtextxy(WIDTH/2 - strlen(title)*8, 200, title);
            continue;
        }
        str[length++] = c;
        str[length] = '_';
        str[length+1] = '\0';
    }
    str[length] = '\0';
    return str;
}
void outputArrayToScreen(long a[], int n, int maximum){
    // init page
    int numOfPage = n/maximum + (n % maximum != 0);
    int currentPage = 1;
    //ahow array to screen
    do {
        cleardevice();
        createHeader();
        // setup title
        char sumary[200];
        char strBottom[200] = "";
        if (n == 0){
            strcpy(sumary, "0 number");
        } else if (n == 1){
            strcpy(sumary, "There is 1 number");
        } else {
            strcpy(sumary, "There are ");
            strcat(sumary, intToString(n));
            strcat(sumary, " numbers.");
        }
        if (n > maximum) strcpy(strBottom, "Using arrow keys to change page. The other key to return to menu");
        outputTop(sumary, strBottom);
        setcolor(15);
        settextstyle(0,0,13);
        // start render
        int x = 10;
        int y = 200;
        for (int i = (currentPage - 1) * maximum;i < min(currentPage*maximum, n);i++){
            outtextxy(x, y, intToString(a[i]));
            if (x > WIDTH - 240){
                x = 10;
                y += 15;
            } else {
                x += 125;
            }
        }
        // show current page
        char str[100] = "Page ";
        strcat(str, intToString(currentPage));
        strcat(str, " of ");
        strcat(str, intToString(numOfPage));
        outtextxy(WIDTH/2 - textwidth(str)/2,HEIGHT-15, str);
        //wait for press
        if (getch() == 0){
            int tmp = getch();
            if (tmp == 75){
                if (currentPage == 1) currentPage = numOfPage;
                else currentPage--;
            } else if (tmp == 77){
                if (currentPage == numOfPage) currentPage = 1;
                else currentPage++;
            }
        } else break;
    } while (1);

}
void pressAnyKeyToGoHome(){
    outtextxy(WIDTH/2 - textwidth("Press any key to return to the menu")/2,HEIGHT-15, "Press any key to return to the menu");
    getch();
}

