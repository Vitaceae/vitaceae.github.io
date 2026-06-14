/**
 * description 1:
 *  n=1, move(a, c)
 *  n=2, move(a, b), move(a, c), move(b, c)
 *  n=3, iter1: c'=b, b'=c  [move(a, b'), move(a, c'), move(b', c')]
 *              [A, B, C]=[3, (1,2), 0]
 *       act:   [move(a, c)]
 *              [A, B, C]=[0, (1,2), 3]
 *       iter2: a'=b, b'=a [move(a', b'), move(a', c), move(b', c)]
 *              [A, B, C]=[0, 0, (1,2,3)]
 * 
 * description 2:
 *  assume disc count=n, start=a, auxilary=b, end=c
 *  n is odd: a >> c >> b >> a
 *  n is even: a >> b >> c >> a
 */

#include <iostream>
#include <limits>
#include <stdio.h>

using namespace std;

#define KEEP_TRACE                      1
#define MAX_HEIGHT                      8
#define SYS_WIN                         1

typedef struct slot_s {
	int data[MAX_HEIGHT];
	int top;
} slot_t;

static int disk_count;
static slot_t slot[3] = {{0}};
const char *disk_graph[MAX_HEIGHT + 1] = {
	"        ",
	"*       ",
	"**      ",
	"***     ",
	"****    ",
	"*****   ",
	"******  ",
	"******* ",
	"********",
};

void move(int n, char src, char dest, char aux);
static void show_slot_data(void);

int main(void) {
	cout << "Disk Count: ";
	cin >> disk_count;
	cin.get();

	if (disk_count > MAX_HEIGHT) {
		cout << "height limit: " << MAX_HEIGHT << endl;
		return -1;
	}

	// init: all disks piled up on slot A
	for (int i = 0; i < disk_count; i++) {
		slot[0].data[i] = disk_count - i;
	}
	slot[0].top = disk_count - 1;

	show_slot_data();
	cout << "press enter to continue..." << endl;
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
#if SYS_WIN == 1
	system("cls");
#else
	system("clear");
#endif

	move(disk_count, 0, 2, 1);

	cout << "press enter to exit" << endl;
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');

	return 0;
}

static void show_slot_data(void) {
	char buf[MAX_HEIGHT * 3 + 7] = {0};

	for (int i = 0; i < disk_count; i++) {
		int index = disk_count - i - 1;
		sprintf(
			buf,
			"%s  %s  %s\n",
			disk_graph[slot[0].data[index]],
			disk_graph[slot[1].data[index]],
			disk_graph[slot[2].data[index]]);
		cout << buf;
	}
}

static void move_slot_data(char src, char dest) {
	// increase index if not empty
	if (slot[dest].data[slot[dest].top]) {
		slot[dest].top++;
	}
	slot[dest].data[slot[dest].top] = slot[src].data[slot[src].top];
	slot[src].data[slot[src].top] = 0;
	// decrease index if not bottom
	if (slot[src].top) {
		slot[src].top--;
	}

	show_slot_data();

	if (slot[2].top == disk_count - 1) {
		cout << "done!" << endl;
	} else {
        cout << "press enter to continue..." << endl;
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
#if KEEP_TRACE == 0
#if SYS_WIN == 1
        system("clr");
#else
        system("clear");
#endif
#endif
	}
}

void move(int n, char src, char dest, char aux) {
	static int step = 0;
	unsigned char ch = 'A';

	if (n == 0) {
        return;
    }

	move(n - 1, src, aux, dest);
	cout << ++step << ") " << (char)(ch + src) << " -> " << (char)(ch + dest) << endl;
	move_slot_data(src, dest);
	move(n - 1, aux, dest, src);
}
