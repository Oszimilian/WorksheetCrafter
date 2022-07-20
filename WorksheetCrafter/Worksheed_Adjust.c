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
        if (worksheed_pointer->WCO_Worksheet_additionEnableFlag)
        {
            worksheed_pointer->WCO_Worksheet_additionEnableFlag = false;
        }else{
            worksheed_pointer->WCO_Worksheet_additionEnableFlag = true;
        }
    }

    if(setting == _Subtraction)
    {
        if (worksheed_pointer->WCO_Worksheet_subtractionEnableFlag)
        {
            worksheed_pointer->WCO_Worksheet_subtractionEnableFlag = false;
        }else{
            worksheed_pointer->WCO_Worksheet_subtractionEnableFlag = true;
        }
    }

    if(setting == _Multiplication)
    {
        if (worksheed_pointer->WCO_Worksheet_multiplicationEnableFlag)
        {
            worksheed_pointer->WCO_Worksheet_multiplicationEnableFlag = false;
        }else{
            worksheed_pointer->WCO_Worksheet_multiplicationEnableFlag = true;
        }
    }

    if(setting == _Division)
    {
        if (worksheed_pointer->WCO_Worksheet_divisonEnableFlag)
        {
            worksheed_pointer->WCO_Worksheet_divisonEnableFlag = false;
        }else{
            worksheed_pointer->WCO_Worksheet_divisonEnableFlag = true;
        }
    }

    if(setting == _Zahlentyp)
    {
        if (worksheed_pointer->WCO_Worksheet_zNumberEnableFlag && !worksheed_pointer->WCO_Worksheet_rNumberEnableFlag)
        {
            worksheed_pointer->WCO_Worksheet_zNumberEnableFlag = false;
            worksheed_pointer->WCO_Worksheet_rNumberEnableFlag = true;
        }else{
            worksheed_pointer->WCO_Worksheet_zNumberEnableFlag = true;
            worksheed_pointer->WCO_Worksheet_rNumberEnableFlag = false;
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
    worksheed_pointer->WCO_Worksheet_additionEnableFlag = true;
    worksheed_pointer->WCO_Worksheet_subtractionEnableFlag = true;
    worksheed_pointer->WCO_Worksheet_multiplicationEnableFlag = true;
    worksheed_pointer->WCO_Worksheet_divisonEnableFlag = true;

    worksheed_pointer->WCO_Worksheet_zNumberEnableFlag = true;
    worksheed_pointer->WCO_Worksheet_rNumberEnableFlag = false;

    worksheed_pointer->baseboard_flag = true;


    worksheed_pointer->WCO_Worksheet_number1_additionDigit = 3;
    worksheed_pointer->WCO_Worksheet_number2_additionDigit = 3;
    worksheed_pointer->WCO_Worksheet_number1_subtractionDigit = 3;
    worksheed_pointer->WCO_Worksheet_number2_subtractionDigit = 3;
    worksheed_pointer->WCO_Worksheet_number1_multiplicationDigit = 3;
    worksheed_pointer->WCO_Worksheet_number2_multiplicationDigit = 3;
    worksheed_pointer->WCO_Worksheet_number1_divisionDigit = 3;
    worksheed_pointer->WCO_Worksheet_number2_divisionDigit = 3;
    worksheed_pointer->WCO_Worksheet_decimalPlaces = 0;

    worksheed_pointer->update_WCO_Worksheet_decimalPlaces = false;
    worksheed_pointer->update_number_type = false;

    return 1;
}



