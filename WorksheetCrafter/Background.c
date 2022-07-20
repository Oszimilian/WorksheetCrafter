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




void *Handle_Worksheed()
{
    while(1)
    {
        while(!worksheed_instanze.init_complete);

        Update_Decimal_Places(&worksheed_instanze);

        Update_Number_Type(&worksheed_instanze);
    }
}

void Update_Decimal_Places(struct worksheed *worksheed_pointer)
{
    if (!worksheed_pointer->update_decimal_places)
    {
        int max_range;
        int min_range = 1;
        if(worksheed_pointer->number_multiplication_digit_1 < worksheed_pointer->number_multiplication_digit_2)
        {
            max_range = worksheed_pointer->number_multiplication_digit_1;
        }else{
            max_range = worksheed_pointer->number_multiplication_digit_2;
        }

        gtk_spin_button_set_range(GTK_SPIN_BUTTON(MySpinButton1), (double)min_range, (double)max_range);

        worksheed_instanze.update_decimal_places = true;
    }
}

void Update_Number_Type(struct worksheed *worksheed_pointer)
{
    if (!worksheed_pointer->update_number_type)
    {
        if (worksheed_pointer->Z_flag && !worksheed_pointer->R_flag)
        {
            gtk_widget_hide(MySpinButton1);
        }
        if (!worksheed_pointer->Z_flag && worksheed_pointer->R_flag)
        {
            gtk_widget_show(MySpinButton1);
        }

        worksheed_pointer->update_number_type = true;
    }
}
