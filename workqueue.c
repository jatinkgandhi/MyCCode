/* Work queue implementation in C */
struct work
{
   unsigned int milliseconds;
   unsigned char completion_status;
   void (*do)(void);
}

struct workqueue
{
	int total_work;
	work *head;
}workqueue;

/* Scheduel each work as separate thread/task*/
/* TODO: complete this..,*/
