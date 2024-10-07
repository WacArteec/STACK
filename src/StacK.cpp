#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include <StacK.h>

enum SizeChanger
{
    MORE_SIZE,
    LESS_SIZE
};

enum Errors
{
    WRONGPOINTER,
    WRONGSIZE,
    NOTEXIST
};

struct Stack_Struct
{
    int* record = NULL;
    size_t point = 0;
    size_t size = 0;
};


void SCreate();
void SDestroy();
int SLook(size_t number);
void SPush(int in);
int SPull();
int* ChangeSize(int mode);
void SVerification(int LineNum);
void SDump();
unsigned int DJBHash(unsigned int delta);

static Stack_Struct stack = {};

static unsigned int stk_hash  = DJBHash(0);
static unsigned int prev_hash = 0;

void SCreate()
{
    stack.record = (int*) calloc(0+4, sizeof(int));
    SVerification(__LINE__);

//    printf("\n\n %u \n\n", stk_hash);

    stack.point = 0;

    stack.size = 1;

    SVerification(__LINE__);
}

void SDestroy()
{
    SVerification(__LINE__);

    free(stack.record);
    stack.record = NULL;

    stack.point = 0;
    stack.size  = 0;

    stk_hash  = DJBHash(0);
    prev_hash = 0;
}

int SLook(size_t number)
{
    if(number < stack.point)
        return stack.record[number]-1;
    else
    {
        printf("This element does not exist :)\n");
        return 0;
    }
}

void SPush(int in)
{
    if(stack.record == NULL) SCreate();

    SVerification(__LINE__);

    if(stack.point == stack.size)
        stack.record = ChangeSize(MORE_SIZE);

    stack.record[stack.point] = in;
    stack.point++;

    prev_hash = stk_hash;
    stk_hash = DJBHash(stk_hash + stack.record[stack.point-1]);

    SVerification(__LINE__);
}

int SPull()
{
    SVerification(__LINE__);

    stack.point--;
    int out = stack.record[stack.point];

    stack.record[stack.point] = 0;

    if(4 * (stack.point + 1) <= stack.size && stack.size > 20)
        stack.record = ChangeSize(LESS_SIZE);

    SVerification(__LINE__);

    if(stack.point == 0) SDestroy();

    return out;
}

int* ChangeSize(int mode)
{
    switch(mode)
    {
        case MORE_SIZE:

                stack.size *= 2;

                stack.record = (int*) realloc(stack.record, (stack.size + 4)* sizeof(int));
                SVerification(__LINE__);

                memset(stack.record + stack.point,
                       0,
                       (stack.size - stack.point + 2)*sizeof(int));

                SVerification(__LINE__);
            break;

        case LESS_SIZE:
        {
                stack.size = (stack.size)/2;

                stack.record = (int *) realloc(stack.record, (stack.size + 4) * sizeof(int));
                SVerification(__LINE__);

                memset(stack.record + stack.size*sizeof(int), 0, 2*sizeof(int));

            break;
        }
        default:
            break;
    }

    SVerification(__LINE__);

    return stack.record;
}

void SVerification(int LineNum)
{
    if(stack.record == NULL)
    {
        printf("\n error on line ¹%d\n", LineNum);
        printf("YOUR STACK DOES NOT EXIST");
        exit(1);
    }

    if(stack.point < 0)
    {
        printf("\n error on line ¹%d\n", LineNum);
        printf("YOUR STACK POINT HAS BROKEN");
        SDump();
        exit(1);
    }

    if(stack.point > stack.size)
    {
        printf("\n error on line ¹%d\n", LineNum);
        printf("YOUR STACK HAS WRONG SIZE");
        SDump();
        exit(1);
    }
    for(int i = 0; i < 1; i++)
    {
        if(*(stack.record + stack.size*sizeof(int) + i) != 0)
        {
            printf("\n error on line %d\n", LineNum);
            printf("YOUR STACK WAS HACKED");
            SDump();
            exit(1);
        }
    }
    if(stk_hash != DJBHash(prev_hash + stack.record[stack.point-1]))
    {
        printf("\n error on line ¹%d\n", LineNum);
        printf("YOUR STACK WAS CHANGED");
        SDump();
        exit(1);
    }
}

void SDump()
{
    FILE* err_out = fopen("ShowStack.txt", "w");

    fprintf(err_out, "current point = %llu \n max size = %llu \n", stack.point, stack.size);

    size_t i = 0;
    while(i < stack.point || stack.record[i] > 0)
    {
        fprintf(err_out, "*[%llu] = %d \n", i, stack.record[i]);
        i++;
    }

    fclose(err_out);
}

unsigned int DJBHash(unsigned int delta)
{
	static unsigned int hash_ = rand()%10000;
	static unsigned int lenght = 1000;

	for (unsigned int i = 0; i < lenght; i++)
	{
		hash_ = ((stk_hash << 5)*MORE_SIZE + hash_*LESS_SIZE) + (delta + hash_*MORE_SIZE*(delta + hash_*MORE_SIZE*(delta + hash_*MORE_SIZE*(delta + hash_*MORE_SIZE))))*MORE_SIZE;
	}

	return hash_;
}
