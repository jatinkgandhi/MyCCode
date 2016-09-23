#include <stdio.h>
#include <string.h>

#define	MAX	10000

typedef struct _stack
{
	int Stack[MAX];
	int Ptr;
	void (*Push) (struct _stack *p,int data);
	int (*Pop) (struct _stack *p);
}stack;


void Push(stack *pstack,int data);
int Pop(stack *pstack);
void StackTest(void);

typedef struct _queue
{

	int Queue[MAX];
	int HeadPtr;
	int TailPtr;
	void (*Insert)(struct _queue *p, int data);
	int (*Remove)(struct _queue *p);
}queue;

void Insert(struct _queue *p, int data);
int Remove(struct _queue *p);

void QueueTest(void);


typedef struct _cirbuf
{
	int pCur;
	int Buffer[MAX];
	void (*Add)(struct _cirbuf *p, int data);
	int (*Get)(struct _cirbuf *p);
}cirbuf;

void CirBuffTest(void);
void Add(cirbuf *p, int x);
int Get(cirbuf *p);

int main(int argc, char **argv)
{
	CirBuffTest();
	StackTest();
	QueueTest();
	printf("Hello World\n");
}

void StackTest(void)
{
	int i;
	stack st = {0};
	memset(st.Stack,0,MAX);
	st.Ptr = 0;
	st.Push = Push;
	st.Pop  = Pop;

	for(i = 0 ; i < MAX; i++)
		st.Push(&st,i);

	
	for(i = 0 ; i < MAX; i++)
		printf("0x%08x\n",st.Pop(&st));	
}


void Push(stack *pstack, int data)
{
	if(NULL == pstack) return;
	if(pstack->Ptr >= MAX)
	{
		printf("Stack Full\n");	
	} else {
		pstack->Stack[pstack->Ptr] = data;
		pstack->Ptr++;
	}
}

int Pop(stack *pstack)
{
	int data = 0xDEADC0DE;

	if(NULL == pstack) return;
	if(pstack->Ptr <= 0)
	{
		printf("Stack Empty\n");	
	} else {
		data = pstack->Stack[pstack->Ptr];
		pstack->Ptr--;
	}
	return data;
}


/* QUEUE : May be buggy : Through Review Required. */
/* Need to debug */
void QueueTest(void)
{
	int i;
	queue queue = {0};
	memset(queue.Queue,0,MAX);
	queue.HeadPtr = 0;
	queue.TailPtr = 0;
	queue.Insert = Insert;
	queue.Remove = Remove;
	
	printf("\n:::::::::::Queue Test:::::::::::\n");

	for(i = 0 ; i < MAX+3; i++)
		queue.Insert(&queue,i);

	
	for(i = 0 ; i < MAX+3; i++)
		printf("0x%08x\n",queue.Remove(&queue));

	queue.Insert(&queue,23);
	printf("0x%08x\n",queue.Remove(&queue));

	printf("\n DONE \n");
}


void Insert(struct _queue *p, int data)
{
	if(p->HeadPtr != MAX)
	{
		p->Queue[p->HeadPtr] = data;
		p->HeadPtr++;
	} else 	/* if(p->HeadPtr == MAX) */ {
		if (0 != p->TailPtr) 
		{
			p->HeadPtr = 0;
		} else  {
			printf("Q is full\n");
		} 
	}
}

int Remove(struct _queue *p)
{
	int data = 0xDEADC0DE;

	if(p->TailPtr != MAX)
	{
		data = p->Queue[p->TailPtr];
		p->TailPtr++;
	} else /* if(p->TailPtr == MAX) */ {
		if(0 != p->HeadPtr)
		{
			p->TailPtr = 0;
		} else {
			data = 0xDEADC0DE;
			printf("Queue Is Empty\n");
		}
	}

	return data;
}


/* Cirbuff */
void Add(cirbuf *p, int data)
{
	printf("%s : data : %d\n",__FUNCTION__,data);
	p->Buffer[p->pCur] = data;
	p->pCur++;
	if(p->pCur >= MAX)
	{
		p->pCur = 0;
	} 
}


int Get(cirbuf *p)
{
	int data = 0xDEADC0DE;

	if((p->pCur >=0) && (p->pCur <= MAX))
	{
		data = p->Buffer[p->pCur];
		p->pCur++;
	}
	return data;
}


void CirBuffTest(void)
{
	int i;
	cirbuf cir;
	memset(cir.Buffer,0,MAX);
	cir.pCur = 0;
	cir.Add = Add;
	cir.Get = Get;
	
	for(i = 0; i < MAX + 5; i++)
	{
		cir.Add(&cir,i);
	}

	cir.pCur = 0;
	for(i = 0; i < MAX + 5; i++)
	{
		printf("Data In Buff : %d\n",cir.Get(&cir));
	}
}
