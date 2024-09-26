#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define $$$
#define Stack_Ass(st) \


struct Stackstruct
{
    int* record;
    size_t cur_size;
    size_t max_size;
};

void StackInit(Stackstruct* st, int count_elem);
int StackOk(Stackstruct* st);
void StackPush(Stackstruct* st, int in);
int StackPull(Stackstruct* st);
void ShowStack(Stackstruct* st);
void MoreSize(Stackstruct* st);
void StackDestroy(Stackstruct* st);

int main()
{
    Stackstruct st = {};
    StackInit(&st, -1);
    for(int i = 0; i < 25; i++)
    {
        StackPush(&st, i);
//$$$     printf("i = %d \n", i);
    }
    for(int i = 0; i < 15; i++)
    {
        printf("%d \n", StackPull(&st));
    }

    StackDestroy(&st);

    return 0;
}

void StackInit(Stackstruct* st, int count_elem)
{
    assert(st);

    if(count_elem < 0)
    {
        fprintf(stderr, "SIZE CAN BE ONLY MORE THAN ZERO OR EQUAL \n \n");
        assert(0);
    }

    st->record = (int*) calloc(count_elem, sizeof(int));
    assert(st->record);

    st->cur_size = 0;

    if(count_elem > 1) st->max_size = count_elem;
    else st->max_size = 1;

    assert(StackOk(st));
}

int StackOk(Stackstruct* st)
{
    if(st == NULL || st->record == NULL || st->cur_size >= st->max_size)
    {
        ShowStack(st);
        return 0;
    }
    else return 1;
}

void ShowStack(Stackstruct* st)
{
    assert(st);

    FILE* err_out = fopen("ShowStack.txt", "w");

    fprintf(err_out, "current point = %lu \n max size = %lu \n", st->cur_size, st->max_size);

    int i = 0;
    while(i < st->cur_size)
    {
        fprintf(err_out, "*[%d] = %d \n", i, st->record[i]);
        i++;
    }

    int j = st->cur_size;
    while(j < st->max_size)
    {
        fprintf(err_out, "[%d] = %d B.ZH.D \n", j, st->record[j]);
        j++;
    }

    fclose(err_out);
}

void StackPush(Stackstruct* st, int in)
{
    assert(StackOk(st));

    MoreSize(st);

    st->record[st->cur_size] = in;
    st->cur_size++;

    assert(StackOk(st));
}

void MoreSize(Stackstruct* st)
{
    assert(st);

    if(st->cur_size >= st->max_size - 1)
    {
        st->max_size *= 2;
        st->record = (int*) realloc(st->record, st->max_size * sizeof(int));
        assert(st->record);
//$$$     printf("I NEED MORE SIZE \n");
    }

    assert(StackOk(st));
}

int StackPull(Stackstruct* st)
{
    assert(StackOk(st));

    st->cur_size--;
    int out = st->record[st->cur_size];

    if(4 * (st->cur_size) <= st->max_size)
    {
        int less_size = round((st->max_size)/2);
        st->record = (int*) realloc(st->record, less_size);
        assert(st->record);
        memset(st->record + st->cur_size + 1, 0, (st->max_size - st->cur_size)*sizeof(int));
        st->max_size = less_size;
    }

    assert(StackOk(st));

    return out;
}

void StackDestroy(Stackstruct* st)
{
    assert(StackOk(st));
    free(st->record);
    st->record = NULL;
    st->cur_size = 0;
    st->max_size = 0;
}
