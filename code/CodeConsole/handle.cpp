#include "handle.h"
#include <stdio.h>
#include <stdlib.h>
int validateData(int n,int h){
    return (n >= 10 && n <= 1000000 && h >= 1 && h <= 54);
}
void sievePrime(char arr[], long n){
    // function: sieve all primes from 0 to n, save to arr
    // after sieve, if arr[i] == 0 then i is a prime
    for (long i = 0;i <= n;i++) arr[i] = 0;
    arr[0] = arr[1] = 1;
    for (long i = 2;i*i <= n;i++){
        if (!arr[i]){
            for (long j = i*i;j <= n;j+=i){
                arr[j] = 1;
            }
        }
    }
}
int heightOfNumber(long n){
    // function: return height of n
    // height of a number is sum of all digits
    int ans = 0;
    while (n != 0){
        ans += n%10;
        n /= 10;
    }
    return ans;
}
int read2NumberFromFile(char path[], long *n, int *h){
    //read n from file path
    // return 1 if success
    *n = *h = -1;
    FILE *file = fopen(path, "r");
    if (file == NULL) return 0;
    fscanf(file, "%ld %d", n, h);
    fclose(file);
    if (*n == -1 || *h == -1) return 0;
    else return 1;
}
int writeArrayToFile(char path[], long arr[], int n){
    //write array arr to file path
    // return 1 if success
    FILE *file = fopen(path, "w");
    if (file == NULL) return 0;
    fprintf(file, "There are %ld numbers \n", n);
    for (int i = 0;i < n;i++)
        fprintf(file, "%ld \n", arr[i]);
    fclose(file);
    return 1;
}
void handle(long n, int h, long ans[], int *num){
    char *arr = (char*)malloc((n+1) * sizeof(char));
    sievePrime(arr, n);
    *num = 0;
    for (long i = 0; i<= n;i++){
        if (arr[i] == 0 && heightOfNumber(i) == h) ans[(*num)++] = i;
    }
}
