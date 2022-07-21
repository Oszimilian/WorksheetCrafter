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

    else if(setting == _Subtraction)
    {
        if (worksheed_pointer->WCO_Worksheet_subtractionEnableFlag)
        {
            worksheed_pointer->WCO_Worksheet_subtractionEnableFlag = false;
        }else{
            worksheed_pointer->WCO_Worksheet_subtractionEnableFlag = true;
        }
    }

    else if(setting == _Multiplication)
    {
        if (worksheed_pointer->WCO_Worksheet_multiplicationEnableFlag)
        {
            worksheed_pointer->WCO_Worksheet_multiplicationEnableFlag = false;
        }else{
            worksheed_pointer->WCO_Worksheet_multiplicationEnableFlag = true;
        }
    }

    else if(setting == _Division)
    {
        if (worksheed_pointer->WCO_Worksheet_divisonEnableFlag)
        {
            worksheed_pointer->WCO_Worksheet_divisonEnableFlag = false;
        }else{
            worksheed_pointer->WCO_Worksheet_divisonEnableFlag = true;
        }
    }

    else if(setting == _Zahlentyp)
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

    else if(setting == _Baseboard)
    {
        if (worksheed_pointer->WCO_Worksheet_baseboardEnableFlag)
        {
            worksheed_pointer->WCO_Worksheet_baseboardEnableFlag = false;
        }else{
            worksheed_pointer->WCO_Worksheet_baseboardEnableFlag = true;
        }
    }

    worksheed_pointer->WCO_Background_updateWorksheetSettingsComplete = false;
}

void WCO_Worksheet_Adjust_ChangeWorksheetValues(struct worksheed *worksheed_pointer, int count, int value)
{
    switch(count)
    {
        case _Addition_Min: worksheed_pointer->WCO_Worksheet_number1_additionDigit = value;  break;
        case _Addition_Max: worksheed_pointer->WCO_Worksheet_number2_additionDigit = value; break;
        case _Subtraction_Min: worksheed_pointer->WCO_Worksheet_number1_subtractionDigit = value; break;
        case _Subtraction_Max: worksheed_pointer->WCO_Worksheet_number2_subtractionDigit = value; break;
        case _Multiplication_Min: worksheed_pointer->WCO_Worksheet_number1_multiplicationDigit = value; break;
        case _Multiplication_Max: worksheed_pointer->WCO_Worksheet_number2_multiplicationDigit = value; break;
        case _Division_Min: worksheed_pointer->WCO_Worksheet_number1_divisionDigit = value; break;
        case _Division_Max: worksheed_pointer->WCO_Worksheet_number2_divisionDigit = value; break;

        case _Addition_DecimalPlaces: worksheed_pointer->WCO_Worksheet_additionDecimalPlaces = value; break;
        case _Subtraction_DecimalPlaces: worksheed_pointer->WCO_Worksheet_subtractionDecimalPlaces = value; break;
        case _Multiplication_DecimalPlaces: worksheed_pointer->WCO_Worksheet_multiplicationDecimalPlaces = value; break;
        case _Division_DecimalPlaces: worksheed_pointer->WCO_Worksheet_divisionDecimalPlaces = value; break;

       default: break;
    }

    worksheed_pointer->WCO_Background_updateDecimalPlacesComplete = false;
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

    worksheed_pointer->WCO_Worksheet_baseboardEnableFlag = true;


    worksheed_pointer->WCO_Worksheet_number1_additionDigit = 3;
    worksheed_pointer->WCO_Worksheet_number2_additionDigit = 3;
    worksheed_pointer->WCO_Worksheet_number1_subtractionDigit = 3;
    worksheed_pointer->WCO_Worksheet_number2_subtractionDigit = 3;
    worksheed_pointer->WCO_Worksheet_number1_multiplicationDigit = 3;
    worksheed_pointer->WCO_Worksheet_number2_multiplicationDigit = 3;
    worksheed_pointer->WCO_Worksheet_number1_divisionDigit = 3;
    worksheed_pointer->WCO_Worksheet_number2_divisionDigit = 3;

    worksheed_pointer->WCO_Worksheet_additionDecimalPlaces = 0;
    worksheed_pointer->WCO_Worksheet_subtractionDecimalPlaces = 0;
    worksheed_pointer->WCO_Worksheet_multiplicationDecimalPlaces = 0;
    worksheed_pointer->WCO_Worksheet_divisionDecimalPlaces = 0;


    //worksheed_pointer->WCO_Worksheet_decimalPlaces = 0;

    worksheed_pointer->WCO_Background_updateDecimalPlacesComplete = false;
    worksheed_pointer->WCO_Background_updateWorksheetSettingsComplete = false;

    worksheed_pointer->WCO_GUI_controllCreatButtonFlag = true;

    return 1;
}



