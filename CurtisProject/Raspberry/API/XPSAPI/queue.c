/*
 * C Program to Implement Queue Data Structure using Linked List
 */
#include <stdio.h>
#include <stdlib.h>

#include <queue.h>
 

 
struct node
{
    struct information info;             /*!< the struct containing all the command infos */
    struct node *ptr;                    /*!< pointer to next node in the fifo linked chain */
}*front,*rear,*temp,*front1;
 
int count = 0;
 
/* Create an empty queue */
void create()
{
    front = rear = NULL;
}
 
/* Returns queue size */
int queuesize()
{
    //printf("\n Queue size : %d", count);
    return count;
}
 
/* Enqueing the queue */
void enq(struct information data)
{
    if (rear == NULL)
    {
        rear = (struct node *)malloc(1*sizeof(struct node));
        rear->ptr = NULL;
        rear->info = data;
        front = rear;
    }
    else
    {
        temp=(struct node *)malloc(1*sizeof(struct node));
        rear->ptr = temp;
        temp->info = data;
        temp->ptr = NULL;
 
        rear = temp;
    }
    count++;
} 
 
/* Displaying the queue elements */
void display()
{
    front1 = front;
 
    if ((front1 == NULL) && (rear == NULL))
    {
        printf("Queue is empty");
        return;
    }
    while (front1 != rear)
    {
        printf("%d\n", front1->info.command_type);
        printf("%f\n", front1->info.cmd1);
        printf("%d\n", front1->info.cmd2);
        printf("%d\n", front1->info.cmd3);
        front1 = front1->ptr;
    }
    if (front1 == rear) {
        printf("%d\n", front1->info.command_type);
        printf("%f\n", front1->info.cmd1);
        printf("%d\n", front1->info.cmd2);
        printf("%d\n", front1->info.cmd3);
    }
}
 
/* Dequeing the queue */
void deq()
{
    front1 = front;
 
    if (front1 == NULL)
    {
        printf("\n Error: Trying to display elements from empty queue");
        return;
    }
    else
        if (front1->ptr != NULL)
        {
            front1 = front1->ptr;
            printf("\n Dequed value : %d", front->info);
            free(front);
            front = front1;
        }
        else
        {
            printf("\n Dequed value : %d", front->info);
            free(front);
            front = NULL;
            rear = NULL;
        }
        count--;
}
 
/* Returns the front element of queue */
struct information frontelement()
{
    if ((front != NULL) && (rear != NULL))
        return(front->info);
}
 
/* Tells if queue is empty or not */
uint8_t empty()
{
    uint8_t retval;

    if ((front == NULL) && (rear == NULL))
       retval = 1;
    else
       retval = 0;

    return retval;
}





/*

void main()
{
    struct information no, e;
    int ch;
 
    printf("\n 1 - Enque");
    printf("\n 2 - Deque");
    printf("\n 3 - Front element");
    printf("\n 4 - Empty");
    printf("\n 5 - Exit");
    printf("\n 6 - Display");
    printf("\n 7 - Queue size");
    create();
    while (1)
    {
        printf("\n Enter choice : ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter data : ");
            scanf("%d", &no);
            enq(no);
            break;
        case 2:
            deq();
            break;
        case 3:
            e = frontelement();
            if (e != 0)
                printf("Front element : %d", e);
            else
                printf("\n No front element in Queue as queue is empty");
            break;
        case 4:
            empty();
            break;
        case 5:
            exit(0);
        case 6:
            display();
            break;
        case 7:
            queuesize();
            break;
        default:
            printf("Wrong choice, Please enter correct choice  ");
            break;
        }
    }
}*/
 
