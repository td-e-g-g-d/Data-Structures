/***********************************************************
 * Author:          Kelsey Helms
 * Date Created:    July 11, 2016
 * Filename:        circularList.c
 *
 * Overview:
 * This program is an implementation of circular linked
 * list functions.
 *
 * Inputs and outputs are defined by functions.
 ************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "circularList.h"

// Double link
struct Link
{
    TYPE value;
    struct Link * next;
    struct Link * prev;
};

struct CircularList
{
    int size;
    struct Link* sentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinel's next and prev should point to the sentinel itself.
 */
static void init(struct CircularList* list)
{
    assert(list != 0);
    list->size = 0;
    list->sentinel = (struct Link *)malloc(sizeof(struct Link));
    assert(list->sentinel != 0);
    list->sentinel->next = list->sentinel;
    list->sentinel->prev = list->sentinel;
}

/**
 * Creates a link with the given value and NULL next and prev pointers.
 */
static struct Link* createLink(TYPE value)
{
    struct Link* newLink = (struct Link *)malloc(sizeof(struct Link));
    assert(newLink != 0);
    newLink->value = value;
    newLink->next = NULL;
    newLink->prev = NULL;
    return(newLink);
}

/**
 * Adds a new link with the given value after the given link and
 * increments the list's size.
 */
static void addLinkAfter(struct CircularList* list, struct Link* link, TYPE value)
{
    assert(list != 0);
    assert(link != 0);
    struct Link* newLink = createLink(value);
    newLink->next = link->next;
    newLink->prev = link;
    link->next->prev = newLink;
    link->next = newLink;
    list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct CircularList* list, struct Link* link)
{
    assert(list != 0);
    assert(link != 0);
    assert(list->size != 0);
    link->prev->next = link->next;
    link->next->prev = link->prev;
    free(link);
    list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct CircularList* circularListCreate()
{
    struct CircularList* list = malloc(sizeof(struct CircularList));
    init(list);
    return list;
}

/**
 * Deallocates every link in the list and frees the list pointer.
 */
void circularListDestroy(struct CircularList* list)
{
    assert(list != 0);
    assert(list->size != 0);
    while(list->size > 0)
        circularListRemoveFront(list);
    free(list->sentinel);
    free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void circularListAddFront(struct CircularList* list, TYPE value)
{
    assert(list != 0);
    addLinkAfter(list, list->sentinel, value);
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void circularListAddBack(struct CircularList* list, TYPE value)
{
    assert(list != 0);
    addLinkAfter(list, list->sentinel->prev, value);
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE circularListFront(struct CircularList* list)
{
    assert(list != 0);
    assert(list->size != 0);
    return(list->sentinel->next->value);
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE circularListBack(struct CircularList* list)
{
    assert(list != 0);
    assert(list->size != 0);
    return(list->sentinel->prev->value);
}

/**
 * Removes the link at the front of the deque.
 */
void circularListRemoveFront(struct CircularList* list)
{
    assert(list != 0);
    assert(list->size != 0);
    removeLink(list, list->sentinel->next);
}

/**
 * Removes the link at the back of the deque.
 */
void circularListRemoveBack(struct CircularList* list)
{
    assert(list != 0);
    assert(list->size != 0);
    removeLink(list, list->sentinel->prev);
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int circularListIsEmpty(struct CircularList* list)
{
    assert(list != 0);
    return(list->size == 0);
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void circularListPrint(struct CircularList* list)
{
    assert(list != 0);
    assert(list->size != 0);
    struct Link* current = list->sentinel->next;
    assert(current != 0);
    while(current != list->sentinel)
    {
        printf("%f\n", current->value);
        current = current->next;
    }
}

/**
 * Reverses the deque.
 */
void circularListReverse(struct CircularList* list)
{
    assert(list != 0);
    assert(list->size != 0);
    struct Link* current = list->sentinel->next;
    struct Link* temp;
    list->sentinel->prev = current;
    do
    {
        temp = current->next;
        if(temp->next == list->sentinel){
            list->sentinel->next = temp;
        }
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    } while(current != list->sentinel);
}
