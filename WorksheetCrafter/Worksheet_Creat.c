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
*   Creats a sheed with the asked solutions
*/
void Create_Task_Sheed(struct worksheed *worksheed_pointer)
{
    Create_Baseboard(worksheed_pointer, _Tasks);

    int size_counter = HPDF_Page_GetHeight(worksheed_pointer->page[_Tasks]) - worksheed_pointer->baseboard_treashold;
    int task_counter = 0;
    int x;

    srand(time(NULL));

    for(int i = 0; i <= 2; i++)
    {

        while(size_counter >= 50)
        {

            switch(i)
            {
                case 0: x = HPDF_Page_GetWidth(worksheed_pointer->page[0]) - (HPDF_Page_GetWidth(worksheed_pointer->page[0]) * 0.9); break;
                case 1: x = HPDF_Page_GetWidth(worksheed_pointer->page[0]) - (HPDF_Page_GetWidth(worksheed_pointer->page[0]) * 0.6); break;
                case 2: x = HPDF_Page_GetWidth(worksheed_pointer->page[0]) - (HPDF_Page_GetWidth(worksheed_pointer->page[0]) * 0.3); break;
                default: break;
            }

            Create_Random_Task(worksheed_pointer, task_counter);

            Write_Text(worksheed_pointer, x, size_counter, worksheed_pointer->mathTaskArray[task_counter], _Tasks);

            Draw_Solution_Line(worksheed_pointer, worksheed_pointer->mathTaskArray[task_counter], x, size_counter, 60, _Tasks);

            task_counter++;

            size_counter = size_counter - 50;

        }

        size_counter = HPDF_Page_GetHeight(worksheed_pointer->page[_Tasks]) - worksheed_pointer->baseboard_treashold;

    }

}

/*
*   Creas a sheed with the solutions
*/
void Creat_Solution_Sheed(struct worksheed *worksheed_pointer)
{
    Create_Baseboard(worksheed_pointer, _Solutions);

    int size_counter = HPDF_Page_GetHeight(worksheed_pointer->page[_Solutions]) - worksheed_pointer->baseboard_treashold;
    int task_counter = 0;
    int x;

    for(int i = 0; i <= 2; i++)
    {

        while(size_counter >= 50)
        {

            switch(i)
            {
                case 0: x = HPDF_Page_GetWidth(worksheed_pointer->page[_Solutions]) - (HPDF_Page_GetWidth(worksheed_pointer->page[_Solutions]) * 0.9); break;
                case 1: x = HPDF_Page_GetWidth(worksheed_pointer->page[_Solutions]) - (HPDF_Page_GetWidth(worksheed_pointer->page[_Solutions]) * 0.6); break;
                case 2: x = HPDF_Page_GetWidth(worksheed_pointer->page[_Solutions]) - (HPDF_Page_GetWidth(worksheed_pointer->page[_Solutions]) * 0.3); break;
                default: break;
            }

            Write_Text(worksheed_pointer, x, size_counter, worksheed_pointer->mathSolutionArray[task_counter], _Solutions);

            task_counter++;

            size_counter = size_counter - 50;

            //printf("-> %s \n", worksheed_pointer->mathSolutionArray[task_counter]);
        }

        size_counter = HPDF_Page_GetHeight(worksheed_pointer->page[_Solutions]) - worksheed_pointer->baseboard_treashold;

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
                    sprintf(worksheed_pointer->mathTaskArray[counter], "%.4f %c %.4f = ", first_num_float, task_operand, second_num_float);
                    sprintf(worksheed_pointer->mathSolutionArray[counter], "%.4f %c %.4f = %.2f", first_num_float, task_operand, second_num_float, solution);
            break;

            case 5:
                    sprintf(worksheed_pointer->mathTaskArray[counter], "%.5f %c %.5f = ", first_num_float, task_operand, second_num_float);
                    sprintf(worksheed_pointer->mathSolutionArray[counter], "%.5f %c %.5f = %.2f", first_num_float, task_operand, second_num_float, solution);
            break;

            default: break;
        }
    }
}


/*
*   This function creats a baseboard "Kopfzeile" with up to date date and the possibility to handwrite your name
*/
void Create_Baseboard(struct worksheed *worksheed_pointer, int page_counter)
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
*   This Funktion starts the process of generating a math-task-pdf from the beginning till the end
*/
void Start_Pdf(struct worksheed *worksheed_pointer)
{
    worksheed_instanze.pdf = HPDF_New (Error_Handler, NULL);

    //Check this pdf-Doc
    int pdf_status = Check_Pdf(&worksheed_instanze);

    if (pdf_status)
    {
        printf("PDF hat einen Fehler, bzw. konnte nicht erzeugt werden \n");
    }else{
        printf("PDF wurde erfolgreich erzeugt \n");
    }

    //Generating a new page zero
    Setup_Page(worksheed_pointer, _Tasks);

    //Wirte some text
    Create_Task_Sheed(worksheed_pointer);


    //Save pdf and show it witch okular viewer
    Save_Pdf(worksheed_pointer, _Tasks);

    //Neue PDF wird erzeugt
    HPDF_NewDoc(worksheed_pointer->pdf);

    //Generatign a new pdf
    Setup_Page(worksheed_pointer, _Solutions);

    //Creates a Solution  - PDF
    Creat_Solution_Sheed(worksheed_pointer);

    //Saves the Solution - PDF
    Save_Pdf(worksheed_pointer, _Solutions);

    //ends the hole progress with generating a pdf
    HPDF_Free(worksheed_pointer->pdf);
}




