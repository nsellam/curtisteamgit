/**
 * @file queue.h
 * @author Curtis Team
 * @brief header of queue.c
 */

#ifndef QUEUE_H
#define QUEUE_H

/********************************/
/*       LIBRARIES              */
/********************************/

#include <stdint.h>


/********************************/
/*       DEFINES                */
/********************************/


/**
* @brief ID of any command when we go backward with xpsapi function
*/
#define GO_BACKWARD_COMMAND 1

/**
* @brief ID of any command when we go forward with xpsapi function
*/
#define GO_FORWARD_COMMAND 2


/********************************/
/*       VARIABLES              */
/********************************/



/********************************/
/*       STRUCTURES             */
/********************************/

struct information
{
    uint8_t command_type;             /*!< to identify the command type */
    float cmd1;                       /*!< the 1st part of the command */
    int cmd2;                         /*!< the 2nd part of the command (mandotary)*/
    int cmd3;                         /*!< the 3rd part of the command (mandatory)*/
};






/********************************/
/*       FUNCTIONS              */
/********************************/

/**
* @brief the first in element of FIFO
* @retval the value stored in the first in element of FIFO
*/
struct information frontelement();

/**
* @brief adds an element to the fifo
* @param the data we want to add to the fifo
* @retval none
*/
void enq(struct information data);

/**
* @brief removes an element to the fifo
* @retval none
*/
void deq();

/**
* @brief tells if the fifo is empty  or not
* @retval 1 if queue empty, 0 if not
*/
uint8_t empty();

/**
* @brief displays the content of the fifo
* @retval none
*/
void display();

/**
* @brief creates a fifo
* @retval none
*/
void create();

/**
* @brief add an element to the fifo
* @retval the queue size (number of elements in it)
*/
int queuesize();
 



#endif