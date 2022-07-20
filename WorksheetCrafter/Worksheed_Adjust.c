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
void WCO_Worksheet_Adjust_ChangeWorksheetSettings(struct worksheed *worksheed_pointer, int setting)
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
*   Initialise the settings for the math-PDF
*/
int WCO_Worksheet_Adjust_InitWorksheetSettings(struct worksheed *worksheed_pointer)
{
    worksheed_pointer->addition_flag = true;
    worksheed_pointer->subtraction_flag = true;
    worksheed_pointer->multiplication_flag = true;
    worksheed_pointer->division_flag = true;

    worksheed_pointer->Z_flag = true;
    worksheed_pointer->R_flag = false;

    worksheed_pointer->baseboard_flag = true;

    worksheed_pointer->number_range = 100;
    worksheed_pointer->number_addition_digit_1 = 3;
    worksheed_pointer->number_addition_digit_2 = 3;
    worksheed_pointer->number_subtraction_digit_1 = 3;
    worksheed_pointer->number_subtraction_digit_2 = 3;
    worksheed_pointer->number_multiplication_digit_1 = 3;
    worksheed_pointer->number_multiplication_digit_2 = 3;
    worksheed_pointer->number_division_digit_1 = 3;
    worksheed_pointer->number_division_digit_2 = 3;
    worksheed_pointer->decimal_places = 0;

    worksheed_pointer->update_decimal_places = false;
    worksheed_pointer->update_number_type = false;

    return 1;
}



