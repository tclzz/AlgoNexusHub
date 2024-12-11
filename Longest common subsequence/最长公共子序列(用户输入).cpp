#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
void lcs();
int max(int a,int b);
 
int main()
{
    lcs();
    return 0;
}
int max(int a,int b)
{
    return a>b?a:b;
}
void lcs()
{
    int n,m,i,j;
    char *a,*b;
    printf("分别输入A和B的长度:");
    scanf("%d%d",&n,&m);
 
    a=(char *)malloc(n*sizeof(char));
    b=(char *)malloc(n*sizeof(char));
    int c[n+1][m+1];
 
    printf("输入A字符串：");
        scanf("%s",a);
    getchar();
    printf("输入B字符串：");
        scanf("%s",b);
    for(i=0;i<=n;i++)c[i][0]=0;
    for(j=0;j<=m;j++)c[0][j]=0;
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            if(a[i-1]==b[j-1])
                c[i][j]=c[i-1][j-1]+1;
            else
                c[i][j]=max(c[i][j-1],c[i-1][j]);
        }
    }
    printf("最长公共子序列为%d",c[n][m]);
}
