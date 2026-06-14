/**
 *  name: johnson-trotter-algo-variant-1.c
 *  desctiption:
 *
 *        [ 0]  [ 1]  [ 2]
 *     [ 3]  [ 4]  [ 5]  [ 6]
 *  [ 7]  [ 8]  [ 9]  [10]  [11]
 *     [12]  [13]  [14]  [15]
 *        [16]  [17]  [18]
 *
 *      a) sum of each row is a constant
 *      b) sum of each diagonal line is a constant
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUCCESS_COUNT               0
#define ENABLE_TRACE                    0

static int arr[21];
static int val_loc[21];
static int success_count = 0;
static int test_count = 0;

void fill_data(int index);

int check(int index, int val)
{
    test_count++;

    for (int i = 0 ; i < index ; i++) {
        if (arr[i] == val) {
            return 0;
        }
    }

    //sum of  diagonal lines
    switch (index) {
    case 7:
        return arr[0] + arr[3] + val == 38;
    case 11:
        return arr[2] + arr[6] + val == 38;
    case 12:
        return arr[1] + arr[4] + arr[8] + val == 38;
    case 15:
        return arr[1] + arr[5] + arr[10] + val;
    case 16:
        return arr[7] + arr[12] + val == 38 && arr[2] + arr[5] + arr[9] + arr[13] + val == 38;
    case 17:
        return arr[3] + arr[8] + arr[13] + val == 38 && arr[6] + arr[10] + arr[14] + val == 38;
    case 18:
        return arr[0] + arr[4] + arr[9] + arr[14] + val == 38 && arr[11] + arr[15] + val == 38;
    }

    return 1;
}

static void show(void)
{
    printf("--------------------------------\n"
           "success(%d), test count: %d\n"
           "    %2d  %2d  %2d\n"
           "  %2d  %2d  %2d  %2d\n"
           "%2d  %2d  %2d  %2d  %2d\n"
           "  %2d  %2d  %2d  %2d\n"
           "    %2d  %2d  %2d\n"
           "--------------------------------\n",
           success_count, test_count,
           arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7],
           arr[8], arr[9], arr[10], arr[11], arr[12], arr[13], arr[14], arr[15],
           arr[16], arr[17], arr[18]);
}

static int is_exit(void)
{
    if (MAX_SUCCESS_COUNT && success_count >= MAX_SUCCESS_COUNT) {
        return 1;
    }

    return 0;
}

void trace(int index)
{
    char buf[62] = { 0 };
    int offset = 0;
    static int last_val = 0;

#if ENABLE_TRACE == 0
    return;
#endif

    if (is_exit()) {
        return;
    }

    if (last_val == arr[index - 1]) {
        return;
    } else {
        last_val = arr[index - 1];
    }

    for (int j = 0; j < index; j++) {
        offset += sprintf(buf + offset, "%2d ", arr[j]);
    }
    sprintf(buf + offset, "\n");
    printf("%s", buf);
}

static void check_process(int index, int val)
{
    if (val_loc[val] < index) {
        return;
    }

    if (check(index, val)) {
        val_loc[arr[index]] = 20;
        arr[index] = val;
        val_loc[val] = index;
        trace(index);
        fill_data(index + 1);
    }
}

void fill_data(int index)
{
    int val;

    if (index == 19) {
        success_count++;
        show();
        return;
    }

    if (is_exit()) {
        return;
    }

    switch (index) {
    case 2:
        val = 38 - arr[0] - arr[1];
        if (val > 0) check_process(index, val);
        break;
    case 6:
        val = 38 - arr[3] - arr[4] - arr[5];
        if (val > 0) check_process(index, val);
        break;
    case 11:
        val = 38 - arr[7] - arr[8] - arr[9] - arr[10];
        if (val > 0) check_process(index, val);
        break;
    case 15:
        val = 38 - arr[12] - arr[13] - arr[14];
        if (val > 0) check_process(index, val);
        break;
    case 18:
        val = 38 - arr[16] - arr[17];
        if (val > 0) check_process(index, val);
        break;
    default:
        for (int i = 1 ; i <= 19 ; i++) {
            check_process(index, i);
        }
        break;
    }
}

int main(void)
{
    for (int i = 0; i < 20; i++) {
        arr[i] = 0;
        val_loc[i] = 20;
    }

    fill_data(0);
    printf("success count: %d\n", success_count);
    system("pause");

    return 0;
}
