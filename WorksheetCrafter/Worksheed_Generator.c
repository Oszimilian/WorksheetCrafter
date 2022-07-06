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
}

/*
*   Changes the Setting for generating the math-PDF
*/
void Change_Task_Settings(struct worksheed *worksheed_pointer, int setting)
{
    if(setting == _Addition)
    {
        if (worksheed_pointer->addition_flag)
        {
            worksheed_pointer->addition_flag = false;
        }else{
            worksheed_pointer->addition_flag = true;
        }
    }

    if(setting == _Subtraction)
    {
        if (worksheed_pointer->subtraction_flag)
        {
            worksheed_pointer->subtraction_flag = false;
        }else{
            worksheed_pointer->subtraction_flag = true;
        }
    }

    if(setting == _Multiplication)
    {
        if (worksheed_pointer->multiplication_flag)
        {
            worksheed_pointer->multiplication_flag = false;
        }else{
            worksheed_pointer->multiplication_flag = true;
        }
    }

    if(setting == _Division)
    {
        if (worksheed_pointer->division_flag)
        {
            worksheed_pointer->division_flag = false;
        }else{
            worksheed_pointer->division_flag = true;
        }
    }

    if(setting == _Zahlentyp)
    {
        if (worksheed_pointer->Z_flag && !worksheed_pointer->R_flag)
        {
            worksheed_pointer->Z_flag = false;
            worksheed_pointer->R_flag = true;
        }else{
            worksheed_pointer->Z_flag = true;
            worksheed_pointer->R_flag = false;
        }
    }
}

void Create_Sheed(struct worksheed *worksheed_pointer)
{
    int size_counter = HPDF_Page_GetHeight(worksheed_pointer->page[0]);
    int task_counter = 0;
    int x;

    srand(time(NULL));

    for(int i = 0; i <= 2; i++)
    {
        while(size_counter >= 50)
        {
            size_counter = size_counter - 50;

            switch(i)
            {
                case 0: x = HPDF_Page_GetWidth(worksheed_pointer->page[0]) - (HPDF_Page_GetWidth(worksheed_pointer->page[0]) * 0.9); break;
                case 1: x = HPDF_Page_GetWidth(worksheed_pointer->page[0]) - (HPDF_Page_GetWidth(worksheed_pointer->page[0]) * 0.6); break;
                case 2: x = HPDF_Page_GetWidth(worksheed_pointer->page[0]) - (HPDF_Page_GetWidth(worksheed_pointer->page[0]) * 0.3); break;
                default: break;
            }

            Create_Random_Task(worksheed_pointer, task_counter);

            Write_Text(worksheed_pointer, x, size_counter, worksheed_pointer->mathTaskArray[task_counter], 0);

            Draw_Line(worksheed_pointer, task_counter, x, size_counter, x, size_counter, 0);

            task_counter++;

        }
        size_counter = HPDF_Page_GetHeight(worksheed_pointer->page[0]);
        printf("i: %d x: %d sc: %d \n", i, x, size_counter);
    }
}

void Create_Random_Task(struct worksheed *worksheed_pointer, int counter)
{
    int max_rand = 1000;

    int first_num = rand() % max_rand;
    int second_num = rand() % max_rand;
    int operand = rand() % 4;
    char task_operand;

    switch(operand)
    {
        case 0: task_operand = '+'; break;
        case 1: task_operand = '-'; break;
        case 2: task_operand = ':'; break;
        case 3: task_operand = '*'; break;
        default: break;
    }

    sprintf(worksheed_pointer->mathTaskArray[counter], "%d %c %d = ", first_num, task_operand, second_num);
}
