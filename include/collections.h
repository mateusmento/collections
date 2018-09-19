#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include "node.h"
#include "list.h"

#define node_new(type) node_new(sizeof(type))
#define list_new(type) list_new(sizeof(type))
#define list_select(list, type, fn) list_select(list, sizeof(type), cast(ListSelectFn, fn))
#define list_filter(list, fn) list_filter(list, cast(ListFilterFn, fn))

#endif
