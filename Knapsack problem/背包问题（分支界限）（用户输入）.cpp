#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX_ITEMS 30000
#define NUM_TESTS 1

// 物品结构体
typedef struct {
    int weight;
    int value;
} Item;

// 定义一个节点用于搜索树
typedef struct {
    int level; // 当前所处理的物品索引
    int value; 
    int weight; 
} Node;

// 比较函数
int compare(const void *a, const void *b) {
    double ratioA = ((Item *)a)->value / (double)((Item *)a)->weight;
    double ratioB = ((Item *)b)->value / (double)((Item *)b)->weight;
    if (ratioA > ratioB) return -1;
    else if (ratioA < ratioB) return 1;
    else return 0;
}

// 计算上界
bool bound(Node node, Item items[], int capacity, int maxProfit) {
    if (node.weight >= capacity) return false;
    int profitBound = node.value;
    int totalWeight = node.weight;
    int k = node.level + 1;

    while (k < MAX_ITEMS && totalWeight + items[k].weight <= capacity) {
        totalWeight += items[k].weight;
        profitBound += items[k].value;
        k++;
    }

    if (k < MAX_ITEMS) {
        profitBound += (capacity - totalWeight) * items[k].value / (double)items[k].weight;
    }

    return profitBound > maxProfit;
}

// 分支限界法求解0-1背包问题
int knapsack(Item items[], int capacity, int num_items) {
    qsort(items, num_items, sizeof(Item), compare);

    Node queue[MAX_ITEMS+1];
    Node current, next;
    int front = -1, rear = -1;
    int maxProfit = 0;

    next.level = -1;
    next.value = next.weight = 0;
    queue[++rear] = next;

    while (front != rear) {
        current = queue[++front];

        if (current.level == num_items - 1) continue;
        
        next.level = current.level + 1;
        next.weight = current.weight + items[next.level].weight;
        next.value = current.value + items[next.level].value;

        if (next.weight <= capacity && next.value > maxProfit) {
            maxProfit = next.value;
        }

        if (bound(next, items, capacity, maxProfit)) {
            queue[++rear] = next;
        }

        next.weight = current.weight;
        next.value = current.value;

        if (bound(next, items, capacity, maxProfit)) {
            queue[++rear] = next;
        }
    }

    return maxProfit;
}

void getUserInput(Item items[], int *capacity, int *num_items) {
    printf("Enter the number of items (up to %d): ", MAX_ITEMS);
    scanf("%d", num_items);

    printf("Enter the weight and value for each item:\n");
    for (int i = 0; i < *num_items; i++) {
        printf("Item %d weight: ", i + 1);
        scanf("%d", &items[i].weight);
        printf("Item %d value: ", i + 1);
        scanf("%d", &items[i].value);
    }

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", capacity);
}

int main() {
    srand(time(NULL));
    Item items[MAX_ITEMS];
    int capacity, num_items;

    for (int test = 0; test < NUM_TESTS; test++) {
        getUserInput(items, &capacity, &num_items);
        int maxProfit = knapsack(items, capacity, num_items);
        
        printf("\nItems:\n");
        for (int i = 0; i < num_items; i++) {
            printf("Item %d: Value: %d, Weight: %d\n", i + 1, items[i].value, items[i].weight);
        }
        printf("\n");
        printf("Capacity: %d, Max Profit: %d\n",  capacity, maxProfit);
    }

    return 0;
}

