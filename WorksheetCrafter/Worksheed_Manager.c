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

    if(setting == _Baseboard)
    {
        if (worksheed_pointer->baseboard_flag)
        {
            worksheed_pointer->baseboard_flag = false;
        }else{
            worksheed_pointer->baseboard_flag = true;
        }
    }
}

/*
*   This function creats a baseboard "Kopfzeile" with up to date date and the possibility to handwrite your name
*/
int Create_Baseboard(struct worksheed *worksheed_pointer, int page_counter)
{
    if (worksheed_pointer->baseboard_flag)
    {
        int startx1 = HPDF_Page_GetWidth(worksheed_pointer->page[page_counter]) - (HPDF_Page_GetWidth(worksheed_pointer->page[page_counter]) * 0.9);
        int startx2 = HPDF_Page_GetWidth(worksheed_pointer->page[page_counter]) - (HPDF_Page_GetWidth(worksheed_pointer->page[page_counter]) * 0.5);
        int startx3 = HPDF_Page_GetWidth(worksheed_pointer->page[page_counter]) - (HPDF_Page_GetWidth(worksheed_pointer->page[page_counter]) * 0.3);

        worksheed_pointer->baseboard_treashold = 150;

        Write_Text(worksheed_pointer, startx1, 775, "Name:", page_counter);
        Draw_Solution_Line(worksheed_pointer, "Name:  ", startx1, 770, 150, page_counter);

        if(page_counter == _Tasks)
        {
            Write_Text(worksheed_pointer, startx2, 775, "AUFGABEN", page_counter);
        }else{
            Write_Text(worksheed_pointer, startx2, 775, "SOLUTION", page_counter);
        }

        time_t now;
        time(&now);
        struct tm *tm_instance;
        tm_instance = localtime(&now);
        char tmp[20];
        sprintf(tmp, "Datum: %d.%d.%d", tm_instance->tm_mday, tm_instance->tm_mon + 1, tm_instance->tm_year + 1900);
        Write_Text(worksheed_pointer, startx3, 775, tmp, page_counter);

        Draw_Line(worksheed_pointer, 50, 750, HPDF_Page_GetWidth(worksheed_pointer->page[page_counter]) - 50, 750, page_counter);

    }else{
        worksheed_pointer->baseboard_treashold = 0;
    }
}

/*
*   This function creats random math task and writes it into a struct defined string
*/
void Create_Random_Task(struct worksheed *worksheed_pointer, int counter)
{
    int max_rand = 1000;

    int first_num = rand() % max_rand;
    int second_num = rand() % max_rand;
    float first_num_float = (float)first_num;
    float second_num_float = (float)second_num;

    char task_operand;
    float solution;

    int operand;

    while(1)
    {
        operand = rand() % 4;

        if (operand == 0 && worksheed_pointer->addition_flag) break;
        if (operand == 1 && worksheed_pointer->subtraction_flag) break;
        if (operand == 2 && worksheed_pointer->multiplication_flag) break;
        if (operand == 3 && worksheed_pointer->division_flag) break;

        if (!worksheed_pointer->addition_flag && !worksheed_pointer->subtraction_flag && !worksheed_pointer->multiplication_flag && !worksheed_pointer->division_flag)
        {
            gtk_label_set_text(MyLabel1, "Sie müssen auf jeden Fall einen Operator auswählen!");
            Close_PDF(&worksheed_instanze);

            while(worksheed_pointer->addition_flag || worksheed_pointer->subtraction_flag || worksheed_pointer->multiplication_flag || worksheed_pointer->division_flag) {}
            break;
        }
    }

    switch(operand)
    {
        case 0: task_operand = '+'; solution = first_num_float + second_num_float; break;
        case 1: task_operand = '-'; solution = first_num_float - second_num_float; break;
        case 2: task_operand = '*'; solution = first_num_float * second_num_float; break;
        case 3: task_operand = ':'; solution = first_num_float / second_num_float; break;
        default: break;
    }

    sprintf(worksheed_pointer->mathTaskArray[counter], "%d %c %d = ", first_num, task_operand, second_num);

    sprintf(worksheed_pointer->mathSolutionArray[counter], "%d %c %d = %.2f", first_num, task_operand, second_num, solution);
}
