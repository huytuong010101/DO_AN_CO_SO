#include "GUI.h"
#include "handle.h"
#include <graphics.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define HEIGHT 700
#define WIDTH 900
#define MAXMAXTRIX 224
char menuList[][100] = {
        "Enter data from screen",
        "Enter data from file",
        "Exit",
    };
int numOfOption = 3;
char menuWayOutput[][100] = {
        "Export data to the screen",
        "Export data to the file",
    };
int numOfWayOutput = 2;
int main()
{
    long n;
    int h;
    char *inputFile, *outputFile;
    initwindow(WIDTH, HEIGHT, "Basic project");
    cleardevice();
    do {
        int selection = getSelection(menuList, numOfOption);
        if (selection == 2) break;
        int outSelection = getSelection(menuWayOutput, numOfWayOutput);
        switch (selection){
        case 0:
            inputDataFromScreen(&n, &h, "Enter n and h");
            while (!validateData(n, h)){
                inputDataFromScreen(&n, &h, "Data is not valid - Type again");
            }
            break;
        case 1:
            inputFile = getStringFromScreen("Enter name of input file");
            while (read2NumberFromFile(inputFile, &n, &h) == 0){
                inputFile = getStringFromScreen("Can\'t open file, please type again");
            }
            break;
        default:
            exit(0);
        }
        //handel
        outputTop("Processing. Please wait...", "");
        long *ans = (long*)malloc(sizeof(long)*1000000);
        int num;
        handle(n, h, ans, &num);
        //-----------
        if (outSelection == 1){
            outputFile = getStringFromScreen("Enter name of output file");
            while(!writeArrayToFile(outputFile, ans, num)){
                outputFile = getStringFromScreen("Can\'t write to file. Enter name of output file again");
            };
            pressAnyKeyToGoHome();
        } else {
            outputArrayToScreen(ans, num, MAXMAXTRIX);
        }
    } while (1);

    closegraph();
}
