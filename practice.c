//用队列实现栈
//栈的特点是后入先出(LIFO)
//先将Queue.c和Queue.h的代码复制粘贴过来
#include "Queue.c"
#include "Queue.h"
typedef struct {
	Queue q1;
	Queue q2;
}MyStack;

MyStack* myStackCreate() {
	MyStack* obj = (MyStack*)malloc(sizeof(MyStack));
	QueueInit(&obj->q1);
	QueueInit(&obj->q2);

	if (obj == NULL)
	{
		printf("malloc fail");
	}

	return obj;
}

void myStackPush(MyStack* obj, int x) {
	if (!QueueEmpty(&obj->q1))
	{
		QueuePush(&obj->q1, x);
	}
	else
	{
		QueuePush(&obj->q2, x);
	}
}

int myStackPop(MyStack* obj) {
	Queue* emptyQ = &obj->q1;
	Queue* nonEmptyQ = &obj->q2;
	if (!QueueEmpty(&obj->q1))
	{
		emptyQ = &obj->q2;
		nonEmptyQ = &obj->q1;
	}

	while (QueueSize(nonEmptyQ) > 1)
	{
		QueuePush(emptyQ, QueueFront(nonEmptyQ));
	}

	int top = QueueFront(nonEmptyQ);
	QueuePop(nonEmptyQ);

	return top;
}

int myStackTop(MyStack* obj) {
	if (!QueueEmpty(&obj->q1))
	{
		return QueueBack(&obj->q1);
	}
	else
	{
		return QueueBack(&obj->q2);
	}
}

bool myStackEmpty(MyStack* obj) {
	return QueueEmpty(&obj->q1) && QueueEmpty(&obj->q2);
}

void myStackFree(MyStack* obj) {
	QueueDestroy(&obj->q1);
	QueueDestroy(&obj->q2);

	free(obj);
}


//用栈实现队列
//先复制Stack.c和Stack.h的代码
typedef struct {
	Stack pushst;
	Stack popst;
}MyQueue;

MyQueue* myQueueCreate() {
	MyQueue* obj = (MyQueue*)malloc(sizeof(MyQueue));
	StackInit(&obj->pushst);
	StackInit(&obj->popst);

	return obj;
}

void MyQueuePush(MyQueue* obj, int x) {
	StackPush(&obj->pushst, x);
}

void MyQueuePop(MyQueue* obj) {
	if (StackEmpty(&obj->popst))
	{
		//如果pop栈为空，则把push栈的数据倒过来
		while (!StackEmpty(&obj->pushst))
		{
			StackPush(&obj->popst, StackTop(&obj->pushst));
			StackPop(&obj->pushst);
		}
	}

	int front = StackTop(&obj->popst);
	StackPop(&obj->popst);
	return front;
}

//取队头
int myQueuePeek(MyQueue* obj) {
	if (StackEmpty(&obj->popst))
	{
		//如果pop栈为空，则把push栈的数据倒(导)过来
		while (!StackEmpty(&obj->pushst))
		{
			StackPush(&obj->popst, StackTop(&obj->pushst));
			StackPop(&obj->pushst);
		}
	}

	return StackTop(&obj->popst);
}

bool myQueueEmpty(MyQueue* obj) {
	return StackEmpty(&obj->popst) && StackEmpty(&obj->pushst);
}

void myQueueFree(MyQueue* obj) {
	StackDestroy(&obj->pushst);
	StackDestroy(&obj->popst);

	free(obj);
}
