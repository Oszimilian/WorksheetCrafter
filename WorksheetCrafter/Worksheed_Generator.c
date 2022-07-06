#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <time.h>
#include <setjmp.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "hpdf.h"
#include "WorksheedCrafter.h"

/*
*   Initialise the settings for the math-PDF
*/
void Init_Task_Settings(struct worksheed *worksheed_pointer)
{
    worksheed_pointer->addition_flag = true;
    worksheed_pointer->subtraction_flag = true;
    worksheed_pointer->multiplication_flag = true;
    worksheed_pointer->division_flag = true;

    worksheed_pointer->Z_flag = true;
    worksheed_pointer->R_flag = false;

    worksheed_pointer->baseboard_flag = true;
}

/*
*   Creats a sheed with the asked solutions
*/
void Create_Task_Sheed(struct worksheed *worksheed_pointer)
{
    Create_Baseboard(worksheed_pointer, _Tasks);

    int size_counter = HPDF_Page_GetHeight(worksheed_pointer->page[_Tasks]) - worksheed_pointer->baseboard_treashold;
    int task_counter = 0;
    int x;

    srand(time(NULL));

    for(int i = 0; i <= 2; i++)
    {

        while(size_counter >= 50)
        {

            switch(i)
            {
                case 0: x = HPDF_Page_GetWidth(worksheed_pointer->page[0]) - (HPDF_Page_GetWidth(worksheed_pointer->page[0]) * 0.9); break;
                case 1: x = HPDF_Page_GetWidth(worksheed_pointer->page[0]) - (HPDF_Page_GetWidth(worksheed_pointer->page[0]) * 0.6); break;
                case 2: x = HPDF_Page_GetWidth(worksheed_pointer->page[0]) - (HPDF_Page_GetWidth(worksheed_pointer->page[0]) * 0.3); break;
                default: break;
            }

            Create_Random_Task(worksheed_pointer, task_counter);

            Write_Text(worksheed_pointer, x, size_counter, worksheed_pointer->mathTaskArray[task_counter], _Tasks);

            Draw_Solution_Line(worksheed_pointer, worksheed_pointer->mathTaskArray[task_counter], x, size_counter, 60, _Tasks);

            task_counter++;

            size_counter = size_counter - 50;

            printf("Hallo \n");

        }

        size_counter = HPDF_Page_GetHeight(worksheed_pointer->page[_Tasks]) - worksheed_pointer->baseboard_treashold;

    }
}

/*
*   Creas a sheed with the solutions
*/
void Creat_Solution_Sheed(struct worksheed *worksheed_pointer)
{
    Create_Baseboard(worksheed_pointer, _Solutions);

    int size_counter = HPDF_Page_GetHeight(worksheed_pointer->page[_Solutions]) - worksheed_pointer->baseboard_treashold;
    int task_counter = 0;
    int x;

    for(int i = 0; i <= 2; i++)
    {

        while(size_counter >= 50)
        {

            switch(i)
            {
                case 0: x = HPDF_Page_GetWidth(worksheed_pointer->page[_Solutions]) - (HPDF_Page_GetWidth(worksheed_pointer->page[_Solutions]) * 0.9); break;
                case 1: x = HPDF_Page_GetWidth(worksheed_pointer->page[_Solutions]) - (HPDF_Page_GetWidth(worksheed_pointer->page[_Solutions]) * 0.6); break;
                case 2: x = HPDF_Page_GetWidth(worksheed_pointer->page[_Solutions]) - (HPDF_Page_GetWidth(worksheed_pointer->page[_Solutions]) * 0.3); break;
                default: break;
            }

            Write_Text(worksheed_pointer, x, size_counter, worksheed_pointer->mathSolutionArray[task_counter], _Solutions);

            task_counter++;

            size_counter = size_counter - 50;

            printf("-> %s \n", worksheed_pointer->mathSolutionArray[task_counter]);
        }

        size_counter = HPDF_Page_GetHeight(worksheed_pointer->page[_Solutions]) - worksheed_pointer->baseboard_treashold;

    }

}


