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
        while(!worksheed_instanze.init_complete);

        WCO_Background_Controll_DecimalPlaces(&worksheed_instanze);

        WCO_Background_Controll_Visibility(&worksheed_instanze);
    }
}

void WCO_Background_Controll_DecimalPlaces(struct worksheed *worksheed_pointer)
{
    if (!worksheed_pointer->update_WCO_Worksheet_decimalPlaces)
    {
        int max_range;
        int min_range = 1;
        if(worksheed_pointer->WCO_Worksheet_number1_multiplicationDigit < worksheed_pointer->WCO_Worksheet_number2_multiplicationDigit)
        {
            max_range = worksheed_pointer->WCO_Worksheet_number1_multiplicationDigit;
        }else{
            max_range = worksheed_pointer->WCO_Worksheet_number2_multiplicationDigit;
        }

        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MySpinButton1), (double)min_range, (double)max_range);

        worksheed_instanze.update_WCO_Worksheet_decimalPlaces = true;
    }
}

void WCO_Background_Controll_Visibility(struct worksheed *worksheed_pointer)
{
    if (!worksheed_pointer->update_number_type)
    {
        if (worksheed_pointer->WCO_Worksheet_zNumberEnableFlag && !worksheed_pointer->WCO_Worksheet_rNumberEnableFlag)
        {
            gtk_widget_hide(MySpinButton1);
        }
        if (!worksheed_pointer->WCO_Worksheet_zNumberEnableFlag && worksheed_pointer->WCO_Worksheet_rNumberEnableFlag)
        {
            gtk_widget_show(MySpinButton1);
        }

        worksheed_pointer->update_number_type = true;
    }
}
