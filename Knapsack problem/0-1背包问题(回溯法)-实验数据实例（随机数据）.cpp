#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_ITEMS 50
#define NUM_TESTS 1

typedef struct {
    int weights;
    int values;
} Item;

// ���������������
void generateRandomTestData(Item items[], int *capacity){
    for (int i = 0; i < NUM_ITEMS; i++) {
        items[i].weights = rand() % 10 + 1;  // ����1��10֮����������Ϊ����
        items[i].values = rand() % 10 + 1;   // ����1��10֮����������Ϊ��ֵ
    }
    *capacity = rand() % 20 + 10;  // ����10��30֮����������Ϊ��������
}

// ���ݷ����
void knapsack(Item items[], int capacity, int index, int current_weight, int current_value, int *max_value){
    if (index == NUM_ITEMS) { //����Ƿ�������Ʒ���Ѿ�����
        if (current_value > *max_value) {  //��ǰ���ܼ�ֵ�����Ѽ�¼����ֵ
            *max_value = current_value;
        }
        return;
    }
    if (current_weight + items[index].weights <= capacity) {//��������ǰ��Ʒ������� �������Ƿ�ᳬ������
        current_weight += items[index].weights;
        current_value += items[index].values; //����ǰ��Ʒ�������ͼ�ֵ����                 �ݹ���� knapsack
        knapsack(items, capacity, index + 1, current_weight, current_value, max_value); //������һ����Ʒ
        current_weight -= items[index].weights;
        current_value -= items[index].values; //���� �Ƴ���ǰ��Ʒ�������ͼ�ֵ
    }
    knapsack(items, capacity, index + 1, current_weight, current_value, max_value);
}    //�ݹ���� knapsack �����Կ��ǲ����뵱ǰ��Ʒ�����

int main() {
    srand(time(NULL));  //��ʼ�������������
    Item items[NUM_ITEMS+1];
    int capacity;

    for (int i = 0; i < NUM_TESTS; i++) { //ѭ�����в���
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
