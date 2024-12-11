#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <malloc.h>

void Swap(int &a, int &b) {
	int i;
	i = a;
	a = b;
	b = i;
}

int partition(int s[], int f[], int a[], int p, int r) {
	int i = p, j = r + 1;
	int x = f[p];
	while (1) {
		while (f[++i] < x && i < r)  ;
		while (f[--j] > x)  ;
		if (i >= j)
			break;
		Swap(s[i], s[j]);
		Swap(f[i], f[j]);
		Swap(a[i], a[j]);
	}
	Swap(s[p], s[j]);
	Swap(f[p], f[j]);
	Swap(a[p], a[j]);
	return j;

}

void sort(int s[], int f[], int a[],int p, int r) {
	if (p < r) {
		int q = partition(s, f, a, p, r);
		sort(s, f, a, p, q - 1);
		sort(s, f, a, q + 1, r);
	}
}

void selector(int n, int s[], int f[], bool A[]) {
	A[0] = 1;
	int j = 0;
	for (int i = 1;i < n;i++) {
		if (s[i] >= f[j]) {
			A[i] = 1;
			j = i;
		}
		else
			A[i] = 0;
	}
}

int main() {
	int n;
	printf("请输入活动个数：");
	scanf("%d", &n);
	int* s = (int*)malloc(sizeof(int) * n);
	int* f = (int*)malloc(sizeof(int) * n);
	int* a = (int*)malloc(sizeof(int) * n);
	bool* A = (bool*)malloc(sizeof(bool) * n);
	printf("请输入各个活动的起始时间与结束时间：");
	for (int i = 0;i < n; i++) {
		scanf("%d %d", &s[i], &f[i]);
		a[i] = i;
	}
	
	sort(s, f, a, 0, n - 1);
	
	selector(n, s, f, A);
	printf("最大的相容活动集合为：");

	for (int i = 0;i < n;i++) {
		if (A[i]) {
			printf("%d ", a[i]+1);
		}
	}


	return 0;
}
