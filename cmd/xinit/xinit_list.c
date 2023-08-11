
#include <stdlib.h>

#include "xinit_list.h"

// Get a node for a specific index
static XINIT_ITEM *index (XINIT_ITEM *l, int i)
{
    for (; i > 0; i--)
        l = l->next;

    return l;
}

// Check whether two strings are equal
static int streq (char *a, char *b)
{
    while (*a == *b && *a != '\0' && *b != '\0')
        a++, b++;

    if (*a == '\0' && *b == '\0') return 1; // equal

    return 0; // not equal
}

// memcpy
static void copy (char *dst, char *src)
{
    char *a = dst, *b = src;
    for (; (b - src) < sizeof(src); *a = *b, a++, b++);
}

// Create a new list
XINIT_ITEM *list_new ()
{
    XINIT_ITEM *l = malloc(sizeof(XINIT_ITEM));
    // l->val = 0;
    l->next = 0;

    return l;
}

// Get a list containing items from 'beg' to 'end'
XINIT_ITEM *list_range (XINIT_ITEM *l, int beg, int end)
{
    end = (end < list_len(l) ? end : list_len(l));
    XINIT_ITEM *new = list_new();

    for (; beg < end; beg++) {
        char *val = list_get(l, beg);
        list_add(new, val);
        free(val);
    }

    return new;
}

// Get an item at an index
char *list_get (XINIT_ITEM *l, int i)
{
    l = index(l, i);
    char *val = malloc(sizeof(l->val));
    copy(val, l->val);

    return val;
}

// Insert an item
void list_insert (XINIT_ITEM *l, int i, char *val)
{
    if (i == 0 && (int)(l->val) == 0) {
        list_add(l, val);
        return;
    }

    if (i > 0) {
        XINIT_ITEM *new = list_new();
        list_add(new, val);

        new->next = index(l, i);
        index(l, i - 1)->next = new;
    } else {
        XINIT_ITEM *next = list_new();
        list_add(next, l->val);
        next->next = l->next;

        // free(l->val);
        free(l);

        *l = *(list_new());
        list_add(l, val);
        l->next = next;
    }
}

// Append an item
void list_add (XINIT_ITEM *l, char *val)
{
    while ((int)(l->next) != 0) l = l->next;

    XINIT_ITEM *new = list_new();
    new->val = malloc(sizeof(val));
    copy(new->val, val);

    if ((int)(l->val) == 0) {
        l->val = malloc(sizeof(val));
        copy(l->val, new->val);
        list_free(new);
    } else l->next = new;
}

// Set an item at an index
void list_set (XINIT_ITEM *l, int i, char *val)
{
    if (i == 0 && (int)(l->val) == 0) {
        list_add(l, val);
        return;
    }

    l = index(l, i);
    free(l->val);
    l->val = malloc(sizeof(val));
    copy(l->val, val);
}

// Remove an item from a list
void list_remove (XINIT_ITEM *l, int i)
{
    l = index(l, i);

    if ((int)(l->next) == 0) {
        list_free(l);
        return;
    }

    XINIT_ITEM *n = l->next;
    l->next = n->next;
    list_set(l, 0, n->val);
    // free(n->val);
    free(n);
}

// Get the length of a list
int list_len (XINIT_ITEM *l)
{
    int i;
    for (i = 1; (int)(l->next) != 0; i++)
        l = l->next;

    return i;
}

// Get the index of an item, or -1
int list_index_of (XINIT_ITEM *l, char *val)
{
    int i = 0;

    do {
        // if (streq(l->val, val)) return i;

        i++;
        l = l->next;
    } while ((int)l != 0);

    return -1;
}

// Free a list
void list_free (XINIT_ITEM *l)
{
    if ((int)(l->next) != 0)
        list_free(l->next);

    // if ((int)(l->val) != 0)
        // free(l->val);

    free(l);
}