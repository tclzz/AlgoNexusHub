#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
# include <malloc.h>
#include<time.h>
using namespace std;

int selectmid(int a[], int p, int r) {
	int* b = new int[r - p + 1];
	int i, min, j, c, d;
	for (i = p;i <= r;i++) {
		b[i - p] = a[i];
	}
	for (i = 0;i < r - p;i++) {
		min = b[i];
		for (j = i;j <= r - p;j++) {
			if (b[j] <= min) {
				min = b[j];
				c = j;
			}
		}
		if (i != c) {
			d = b[c];
			b[c] = b[i];
			b[i] = d;
		}
	}
	for (i = p;i <= r;i++) {
		if (a[i] == b[(r - p + 1) / 2]) {
			return i;
		}
	}
	delete[]b;
	return 0;
}

int Partition(int a[], int p, int r, int x) {
	int i, j, b;
	i = p - 1;
	j = r + 1;
	while (1) {
		while (a[++i] < x && i < r)  ;
		while (a[--j] > x && j > p)  ;
		if (i >= j)
			break;
		b = a[i];
		a[i] = a[j];
		a[j] = b;
		
	}

	return j;
}

int Select(int a[], int p, int r, int k) {
	int i, j;
	int min, b, c;
	
	if (r - p < 5) {
		for (i = p;i < r;i++) {
			min = a[i];
			for (j = i;j <= r;j++) {
				if (a[j] <= min) {
					min = a[j];
					b = j;
				}
			}
			if (i != b) {
				c = a[b];
				a[b] = a[i];
				a[i] = c;
			}
		}
		return a[p + k - 1];
	}
	for (i = 0;i <= (r - p - 4) / 5;i++) {
		int mid;
		mid = selectmid(a, p + i * 5, p + i * 5 + 4);
		int c;
		c = a[mid];
		a[mid] = a[p + i];
		a[p + i] = c;
	}
		int x;
		x = Select(a, p, p + (r - p - 4) / 5, (r - p - 4) / 10 + 1);
		i = Partition(a, p, r, x);
		j = i - p + 1;
		
		if (k <= j)
			return Select(a, p, i, k);
		else
			return Select(a, i + 1, r, k - j);
	
}

int main() {
	
	int n, k, count;
	int i;
	
	printf("输入元素的个数：\n");
	cin >> n;
	int* a = new int[n];
	printf("\n输入元素：\n");
	for (i = 0;i < n;i++) {
		cin >> a[i];
	}
	printf("\n输入整数k：\n");
	cin >> k;
	double startTime1 = clock();
	count = Select(a, 0, n - 1, k);
	
	printf("\n第k小的数是：%d\n", count);
	double endTime1 = clock();
	std::cout << "The run time is: " << (double)(endTime1 - startTime1) / CLOCKS_PER_SEC << "s" << std::endl;
	
	delete[]a;
	return 0;
}

