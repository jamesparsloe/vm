#ifndef VALUE_H
#define VALUE_H

#include "common.h"

typedef struct Obj Obj;
typedef struct ObjString ObjString;

typedef enum
{
    VAL_BOOL,
    VAL_NONE,
    VAL_NUMBER,
    VAL_OBJ
} ValueType;

typedef struct
{
    ValueType type;
    union
    {
        bool boolean;
        double number;
        Obj *obj;
    } as;
} Value;

#define IS_BOOL(value) ((value).type == VAL_BOOL)
#define IS_NONE(value) ((value).type == VAL_NONE)
#define IS_NUMBER(value) ((value).type == VAL_NUMBER)
#define IS_OBJ(value) ((value).type == VAL_OBJ)

#define AS_OBJ(value) ((value).as.obj)
#define AS_BOOL(value) ((value).as.boolean)
#define AS_NUMBER(value) ((value).as.number)

#define BOOL_VAL(value) ((Value){VAL_BOOL, {.boolean = value}})
#define NONE_VAL ((Value){VAL_NONE, {.number = 0}})
#define NUMBER_VAL(value) ((Value){VAL_NUMBER, {.number = value}})
#define OBJ_VAL(object) ((Value){VAL_OBJ, {.obj = (Obj *)object}})

typedef struct
{
    int count;
    int capacity;
    Value *values;
} ValueArray;

void value_array_init(ValueArray *array);
void value_array_free(ValueArray *array);
void value_array_write(ValueArray *array, Value value);
void value_print(Value value);

bool values_equal(Value a, Value b);

#endif