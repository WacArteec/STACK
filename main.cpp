#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define $$$
#define stack stacks[current_stack]

enum{MORESIZE, LESSSIZE};
enum {SIZE_PROBLEM};

int current_stack = 0;

typedef long unsigned int stack_type_duty ;

struct Stackstruct
{
    int* record;
    stack_type_duty cur_size;
    stack_type_duty max_size;
};
struct Stackstruct stacks[128] = {};

void StackInit();
void StackOk(int LineNum);
void StackPush(int in);
int StackPull();
void ShowStack();
void ChangeSize(int mode);
void StackDestroy();

int main()
{
    StackInit();

    for(int i = 1; i < 100; i++)
    {
        StackPush(i);
//$$$     printf("i = %d \n", i);
    }

    for(int i = 0; i < 100; i++)
    {
//$$$     printf("\n %d\n", 24-i);
//$$$     printf("\n current point = %d \n", st.cur_size);
        printf("StackPull = %d \n", StackPull());
    }
    return 0;
}

void StackInit()
{
    static int StackNum = 0;

    stacks[StackNum] = {};

    stacks[StackNum].record = (int*) calloc(0, sizeof(int));
    assert(stacks[StackNum].record);

    stacks[StackNum].cur_size = 0;

    stacks[StackNum].max_size = 1;

    current_stack = StackNum;

    StackNum++;

    StackOk(__LINE__);
}

void StackOk(int LineNum)
{
    if(/*stacks[current_stack] == NULL ||*/ stacks[current_stack].record == NULL || stacks[current_stack].cur_size >= stacks[current_stack].max_size)
    {
        printf("\n error on line ¹%d\n", LineNum);
        ShowStack();
        exit(1);
    }
}

void ShowStack()
{
    FILE* err_out = fopen("ShowStack.txt", "w");

    fprintf(err_out, "current point = %lu \n max size = %lu \n", stacks[current_stack].cur_size, stacks[current_stack].max_size);

    stack_type_duty i = 0;
    while(i < stack.cur_size)
    {
        fprintf(err_out, "*[%lu] = %d \n", i, stack.record[i]);
        i++;
    }

    stack_type_duty j = stack.cur_size;
    while(j < stack.max_size)
    {
        fprintf(err_out, "[%lu] = %d B.ZH.D \n", j, stack.record[j]);
        j++;
    }

    fclose(err_out);
}

void StackPush(int in)
{
    StackOk(__LINE__);

    ChangeSize(MORESIZE);

    stack.record[stack.cur_size] = in;
    stack.cur_size++;

    StackOk(__LINE__);
}

void ChangeSize(int mode)
{
    switch(mode)
    {
        case MORESIZE:
            if(stack.cur_size >= stack.max_size - 1)
            {
                stack.max_size *= 2;
                stack.record = (int*) realloc(stack.record, stack.max_size * sizeof(int));
                assert(stack.record);
//$$$             printf("I NEED MORE SIZE \n");
            }
            break;

        case LESSSIZE:
            if(4 * (stack.cur_size + 1) <= stacks[current_stack].max_size)
            {
                int less_size = round((stacks[current_stack].max_size)/2);
$$$             printf("I NEED LESS SIZE current point = %d \t max size = %d \t need size = %d \n",
                       stacks[current_stack].cur_size,
                       stacks[current_stack].max_size,
                       less_size
                       );

                stacks[current_stack].record = (int*) realloc(stacks[current_stack].record, less_size);
                assert(stacks[current_stack].record);

                memset(stacks[current_stack].record + stacks[current_stack].cur_size + 1,
                       0,
                       (stacks[current_stack].max_size - stacks[current_stack].cur_size)*sizeof(int)
                       );
                stacks[current_stack].max_size = less_size;

//$$$             printf("I NEED LESS SIZE current point = %d \n", stacks[current_stack].cur_size);
            }
            break;
        default:
            break;
    }

    StackOk(__LINE__);
}

int StackPull()
{
    StackOk(__LINE__);

    stacks[current_stack].cur_size--;
    int out = stacks[current_stack].record[stacks[current_stack].cur_size];

    //stacks[current_stack].record[stacks[current_stack].cur_size] = 0;

    ChangeSize(LESSSIZE);

    StackOk(__LINE__);

    return out;
}


void StackDestroy()
{
    StackOk(__LINE__);
    free(stacks[current_stack].record);
    stacks[current_stack].record = NULL;
    stacks[current_stack].cur_size = 0;
    stacks[current_stack].max_size = 0;
    current_stack--;
}
