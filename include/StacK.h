#ifndef STACK_H
#define STACK_H

int SLook(size_t number);
void SPush(int in);
int SPull();
int* ChangeSize(int mode);
void SVerification();
void SDump();
unsigned int DJBHash(unsigned int delta);

#endif // STACK_H
