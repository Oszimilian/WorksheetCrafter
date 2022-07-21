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



void *WCO_Background_Handle()
{
    while(1)
    {
        while(!worksheed_instanze.WCO_Worksheet_initWorksheetComplete);

        WCO_Background_Controll_DecimalPlaces(&worksheed_instanze);

        WCO_Background_Controll_Visibility(&worksheed_instanze);
    }
}

/**********************************************************************************************************************************************************************************/
/*
*   function is responsible for looking after logic failures
*   If one of the number digits of a task is lower as as the nachkommastellen, that makes no sense. This function prevent this
*/
void WCO_Background_Controll_DecimalPlaces(struct worksheed *worksheed_pointer)
{
    if (!worksheed_pointer->WCO_Background_updateDecimalPlacesComplete)
    {
        int additionDigitRange;
        int subtractionDigitRange;
        int multiplicationDigitRange;
        int divisionDigitRange;
        int min_range = 0;

        if (worksheed_pointer->WCO_Worksheet_number1_additionDigit < worksheed_pointer->WCO_Worksheet_number2_additionDigit)
        {
            additionDigitRange = worksheed_pointer->WCO_Worksheet_number1_additionDigit;
        }else{
            additionDigitRange = worksheed_pointer->WCO_Worksheet_number2_additionDigit;
        }

        if (worksheed_pointer->WCO_Worksheet_number1_subtractionDigit < worksheed_pointer->WCO_Worksheet_number2_subtractionDigit)
        {
            subtractionDigitRange = worksheed_pointer->WCO_Worksheet_number1_subtractionDigit;
        }else{
            subtractionDigitRange = worksheed_pointer->WCO_Worksheet_number2_subtractionDigit;
        }

        if (worksheed_pointer->WCO_Worksheet_number1_multiplicationDigit < worksheed_pointer->WCO_Worksheet_number2_multiplicationDigit)
        {
            multiplicationDigitRange = worksheed_pointer->WCO_Worksheet_number1_multiplicationDigit;
        }else{
            multiplicationDigitRange = worksheed_pointer->WCO_Worksheet_number2_multiplicationDigit;
        }

        if (worksheed_pointer->WCO_Worksheet_number1_divisionDigit < worksheed_pointer->WCO_Worksheet_number2_divisionDigit)
        {
            divisionDigitRange = worksheed_pointer->WCO_Worksheet_number1_divisionDigit;
        }else{
            divisionDigitRange = worksheed_pointer->WCO_Worksheet_number2_divisionDigit;
        }


        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MySpinButton10), (double)min_range, (double)additionDigitRange);
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MySpinButton11), (double)min_range, (double)subtractionDigitRange);
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MySpinButton12), (double)min_range, (double)multiplicationDigitRange);
        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MySpinButton13), (double)min_range, (double)divisionDigitRange);

        worksheed_instanze.WCO_Background_updateDecimalPlacesComplete = true;
    }
}

/*
*   This function is resbonsible for the visibility of specific buttons
*   If a button with a systemchange function is pressed this funcition locks at the new conditions
*/
void WCO_Background_Controll_Visibility(struct worksheed *worksheed_pointer)
{
    if (!worksheed_pointer->WCO_Background_updateWorksheetSettingsComplete)
    {
        if (worksheed_pointer->WCO_Worksheet_zNumberEnableFlag && !worksheed_pointer->WCO_Worksheet_rNumberEnableFlag)
        {
            gtk_widget_hide(MySpinButton1);
        }
        if (!worksheed_pointer->WCO_Worksheet_zNumberEnableFlag && worksheed_pointer->WCO_Worksheet_rNumberEnableFlag)
        {
            gtk_widget_show(MySpinButton1);
        }

        if(worksheed_pointer->WCO_Worksheet_additionEnableFlag)
        {
            gtk_widget_show(MySpinButton2);
            gtk_widget_show(MySpinButton8);
            gtk_widget_show(MySpinButton10);
            gtk_widget_show(MyLabel2);
        }else{
            gtk_widget_hide(MySpinButton2);
            gtk_widget_hide(MySpinButton8);
            gtk_widget_hide(MySpinButton10);
            gtk_widget_hide(MyLabel2);
        }

        if(worksheed_pointer->WCO_Worksheet_subtractionEnableFlag)
        {
            gtk_widget_show(MySpinButton5);
            gtk_widget_show(MySpinButton9);
            gtk_widget_show(MySpinButton11);
            gtk_widget_show(MyLabel3);
        }else{
            gtk_widget_hide(MySpinButton5);
            gtk_widget_hide(MySpinButton9);
            gtk_widget_hide(MySpinButton11);
            gtk_widget_hide(MyLabel3);
        }

        if(worksheed_pointer->WCO_Worksheet_multiplicationEnableFlag)
        {
            gtk_widget_show(MySpinButton3);
            gtk_widget_show(MySpinButton4);
            gtk_widget_show(MySpinButton12);
            gtk_widget_show(MyLabel4);
        }else{
            gtk_widget_hide(MySpinButton3);
            gtk_widget_hide(MySpinButton4);
            gtk_widget_hide(MySpinButton12);
            gtk_widget_hide(MyLabel4);
        }

        if(worksheed_pointer->WCO_Worksheet_divisonEnableFlag)
        {
            gtk_widget_show(MySpinButton6);
            gtk_widget_show(MySpinButton7);
            gtk_widget_show(MySpinButton13);
            gtk_widget_show(MyLabel5);
        }else{
            gtk_widget_hide(MySpinButton6);
            gtk_widget_hide(MySpinButton7);
            gtk_widget_hide(MySpinButton13);
            gtk_widget_hide(MyLabel5);
        }

        if( !worksheed_pointer->WCO_Worksheet_additionEnableFlag &&
            !worksheed_pointer->WCO_Worksheet_subtractionEnableFlag &&
            !worksheed_pointer->WCO_Worksheet_multiplicationEnableFlag&&
            !worksheed_pointer->WCO_Worksheet_divisonEnableFlag)
        {
            worksheed_pointer->WCO_GUI_controllCreatButtonFlag = false;
            gtk_widget_hide(MyButton1);
            WCO_GUI_ClosePDFViewer(&worksheed_instanze);
        }else{
            worksheed_pointer->WCO_GUI_controllCreatButtonFlag = true;
            gtk_widget_show(MyButton1);
        }

        worksheed_pointer->WCO_Background_updateWorksheetSettingsComplete = true;
    }
}
