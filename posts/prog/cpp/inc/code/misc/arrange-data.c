#include <iostream>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
    void *id;
    void *grade;
    struct node_s *next;
} node_t;

node_t *create_node(void *id, void *grade)
{
    node_t *node;
    node = (node_t *)malloc(sizeof(node_t));
    node->id = id;
    node->grade = grade;
    node->next = NULL;

    return node;
}

int main(void)
{
    int data_count = 1, i = 1, doloop = 0, loop_count = 0, edge_test = 0;
    int *id;
    float *grade;
    node_t *node, *node_smallest, *node_pre;
    FILE *fp = fopen("arrange-data.txt", "r");

    id = (int *)malloc(sizeof(int));
    fscanf(fp, "%d", id);

    grade = (float *)malloc(sizeof(float));
    fscanf(fp, "%f", grade);

    node = create_node(id, grade);

    while (!feof(fp)) {
        id = (int *)malloc(sizeof(int));
        fscanf(fp, "%d", id);

        grade = (float *)malloc(sizeof(float));
        fscanf(fp, "%f", grade);

        node_t *new_node = create_node(id, grade);

        if (data_count == 1) {
            if (*(int *)new_node->id < *(int *)node->id) {
                new_node->next = node;
                node = new_node;
            } else {
                node->next = new_node;
            }
            node_smallest = node;
        } else {
            while(*(int *)new_node->id > *(int *)node->id) {
                loop_count++;
                if (loop_count == data_count) {
                    edge_test = 1;
                    break;
                }
                node_pre = node;
                node = node->next;
                doloop = 1;
            }

            if (doloop == 1) {
                if (edge_test == 0) {
                    new_node->next = node;
                    node_pre->next = new_node;
                } else {
                    node->next = new_node;
                }
                node = node_smallest;
            } else {
                new_node->next = node;
                node = new_node;
                node_smallest = node;
            }
        }

        doloop = 0;
        loop_count = 0;
        edge_test = 0;
        data_count++;
    }

    for (; i <= data_count; i++) {
        printf("ID   %3d  %d    ", i, *(int *)node->id);
        printf("Grade     %f\n", *(float *)node->grade);
        node = node->next;
    }

    return 0;
}
