/*
 * linkedlist.c: Dynamic array implementation
 * Copyright (C) 2011 Daniel Cheah
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */ 

/*
 * A basic doublely linked list implementation. List is terminated with 
 * a NULL pointer.
 *
 * To compile on my mac:
 * gcc -DUSEMAIN -Werror -std=c99 -pedantic -o linkedlist linkedlist.c (works on Ubuntu)
 * clang -DUSEMAIN linkedlist.c
 */
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int data_t;

typedef struct linkedlist_node 
{
    data_t value;
    struct linkedlist_node* next;
    struct linkedlist_node* prev;
} linkedlist_node_t;

typedef struct linkedlist
{
    unsigned int node_count;
    linkedlist_node_t* head;
    linkedlist_node_t* tail;
} linkedlist_t;

/**
 * Create a new linked list instance.
 */
linkedlist_t* new_linkedlist(void)
{
    // Allocate memory for the linked list
    linkedlist_t* newlist = (linkedlist_t*)malloc(sizeof(linkedlist_t));

    // No nodes in list currently
    newlist->node_count = 0;
    newlist->head = NULL;
    newlist->tail = NULL;

    return newlist;
}

static linkedlist_node_t* new_node(data_t newvalue)
{
    linkedlist_node_t* newnode = 
        (linkedlist_node_t*)malloc(sizeof(linkedlist_node_t));

    newnode->value = newvalue;
    newnode->prev = NULL;
    newnode->next = NULL;

    return newnode;
}

/**
 * Insert a new node at the head of the linked list
 */
void insert_at_head(linkedlist_t* list, data_t newvalue)
{
    // First create the new node
    linkedlist_node_t* node = new_node(newvalue);

    // This is an invariant. When inserting at head,
    // prev is always NULL.
    node->prev = NULL;

    // Point to what head currently points at
    node->next = list->head;

    // If the tail points to nothing, then we want
    // it to point to this new node. i.e. the list
    // is empty.
    if (list->tail == NULL) {
        list->tail = node;
    } 
 
    // Head pointer points to the new head
    list->head = node;

    list->node_count++;
}

/**
 * Insert a new node at the tail of the linked list
 */
void insert_at_tail(linkedlist_t* list, data_t newvalue)
{
    // First create the new node
    linkedlist_node_t* node = new_node(newvalue);

    // Invariant. When inserting at tail, next is always NULL
    node->next = NULL;

    // Point back to the node that is currently the tail
    node->prev = list->tail;

    // If the head points to nothing, then we want to
    // point to this node. i.e. the list is empty.
    if (list->head == NULL) {
        list->head = node;
    }

    // Current tail node needs to point to new node
    if (list->tail != NULL) {
        list->tail->next = node;
    }

    // Tail pointer points to the new tail
    list->tail = node;

    list->node_count++;
}

linkedlist_node_t* get_node_at_position(linkedlist_t* list, unsigned int position)
{
    // Check that we have enough nodes
    if (position > (list->node_count - 1)) {
        return NULL;
    } 

    linkedlist_node_t* current;
    current = list->head;
    for (int i = 0; i < position; i++) {
        current = current->next;
    }

    return current;
}

void delete_at_head(void);
void delete_at_tail(void);

void insert_after_value();
void insert_before_value();

/**
 * Deallocates all memory associated with this
 * linked list.
 */
void delete_linkedlist(linkedlist_t* list)
{
    linkedlist_node_t* current;
    current = list->head;
    while (current != NULL) {
        // First point to the next one. Need
        // to do this first because in the next step
        // we are deleting the memory associated with 
        // the node.
        linkedlist_node_t* next = current->next;

        // Now delete it
        free(current);

        // Then make current point to the next one.
        current = next;
    }

    // Now free up the parent linkedlist struct
    free(list);
}

/**
 * Print out the linked list
 */
void print_linkedlist(linkedlist_t* list)
{
    linkedlist_node_t* current;
    current = list->head;
    while (current != NULL) {
        printf("%u\n", current->value);
        current = current->next;
    }
}

void print_node(linkedlist_node_t* node)
{
    if (node != NULL) {
        printf("Node Value: %d\n", node->value);

        if (node->prev != NULL) {
            printf("Prev Node Value:%d\n", node->prev->value);
        } else {
            printf("NULL Prev Node\n");
        }

        if (node->next != NULL) {
            printf("Next Node Value:%d\n", node->next->value);
        } else {
            printf("NULL Next Node\n");
        }

        printf("----------------\n");
    } else {
        printf("NULL Node\n");
    }
}

#ifdef USEMAIN
void test1(void)
{
    linkedlist_t* list = new_linkedlist();

    for (int i = 0; i < 5; i++) {
        insert_at_head(list, i);
    }

    print_linkedlist(list);

    delete_linkedlist(list);
}

void test2(void)
{
    linkedlist_t* list = new_linkedlist();

    for (int i = 0; i < 5; i++) {
        insert_at_tail(list, i);
    }

    print_linkedlist(list);

    delete_linkedlist(list);
}

void test3(void)
{
    linkedlist_t* list = new_linkedlist();

    linkedlist_node_t* node = get_node_at_position(list, 0);
    print_node(node);

    for (int i = 0; i < 5; i++) {
        insert_at_tail(list, i);
        node = get_node_at_position(list, i);
        print_node(node);
    }

    for (int i = 0; i < 5; i++) {
        node = get_node_at_position(list, i);
        print_node(node);
    }

    delete_linkedlist(list);
}

int main(void)
{
    test1();

    test2();

    test3();

    return 0;
}
#endif // USEMAIN


// vim: sts=4 sw=4 ts=4 et ft=c
