#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define $$$
#define Stack_Ass(st) \

enum {SIZE_PROBLEM};

typedef long unsigned int stack_type_duty ;

struct Stackstruct
{
    int* record;
    stack_type_duty cur_size;
    stack_type_duty max_size;
    const char* err_out_file = "ShowStack.txt";
};

int StackInit(Stackstruct* st, int count_elem);
void StackOk(Stackstruct* st, int LineNum);
void StackPush(Stackstruct* st, int in);
int StackPull(Stackstruct* st);
void ShowStack(Stackstruct* st);
void ChangeSize(Stackstruct* st);
void StackDestroy(Stackstruct* st);

int main()
{
    Stackstruct st = {};

    int stack_size = 0;
    do
    {
        printf("Enter size of your stack: \n");
        scanf("%d", &stack_size);
    }
    while(StackInit(&st, stack_size));

    for(int i = 0; i < 25; i++)
    {
        StackPush(&st, i);
//$$$     printf("i = %d \n", i);
    }

    for(int i = 0; i < 25; i++)
    {
        printf("%d \n", StackPull(&st));
    }

    StackDestroy(&st);

    return 0;
}

int StackInit(Stackstruct* st, int count_elem)
{
    assert(st);

    if(count_elem < 0)
    {
        fprintf(stderr, "SIZE CAN BE ONLY MORE THAN ZERO OR EQUAL \n \n");
        return 1;
    }

    st->record = (int*) calloc(count_elem, sizeof(int));
    assert(st->record);

    st->cur_size = 0;

    if(count_elem > 1) st->max_size = count_elem;
    else st->max_size = 1;

    StackOk(st, __LINE__);

    return 0;
}

void StackOk(Stackstruct* st, int LineNum)
{
    if(st == NULL || st->record == NULL || st->cur_size >= st->max_size)
    {
        printf("\n error on line ¹%d\n", LineNum);
        ShowStack(st);
        exit(1);
    }
}

void ShowStack(Stackstruct* st)
{
    assert(st);

    FILE* err_out = fopen(st->err_out_file, "w");

    fprintf(err_out, "current point = %lu \n max size = %lu \n", st->cur_size, st->max_size);

    stack_type_duty i = 0;
    while(i < st->cur_size)
    {
        fprintf(err_out, "*[%lu] = %d \n", i, st->record[i]);
        i++;
    }

    stack_type_duty j = st->cur_size;
    while(j < st->max_size)
    {
        fprintf(err_out, "[%lu] = %d B.ZH.D \n", j, st->record[j]);
        j++;
    }

    fclose(err_out);
}

void StackPush(Stackstruct* st, int in)
{
    StackOk(st, __LINE__);

    ChangeSize(st);

    st->record[st->cur_size] = in;
    st->cur_size++;

    StackOk(st, __LINE__);
}

void ChangeSize(Stackstruct* st)
{
    assert(st);

    if(st->cur_size >= st->max_size - 1)
    {
        st->max_size *= 2;
        st->record = (int*) realloc(st->record, st->max_size * sizeof(int));
        assert(st->record);
//$$$     printf("I NEED MORE SIZE \n");
    }

    if(4 * (st->cur_size + 1) <= st->max_size)
    {
        int less_size = round((st->max_size)/2);
        st->record = (int*) realloc(st->record, less_size);
        assert(st->record);
        memset(st->record + st->cur_size + 1, 0, (st->max_size - st->cur_size)*sizeof(int));
        st->max_size = less_size;
    }

    StackOk(st, __LINE__);
}

int StackPull(Stackstruct* st)
{
    StackOk(st, __LINE__);

    st->cur_size--;
    int out = st->record[st->cur_size];

    ChangeSize(st);

    StackOk(st, __LINE__);

    return out;
}


void StackDestroy(Stackstruct* st)
{
    StackOk(st, __LINE__);
    free(st->record);
    st->record = NULL;
    st->cur_size = 0;
    st->max_size = 0;
}
