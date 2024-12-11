#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LENGTH 30000

int max(int a, int b) {
return (a > b) ? a : b;
}

int longestCommonSequence(char *str1, char *str2) {
int m = strlen(str1);
int n = strlen(str2);
int *prev = (int *)malloc((n + 1) * sizeof(int));
int *curr = (int *)malloc((n + 1) * sizeof(int));

if (!prev || !curr) {
    free(prev);
    free(curr);
    return -1; 
}

for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
        if (i == 0 || j == 0) {
            curr[j] = 0;
        } else if (str1[i - 1] == str2[j - 1]) {
            curr[j] = prev[j - 1] + 1;
        } else {
            curr[j] = max(prev[j], curr[j - 1]);
        }
    }
    int *temp = prev;
    prev = curr;
    curr = temp;
}

int result = prev[n];
free(prev);
free(curr);
return result;
}

void generate_random_string(int length, char *str) {
static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
int charset_length = strlen(charset);

for (int i = 0; i < length; i++) {
    str[i] = charset[rand() % charset_length];
}
str[length] = '\0';
}

int main() {
char *str1 = (char *)malloc(MAX_LENGTH + 1);
char *str2 = (char *)malloc(MAX_LENGTH + 1);

if (!str1 || !str2) {
    printf("Memory allocation failed.\n");
    free(str1);
    free(str2);
    return -1;
}

srand((unsigned)time(NULL));

generate_random_string(MAX_LENGTH, str1);
generate_random_string(MAX_LENGTH, str2);

printf("String 1: %s\n", str1);
printf("String 2: %s\n", str2);

int result = longestCommonSequence(str1, str2);
if (result != -1) {
    printf("Length of Longest Common Subsequence: %d\n", result);
} else {
    printf("Memory allocation failed.\n");
}

free(str1);
free(str2);
return 0;
}
