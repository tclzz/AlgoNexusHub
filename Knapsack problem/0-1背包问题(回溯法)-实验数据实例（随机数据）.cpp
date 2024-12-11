#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_ITEMS 50
#define NUM_TESTS 1

typedef struct {
    int weights;
    int values;
} Item;

// 生成随机测试数据
void generateRandomTestData(Item items[], int *capacity){
    for (int i = 0; i < NUM_ITEMS; i++) {
        items[i].weights = rand() % 10 + 1;  // 生成1到10之间的随机数作为重量
        items[i].values = rand() % 10 + 1;   // 生成1到10之间的随机数作为价值
    }
    *capacity = rand() % 20 + 10;  // 生成10到30之间的随机数作为背包容量
}

// 回溯法求解
void knapsack(Item items[], int capacity, int index, int current_weight, int current_value, int *max_value){
    if (index == NUM_ITEMS) { //检查是否所有物品都已经考虑
        if (current_value > *max_value) {  //当前的总价值大于已记录最大价值
            *max_value = current_value;
        }
        return;
    }
    if (current_weight + items[index].weights <= capacity) {//检查如果当前物品被加入后 总重量是否会超过容量
        current_weight += items[index].weights;
        current_value += items[index].values; //将当前物品的重量和价值加上                 递归调用 knapsack
        knapsack(items, capacity, index + 1, current_weight, current_value, max_value); //考虑下一个物品
        current_weight -= items[index].weights;
        current_value -= items[index].values; //回溯 移除当前物品的重量和价值
    }
    knapsack(items, capacity, index + 1, current_weight, current_value, max_value);
}    //递归调用 knapsack 函数以考虑不加入当前物品的情况

int main() {
    srand(time(NULL));  //初始化随机数生成器
    Item items[NUM_ITEMS+1];
    int capacity;

    for (int i = 0; i < NUM_TESTS; i++) { //循环进行测试
        generateRandomTestData(items, &capacity);
        int max_value = 0;
        knapsack(items, capacity, 0, 0, 0, &max_value);
        
        for (int j = 0; j < NUM_ITEMS; j++) {
            printf("Item %d: Value: %d, Weight: %d\n", j + 1, items[j].values, items[j].weights);
        }
        printf("\n");
        printf("Test %d: Capacity: %d, Max Value: %d\n", i + 1, capacity, max_value);
    }
    return 0;
}
