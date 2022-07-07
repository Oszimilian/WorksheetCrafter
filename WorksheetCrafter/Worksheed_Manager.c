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
    int max_rand_1 = 0;
    int max_rand_2 = 0;
    int first_num;
    int second_num;
    float first_num_float;
    float second_num_float;

    char task_operand;
    float solution;
    int operand;
    int operand_check = 0;

    while(!operand_check)
    {
        operand = rand() % 4;

        switch(operand)
        {
            case 0:
                    if (worksheed_pointer->addition_flag) operand_check = true;
                    if (!worksheed_pointer->addition_flag) operand_check = false;
            break;

            case 1:
                    if (worksheed_pointer->subtraction_flag) operand_check = true;
                    if (!worksheed_pointer->subtraction_flag) operand_check = false;
            break;

            case 2:
                    if (worksheed_pointer->multiplication_flag) operand_check = true;
                    if (!worksheed_pointer->multiplication_flag) operand_check = false;
            break;

            case 3:
                    if (worksheed_pointer->division_flag) operand_check = true;
                    if (!worksheed_pointer->division_flag) operand_check = false;
            break;
        }
    }


    if(operand == 0)
    {
        switch(worksheed_pointer->number_addition_digit_1)
        {
            case 1: max_rand_1 = 10; break;
            case 2: max_rand_1 = 100; break;
            case 3: max_rand_1 = 1000; break;
            case 4: max_rand_1 = 10000; break;
            case 5: max_rand_1 = 100000; break;
            default: break;
        }

        switch(worksheed_pointer->number_addition_digit_2)
        {
            case 1: max_rand_2 = 10; break;
            case 2: max_rand_2 = 100; break;
            case 3: max_rand_2 = 1000; break;
            case 4: max_rand_2 = 10000; break;
            case 5: max_rand_2 = 100000; break;
            default: break;
        }
    }
    else if(operand == 1)
    {
        switch(worksheed_pointer->number_subtraction_digit_1)
        {
            case 1: max_rand_1 = 10; break;
            case 2: max_rand_1 = 100; break;
            case 3: max_rand_1 = 1000; break;
            case 4: max_rand_1 = 10000; break;
            case 5: max_rand_1 = 100000; break;
            default: break;
        }

        switch(worksheed_pointer->number_subtraction_digit_2)
        {
            case 1: max_rand_2 = 10; break;
            case 2: max_rand_2 = 100; break;
            case 3: max_rand_2 = 1000; break;
            case 4: max_rand_2 = 10000; break;
            case 5: max_rand_2 = 100000; break;
            default: break;
        }
    }
    else if(operand == 2)
    {
        switch(worksheed_pointer->number_multiplication_digit_1)
        {
            case 1: max_rand_1 = 10; break;
            case 2: max_rand_1 = 100; break;
            case 3: max_rand_1 = 1000; break;
            case 4: max_rand_1 = 10000; break;
            case 5: max_rand_1 = 100000; break;
            default: break;
        }

        switch(worksheed_pointer->number_multiplication_digit_2)
        {
            case 1: max_rand_2 = 10; break;
            case 2: max_rand_2 = 100; break;
            case 3: max_rand_2 = 1000; break;
            case 4: max_rand_2 = 10000; break;
            case 5: max_rand_2 = 100000; break;
            default: break;
        }
    }
    else if(operand == 3)
    {
        switch(worksheed_pointer->number_division_digit_1)
        {
            case 1: max_rand_1 = 10; break;
            case 2: max_rand_1 = 100; break;
            case 3: max_rand_1 = 1000; break;
            case 4: max_rand_1 = 10000; break;
            case 5: max_rand_1 = 100000; break;
            default: break;
        }

        switch(worksheed_pointer->number_division_digit_2)
        {
            case 1: max_rand_2 = 10; break;
            case 2: max_rand_2 = 100; break;
            case 3: max_rand_2 = 1000; break;
            case 4: max_rand_2 = 10000; break;
            case 5: max_rand_2 = 100000; break;
            default: break;
        }

        printf("Ich habe division erkannt \n");
    }

    do
    {
        first_num = rand() % max_rand_1;
        second_num = rand() % max_rand_2;
        first_num_float = (float)first_num;
        second_num_float = (float)second_num;
    }while(max_rand_1 < 0 && max_rand_2 < 0);


    while(1)
    {
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

    if (worksheed_pointer->Z_flag && !worksheed_pointer->R_flag)
    {
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

    if (!worksheed_pointer->Z_flag && worksheed_pointer->R_flag)
    {
        switch(worksheed_pointer->decimal_places)
        {
            case 0: first_num_float *= 1; second_num_float *= 1; break;
            case 1: first_num_float *= 0.1; second_num_float *= 0.1; break;
            case 2: first_num_float *= 0.01; second_num_float *= 0.01; break;
            case 3: first_num_float *= 0.001; second_num_float *= 0.001; break;
            case 4: first_num_float *= 0.0001; second_num_float *= 0.0001; break;
            case 5: first_num_float *= 0.00001;  second_num_float *= 0.00001; break;
            default: break;
        }

        switch(operand)
        {
            case 0: task_operand = '+'; solution = first_num_float + second_num_float; break;
            case 1: task_operand = '-'; solution = first_num_float - second_num_float; break;
            case 2: task_operand = '*'; solution = first_num_float * second_num_float; break;
            case 3: task_operand = ':'; solution = first_num_float / second_num_float; break;
            default: break;
        }

        switch(worksheed_pointer->decimal_places)
        {
            case 0:
                    sprintf(worksheed_pointer->mathTaskArray[counter], "%.0f %c %.0f = ", first_num_float, task_operand, second_num_float);
                    sprintf(worksheed_pointer->mathSolutionArray[counter], "%.0f %c %.0f = %.2f", first_num_float, task_operand, second_num_float, solution);
            break;

            case 1:
                    sprintf(worksheed_pointer->mathTaskArray[counter], "%.1f %c %.1f = ", first_num_float, task_operand, second_num_float);
                    sprintf(worksheed_pointer->mathSolutionArray[counter], "%.1f %c %.1f = %.2f", first_num_float, task_operand, second_num_float, solution);
            break;

            case 2:
                    sprintf(worksheed_pointer->mathTaskArray[counter], "%.2f %c %.2f = ", first_num_float, task_operand, second_num_float);
                    sprintf(worksheed_pointer->mathSolutionArray[counter], "%.2f %c %.2f = %.2f", first_num_float, task_operand, second_num_float, solution);
            break;

            case 3:
                    sprintf(worksheed_pointer->mathTaskArray[counter], "%.3f %c %.3f = ", first_num_float, task_operand, second_num_float);
                    sprintf(worksheed_pointer->mathSolutionArray[counter], "%.3f %c %.3f = %.2f", first_num_float, task_operand, second_num_float, solution);
            break;

            case 4:
                    sprintf(worksheed_pointer->mathTaskArray[counter], "%.4f %c %.4f = ", first_num, task_operand, second_num_float);
                    sprintf(worksheed_pointer->mathSolutionArray[counter], "%.4f %c %.4f = %.2f", first_num, task_operand, second_num_float, solution);
            break;

            case 5:
                    sprintf(worksheed_pointer->mathTaskArray[counter], "%.5f %c %.5f = ", first_num_float, task_operand, second_num_float);
                    sprintf(worksheed_pointer->mathSolutionArray[counter], "%.5f %c %.5f = %.2f", first_num_float, task_operand, second_num_float, solution);
            break;

            default: break;
        }
    }
}

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
