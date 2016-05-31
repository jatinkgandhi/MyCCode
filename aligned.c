#include <stdio.h>
#include <stdlib.h>


void * aligned_malloc(size_t size, int align) {
    /* alignment could not be less then zero */
    if (align < 0) {
        return NULL;
    }
     
    /* Allocate necessary memory area
     * client request - size parameter -
     * plus area to store the address
     * of the memory returned by standard
     * malloc().
     */
    void *ptr;
    void *p = malloc(size + align - 1 + sizeof(void*));
     
    if (p != NULL) {
        /* Address of the aligned memory according to the align parameter*/
        ptr = (void*) (((unsigned int)p + sizeof(void*) + align -1) & ~(align-1));
        /* store the address of the malloc() above
         * at the beginning of our total memory area.
         * You can also use *((void **)ptr-1) = p
         * instead of the one below.
         */
        *((void**)((unsigned int)ptr - sizeof(void*))) = p;
        /* Return the address of aligned memory */
        return ptr; 
    }
    return NULL;
}
 
void aligned_free(void *p) {
    /* Get the address of the memory, stored at the
     * start of our total memory area. Alternatively,
     * you can use void *ptr = *((void **)p-1) instead 
     * of the one below.
     */
    void *ptr = *((void**)((unsigned int)p - sizeof(void*)));
    free(ptr);
    return;
}


int main(int argc, char **argv)
{
	char *p1, *p2;
	
	p1 = malloc(127);
	printf("first : 0x%08x\n",p1);
	free(p1);
	p2 = aligned_malloc(127, 4);
	printf("second : 0x%08x\n",p2);
	aligned_free(p2);
	
	p2 = aligned_malloc(127, 8);
	printf("second : 0x%08x\n",p2);
	aligned_free(p2);
	
	return 0;
}


