#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <time.h>
#include <setjmp.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
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
