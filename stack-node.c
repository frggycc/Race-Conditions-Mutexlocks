
/*******************************
* CPSC351: Group Assignment #3
* Members: 
* 	Charlie Cardenas
* 	Chaitanya Talluri
* 	Ansh Tomar
* 	Hunter Tran
********************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREAD 200

// Declare thread lock
pthread_mutex_t lock;

// Linked list node
typedef int value_t;
typedef struct Node
{
    value_t data;
    struct Node *next;
} StackNode;

// Stack function declarations
void    push    (value_t v, StackNode **top);
value_t pop     (           StackNode **top);
int     is_empty(           StackNode *top);
void *testStack(void *stack);

int main(void)
{
    pthread_t workers[NUM_THREAD];
    StackNode *top = NULL;

    for(int i = 0; i < NUM_THREAD; i++){
        pthread_create(&workers[i], NULL, testStack, &top);
    }

    // Test if affected one stack
    // for(int i = 2000; i > 0; i--){
    //     value_t value = pop(&top);
    //     printf("value on top: %d\n", value);
    // }

    for (int i = 0; i < NUM_THREAD; ++i) {
        pthread_join(workers[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}

// Stack function definitions
void push(value_t v, StackNode **top)
{
    // Thread holds onto shared stack
    pthread_mutex_lock(&lock);

    StackNode * new_node = malloc(sizeof(StackNode));

    new_node->data = v;
    new_node->next = *top;
    *top           = new_node;

    // Thread releases shared stack
    pthread_mutex_unlock(&lock);
}

value_t pop(StackNode **top)
{
    // Thread holds onto shared stack
    pthread_mutex_lock(&lock);

    if (is_empty(*top)) return (value_t)0;

    // Segfault can occur with race condition 
    value_t     data  = (*top)->data;
    StackNode * temp  = *top;
    *top              = (*top)->next;

    // Double free can occur with race condition
    free(temp);

    // Thread releases shared stack
    pthread_mutex_unlock(&lock);

    return data;
}

int is_empty(StackNode *top) {
    if (top == NULL) return 1;
    else             return 0;
}

void *testStack(void *arg){
    // Test to the one stack
    StackNode** top = (StackNode**)arg;

    // testing push and pop
    for (int i = 1; i <= 500; i++){
        // 3 push operations
        push(i, top);
        push(i, top);
        push(i, top);
        // To test if all changed one stack
        // push(i, top);

        // 3 pop operations
        pop(top);
        pop(top);
        pop(top);
    }

    return NULL;
}