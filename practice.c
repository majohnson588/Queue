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
