/* lab3.c
 * Huzefa Dossaji                        <--- replace with your name!
 * hdossaj                             <--- replace with your user name!
 * ECE 223 Fall 2015
 * MP3
 *
 * NOTE:  You must update all of the following comments!
 *
 * Propose: A template for MP3. contains the main() function, menu code for handling simple input and output, and
 * any other functions that are not part of the ADT
 *
 * Assumptions: This file is simple.  Input is collected and the
 * appropriate wifi function is called.
 *
 * An outline for the interactive menu input is provided.  Details need to be
 * completed but format of the commands and the output generated by the
 * print statements must not be changed. You have to call the corrent 
 * print statement in response to the input
 *
 * Bugs: No bugs have been observed.
 *
 * See the ECE 223 programming guide
 *
 * Are you unhappy with the way this code is formatted?  You can easily
 * reformat (and automatically indent) your code using the astyle 
 * command.  If it is not installed use the Ubuntu Software Center to 
 * install astyle.  Then in a terminal on the command line do
 *     astyle --style=kr lab1.c
 *
 * See "man astyle" for different styles.  Replace "kr" with one of
 * ansi, java, gnu, linux, or google to see different options.  Or, set up 
 * your own style.
 *
 * To create a nicely formated PDF file for printing install the enscript 
 * command.  To create a PDF for "file.c" in landscape with 2 columns do:
 *     enscript file.c -G2rE -o - | ps2pdf - file.pdf
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "datatypes.h"
#include "list.h"
#include "hpot_support.h"

int main(int argc, char * argv[])
{
    pList sorted_list;
    pList unsorted_list;
    pList priority_list;
    char line[MAXLINE];
    char command[MAXLINE];
    char junk[MAXLINE];
    int num_items;
    int id_add;

    if (argc != 1) {
        printf("Usage: ./lab2\n");
        exit(1);
    }
    /*
    printf("Welcome to lab2. Possible commands:\n");
    printf("Sorted list: INSERT x; LIST x; REMOVE x; SCAN x; PRINT\n");
    printf("Queue      : ADDTAIL x; RMHEAD; PRINTQ\n");
    printf("PQueue     : APPENDL x; SORTL x; PRINTL; SCANL x\n");
    printf("           : STATS; QUIT\n");
    */
    int scan3 = 1;
    // Create two List objects
    /* this list is sorted */
    sorted_list = hpot_create("List");

    /* this list is unsorted and has no duplicates */
    unsorted_list = hpot_create("Queue");
    
    /* this list is for the priority queue */
    priority_list = hpot_create("Priority");

    /* remember fgets includes newline \n unless line too long */
    while (fgets(line, MAXLINE, stdin) != NULL) {
        num_items = sscanf(line, "%s%d%s", command, &id_add, junk);
        if (num_items == 2 && strcmp(command, "INSERT") == 0) {
            hpot_add(sorted_list, id_add);
        } else if (num_items == 2 && strcmp(command, "LIST") == 0) {
            hpot_list(sorted_list, id_add);
        } else if (num_items == 2 && strcmp(command, "REMOVE") == 0) {
            hpot_remove(sorted_list, id_add);
        } else if (num_items == 2 && strcmp(command, "SCAN") == 0) {
            hpot_scan(sorted_list, id_add);
        } else if (num_items == 1 && strcmp(command, "PRINT") == 0) {
            hpot_print(sorted_list, "List");
        } else if (num_items == 2 && strcmp(command, "ADDTAIL") == 0) {
            hpot_add_tail(unsorted_list, id_add);
        } else if (num_items == 1 && strcmp(command, "RMHEAD") == 0) {
            hpot_remove_head(unsorted_list);
        } else if (num_items == 1 && strcmp(command, "PRINTQ") == 0) {
            hpot_print(unsorted_list, "Queue");
        } else if (num_items == 1 && strcmp(command, "STATS") == 0) {
            hpot_stats(sorted_list, unsorted_list, priority_list);
        } else if (num_items == 2 && strcmp(command, "APPENDL") == 0) {
            hpot_add_tail_append(priority_list, id_add);
            scan3=-1;
        } else if (num_items == 2 && strcmp(command, "SORTL") == 0) {
            
            scan3=1;
            
                clock_t start, end;
                double elapse_time; /* time in milliseconds */
                //(when the SORTL command is found do)
                int initialsize = list_size(priority_list);
                start = clock();
                hpot_sort(priority_list, id_add);
                end = clock();
                elapse_time = 1000.0 * ((double) (end - start)) / CLOCKS_PER_SEC;
                assert(list_size(priority_list) == initialsize);
                printf("%d\t%f\t%d\n", initialsize, elapse_time, id_add);
                
        } else if (num_items == 1 && strcmp(command, "PRINTL") == 0) {
            hpot_print(priority_list, "Priority");
        } else if (num_items == 2 && strcmp(command, "SCANL") == 0) {
            if(scan3 == 1){
            hpot_scan_MP3(priority_list, id_add);
            }
            else
            {
            printf("This operation cannot be performed until the list has been sorted.\n");
            }
        }else if (num_items == 1 && strcmp(command, "QUIT") == 0) {
            hpot_cleanup(sorted_list);
            hpot_cleanup(unsorted_list);
            hpot_cleanup(priority_list);
           // printf("Goodbye\n");
            break;
        } else {
            printf("# %s", line);
        }
    }
    exit(0);
}
/* commands specified to vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */