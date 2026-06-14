/**
 * Direct Access Table using only arrays
 * drawbacks:
 *  1. keys SHOULD be non-negative integers
 *  2. waste of memory if the range of keys are wide compared to a small number of keys
 */

#include<stdio.h>
#include<stdlib.h>

struct hash_dictionary {
    int key;
    int value;
};

struct hash_dictionary *hash_array;
int capacity = 10;
int table_size = 0;


/* this function gives a unique hash code to the given key */
static int get_hash_code(int key)
{
    return (key % capacity);
}

/* to check if given input (i.e n) is prime or not */
static int is_prime(int x)
{
    int i;

    if (x == 1 || x == 0) {
        return 0;
    }

    /* the largest prime factor shall be smaller than the square root */
    for (i = 2; ((i * i) < x); i++) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}

/* it returns prime number just greater than array capacity */
int get_prime(int n)
{
    if (n % 2 == 0) {
        n++;
    }

    for (; !is_prime(n); n += 2);

    return n;
}

void init_hash_array()
{
    int i;
    size_t array_size;

    capacity = get_prime(capacity);
    array_size = capacity * sizeof(struct hash_dictionary);
    hash_array = (struct hash_dictionary *)malloc(array_size);

    memset((void *)hash_array, 0, array_size);
}

/* to insert a key in the hash table */
void hash_insert(int key)
{
    int index = get_hash_code(key);

    if (hash_array[index].value == 0) {
        /*  key not present, insert it  */
        hash_array[index].key = key;
        hash_array[index].value = 1;
        table_size++;
    } else if(hash_array[index].key == key) {
        /*  updating already existing key  */
        hash_array[index].value += 1;
    } else {
        /*  key cannot be insert as the index is already containing some other key  */
        printf("\n ELEMENT CANNOT BE INSERTED \n");
    }
}

/* to remove a key from hash table */
void remove_element(int key)
{
    int index = get_hash_code(key);

    if(hash_array[index].value == 0) {
        printf("\n This key does not exist \n");
    } else {
        hash_array[index].key = 0;
        hash_array[index].value = 0;
        table_size--;
    }
}

