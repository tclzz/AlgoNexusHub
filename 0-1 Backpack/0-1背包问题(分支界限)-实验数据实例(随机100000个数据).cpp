#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define NUM_ITEMS 100000
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
    double ratioA = ((Item *)a)->value / (double)((Item *)a)->weight;//将void指针a强制转换为 Item类型的指针	                                                                
    double ratioB = ((Item *)b)->value / (double)((Item *)b)->weight;//然后访问该物品的value weight属性
    if (ratioA > ratioB) return -1;
    else if (ratioA < ratioB) return 1;
    else return 0;
}

// 计算上界
bool bound(Node node, Item items[], int capacity, int maxProfit) {
    if (node.weight >= capacity) return false; // 超过容量，不加入搜索队列
    int profitBound = node.value; //初始化 profitBound 为当前节点的总价值
    int totalWeight = node.weight; //totalWeight 为当前节点的总重量
    int k = node.level + 1;  //k表示下一个要考虑的物品的索引

    while (k < NUM_ITEMS && totalWeight + items[k].weight <= capacity) {
        totalWeight += items[k].weight;      //直到加入物品使得总重量超过背包容量或者所有物品都已考虑完毕
        profitBound += items[k].value;
        k++;
    }

    if (k < NUM_ITEMS) {  //循环结束时还有未处理的物品
        profitBound += (capacity - totalWeight) * items[k].value / (double)items[k].weight;
    }    //估算可能的最大价值

    return profitBound > maxProfit;  //比较计算得到的潜在最大利润是否大于当前已知的最大利润 
}

// 分支限界法求解0-1背包问题
int knapsack(Item items[], int capacity) {
    qsort(items, NUM_ITEMS, sizeof(Item), compare); // 根据单位重量价值排序

    Node queue[NUM_ITEMS+1]; // 用于存放搜索树节点的队列
    Node current, next;
    int front = -1, rear = -1; //front 和 rear 用于队列的头尾指针
    int maxProfit = 0;

    next.level = -1; //初始化 
    next.value = next.weight = 0;
    queue[++rear] = next;

    while (front != rear) {
        current = queue[++front]; //处理队列中的所有节 

        if (current.level == NUM_ITEMS - 1) continue; // 已经到达叶子结点 跳过当前迭代
        
        next.level = current.level + 1; //生成下一个节点 
        next.weight = current.weight + items[next.level].weight;
        next.value = current.value + items[next.level].value;

        if (next.weight <= capacity && next.value > maxProfit) {
            maxProfit = next.value;  //下一个节点的重量不超过背包容量且价值大于当前最大利润
        }

        if (bound(next, items, capacity, maxProfit)) {//检查不加入当前物品的情况是否值得探索 
            queue[++rear] = next; // 加入左子树
        }

        next.weight = current.weight; //重置 next节点
        next.value = current.value;   //为不选择当前物品的况做准备

        if (bound(next, items, capacity, maxProfit)) {
            queue[++rear] = next; // 加入右子树
        }
    }

    return maxProfit;
}

void generateRandomTestData(Item items[], int *capacity) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        items[i].weight = rand() % 100 + 1;  // 生成1到100的随机重量
        items[i].value = rand() % 100 + 1;   // 生成1到100的随机价值
    }
    *capacity = rand() % 100 + 50;  // 生成50到150的随机容量
}

int main() {
    srand(time(NULL));  //初始化随机数
    Item items[NUM_ITEMS];
    int capacity;

    for (int test = 0; test < NUM_TESTS; test++) { //使用循环来执行多次测试
        generateRandomTestData(items, &capacity);
        int maxProfit = knapsack(items, capacity);
        
        for (int i = 0; i < NUM_ITEMS; i++) {
            printf("Item %d: Value: %d, Weight: %d\n", i + 1, items[i].value, items[i].weight);
        }
        printf("\n");
        printf(" Capacity: %d, Max Profit: %d\n",  capacity, maxProfit);
        
    }
    return 0;
}
