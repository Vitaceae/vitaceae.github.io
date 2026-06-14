#include <iostream>
#include <stdio.h>
#include <string.h>

#include "singly_linked_list.h"
#include "sys_util.h"
#include "time.h"

#ifndef NULL
#define NULL                            0
#endif

#define CONFIG_PERF_TR

#ifdef CONFIG_PERF_TR
#define PERF_TR(str_tr, str_cpt)        perf_tr_add(str_tr, str_cpt, str_tr)
#else
#define PERF_TR(str_tr, str_cpt)
#endif //CONFIG_PERF_TR


typedef struct checkpoint_object_s {
    uint32_t hash;
    const char *name;
    uint32_t tid;
    const char *tname;
    uint32_t timestamp;
    slist_node_t node;
} cpt_obj_t;

typedef struct trace_object_s {
    uint32_t hash;
    const char *name;
    slist_head_t cpt_list;
    slist_node_t node;
} tr_obj_t;

static slist_head_t tr_list = { 0 };


static uint32_t hash_djb2(const char *name)
{
    uint32_t k = 5381;
    int32_t ch;

    while (ch = *name++) {
        //k * 33 + ch
        k = ((k << 5) + k) + ch;
    }

    return k;
}

static slist_head_t *get_tr_list(void)
{
    return &tr_list;
}

static void perf_tr_add(const char *str_tr, const char *str_cpt, const char *str_task)
{
    tr_obj_t *obj_tr = NULL;
    cpt_obj_t *obj_cpt = NULL;
    time_t cur_time = time(0);
    uint32_t hash = 0;
    int is_found = 0;

    if (str_tr == NULL || str_cpt == NULL || str_task == NULL) {
        return;
    }

    hash = hash_djb2(str_tr);
    is_found = 0;

    slist_for_each_entry(obj_tr, get_tr_list()->first, tr_obj_t, node) {
        if (hash == obj_tr->hash) {
            is_found = 1;
            break;
        }
    }

    if (is_found == 0) {
        obj_tr = (tr_obj_t *)malloc(sizeof(tr_obj_t));
        memset(obj_tr, 0, sizeof(tr_obj_t));
        obj_tr->hash = hash_djb2(str_tr);
        obj_tr->name = str_tr;
        slist_add(&obj_tr->node, get_tr_list());
    }

    obj_cpt = (cpt_obj_t *)malloc(sizeof(cpt_obj_t));
    memset(obj_cpt, 0, sizeof(cpt_obj_t));
    obj_cpt->hash = hash_djb2(str_cpt);
    obj_cpt->name = str_cpt;
    obj_cpt->tid = hash_djb2(str_task);
    obj_cpt->tname = str_task;
    obj_cpt->timestamp = cur_time;

    slist_add(&obj_cpt->node, &obj_tr->cpt_list);
}

void per_tr_show_result(void)
{
    tr_obj_t *obj_tr = NULL;
    cpt_obj_t *obj_cpt = NULL;
slist_head_t *head;
    slist_for_each_entry(obj_tr, get_tr_list()->first, tr_obj_t, node) {
        head = &obj_tr->cpt_list;
        slist_for_each_entry(obj_cpt, head->first, cpt_obj_t, node) {
            printf("%u\n", (uint32_t)&obj_cpt->node);
//            printf("%s,%s,%s,%u\n", obj_tr->name, obj_cpt->name, obj_cpt->tname, obj_cpt->timestamp);
//            printf("%s\n", obj_tr->name);
        }
            printf("-------------\n");
        head = (slist_head_t *)slist_reverse_except_head((slist_node_t *)&obj_tr->cpt_list);
        slist_for_each_entry(obj_cpt, head->first, cpt_obj_t, node) {
            printf("%u\n", (uint32_t)&obj_cpt->node);
//            printf("%s,%s,%s,%u\n", obj_tr->name, obj_cpt->name, obj_cpt->tname, obj_cpt->timestamp);
//            printf("%s\n", obj_tr->name);
        }
            printf("-------------end\n");
    }
}

void task_1(void)
{
    PERF_TR("trace 1", "checkpoint 1");
}

void task_2(void)
{
    PERF_TR("trace 2", "checkpoint 1");
}

void task_3(void)
{
    PERF_TR("trace 1", "checkpoint 2");
}

void task_4(void)
{
    PERF_TR("trace 2", "checkpoint 2");
}

#define time_after(a,b)		((int32_t)(b) - (int32_t)(a) < 0)

int main(void)
{
    printf("hash=%u, %u", hash_djb2("st:idle"), hash_djb2("st:offline"));
    system("pause");
    return 0;
    task_1();
    task_2();
    task_3();
    task_4();

    per_tr_show_result();

    system("pause");

    return 0;
}

