#ifndef _LIST_H
#define _LIST_H

#include "xinit.h"


XINIT_ITEM *list_new ();
XINIT_ITEM *list_range (XINIT_ITEM *l, int beg, int end);
char *list_get (XINIT_ITEM *l, int i);
void list_insert (XINIT_ITEM *l, int i, char *val);
void list_add (XINIT_ITEM *l, char *val);
void list_set (XINIT_ITEM *l, int i, char *val);
void list_remove (XINIT_ITEM *l, int i);
int list_len (XINIT_ITEM *l);
int list_index_of (XINIT_ITEM *l, char *val);
void list_free (XINIT_ITEM *l);

#endif