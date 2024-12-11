#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define NUM_ITEMS 100000
#define NUM_TESTS 1

// ��Ʒ�ṹ��
typedef struct {
    int weight;
    int value;
} Item;

// ����һ���ڵ�����������
typedef struct {
    int level; // ��ǰ���������Ʒ����
    int value; 
    int weight; 
} Node;

// �ȽϺ���
int compare(const void *a, const void *b) {
    double ratioA = ((Item *)a)->value / (double)((Item *)a)->weight;//��voidָ��aǿ��ת��Ϊ Item���͵�ָ��	                                                                
    double ratioB = ((Item *)b)->value / (double)((Item *)b)->weight;//Ȼ����ʸ���Ʒ��value weight����
    if (ratioA > ratioB) return -1;
    else if (ratioA < ratioB) return 1;
    else return 0;
}

// �����Ͻ�
bool bound(Node node, Item items[], int capacity, int maxProfit) {
    if (node.weight >= capacity) return false; // ������������������������
    int profitBound = node.value; //��ʼ�� profitBound Ϊ��ǰ�ڵ���ܼ�ֵ
    int totalWeight = node.weight; //totalWeight Ϊ��ǰ�ڵ��������
    int k = node.level + 1;  //k��ʾ��һ��Ҫ���ǵ���Ʒ������

    while (k < NUM_ITEMS && totalWeight + items[k].weight <= capacity) {
        totalWeight += items[k].weight;      //ֱ��������Ʒʹ������������������������������Ʒ���ѿ������
        profitBound += items[k].value;
        k++;
    }

    if (k < NUM_ITEMS) {  //ѭ������ʱ����δ�������Ʒ
        profitBound += (capacity - totalWeight) * items[k].value / (double)items[k].weight;
    }    //������ܵ�����ֵ

    return profitBound > maxProfit;  //�Ƚϼ���õ���Ǳ����������Ƿ���ڵ�ǰ��֪��������� 
}

// ��֧�޽編���0-1��������
int knapsack(Item items[], int capacity) {
    qsort(items, NUM_ITEMS, sizeof(Item), compare); // ���ݵ�λ������ֵ����

    Node queue[NUM_ITEMS+1]; // ���ڴ���������ڵ�Ķ���
    Node current, next;
    int front = -1, rear = -1; //front �� rear ���ڶ��е�ͷβָ��
    int maxProfit = 0;

    next.level = -1; //��ʼ�� 
    next.value = next.weight = 0;
    queue[++rear] = next;

    while (front != rear) {
        current = queue[++front]; //��������е����н� 

        if (current.level == NUM_ITEMS - 1) continue; // �Ѿ�����Ҷ�ӽ�� ������ǰ����
        
        next.level = current.level + 1; //������һ���ڵ� 
        next.weight = current.weight + items[next.level].weight;
        next.value = current.value + items[next.level].value;

        if (next.weight <= capacity && next.value > maxProfit) {
            maxProfit = next.value;  //��һ���ڵ���������������������Ҽ�ֵ���ڵ�ǰ�������
        }

        if (bound(next, items, capacity, maxProfit)) {//��鲻���뵱ǰ��Ʒ������Ƿ�ֵ��̽�� 
            queue[++rear] = next; // ����������
        }

        next.weight = current.weight; //���� next�ڵ�
        next.value = current.value;   //Ϊ��ѡ��ǰ��Ʒ�Ŀ���׼��

        if (bound(next, items, capacity, maxProfit)) {
            queue[++rear] = next; // ����������
        }
    }

    return maxProfit;
}

void generateRandomTestData(Item items[], int *capacity) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        items[i].weight = rand() % 100 + 1;  // ����1��100���������
        items[i].value = rand() % 100 + 1;   // ����1��100�������ֵ
    }
    *capacity = rand() % 100 + 50;  // ����50��150���������
}

int main() {
    srand(time(NULL));  //��ʼ�������
    Item items[NUM_ITEMS];
    int capacity;

    for (int test = 0; test < NUM_TESTS; test++) { //ʹ��ѭ����ִ�ж�β���
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
