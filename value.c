#include <stdio.h>
#include <string.h>

#include "value.h"
#include "object.h"
#include "memory.h"

void value_array_init(ValueArray *array)
{
    array->count = 0;
    array->capacity = 0;
    array->values = NULL;
}

void value_array_free(ValueArray *array)
{
    FREE_ARRAY(Value, array->values, array->capacity);
    value_array_init(array);
}

void value_array_write(ValueArray *array, Value value)
{
    if (array->capacity < array->count + 1)
    {
        int old_capacity = array->capacity;
        array->capacity = GROW_CAPACITY(old_capacity);
        array->values = GROW_ARRAY(Value, array->values, old_capacity, array->capacity);
    }

    array->values[array->count] = value;
    array->count++;
}

void value_print(Value value)
{
    switch (value.type)
    {
    case VAL_BOOL:
        printf(AS_BOOL(value) ? "True" : "False");
        break;
    case VAL_NONE:
        printf("None");
        break;
    case VAL_NUMBER:
        printf("%g", AS_NUMBER(value));
        break;
    case VAL_OBJ:
        object_print(value);
        break;
    }
}

bool values_equal(Value a, Value b)
{
    if (a.type != b.type)
        return false;
    switch (a.type)
    {
    case VAL_BOOL:
        return AS_BOOL(a) == AS_BOOL(b);
    case VAL_NONE:
        return true;
    case VAL_NUMBER:
        return AS_NUMBER(a) == AS_NUMBER(b);
    case VAL_OBJ:
    {
        return AS_OBJ(a) == AS_OBJ(b);
    }
    default:
        return false; // Unreachable.
    }
}