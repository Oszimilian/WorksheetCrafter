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
*   This Funktion starts the process of generating a math-task-pdf from the beginning till the end
*/
void WCO_Worksheet_Create_Start(struct worksheed *worksheed_pointer)
{
    worksheed_instanze.pdf = HPDF_New (Error_Handler, NULL);

    //Check this pdf-Doc
    int pdf_status = WCO_PDF_Check(&worksheed_instanze);

    if (pdf_status)
    {
        printf("PDF hat einen Fehler, bzw. konnte nicht erzeugt werden \n");
    }else{
        printf("PDF wurde erfolgreich erzeugt \n");
    }

    //Generating a new page zero
    WCO_PDF_SetupPage(worksheed_pointer, _Tasks);

    //Wirte some text
    WCO_Worksheet_Creat_TaskSheet(worksheed_pointer);


    //Save pdf and show it witch okular viewer
    WCO_PDF_SavePDF(worksheed_pointer, _Tasks);

    //Neue PDF wird erzeugt
    HPDF_NewDoc(worksheed_pointer->pdf);

    //Generatign a new pdf
    WCO_PDF_SetupPage(worksheed_pointer, _Solutions);

    //Creates a Solution  - PDF
    WCO_Worksheet_Create_SolutionSheed(worksheed_pointer);

    //Saves the Solution - PDF
    WCO_PDF_SavePDF(worksheed_pointer, _Solutions);

    //ends the hole progress with generating a pdf
    HPDF_Free(worksheed_pointer->pdf);
}

/*
*   Creats a sheed with the asked solutions
*/
void WCO_Worksheet_Creat_TaskSheet(struct worksheed *worksheed_pointer)
{
    WCO_Worksheet_Creat_Baseboard(worksheed_pointer, _Tasks);

    int size_counter = HPDF_Page_GetHeight(worksheed_pointer->page[_Tasks]) - worksheed_pointer->WCO_Worksheet_baseboardThreashold;
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

            WCO_Worksheet_Create_RandomTask(worksheed_pointer, task_counter);

            WCO_PDF_WriteText(worksheed_pointer, x, size_counter, worksheed_pointer->WCO_Worksheet_taskArray[task_counter], _Tasks);

            WCO_PDF_DrawSolutionLine(worksheed_pointer, worksheed_pointer->WCO_Worksheet_taskArray[task_counter], x, size_counter, 60, _Tasks);

            task_counter++;

            size_counter = size_counter - 50;

        }

        size_counter = HPDF_Page_GetHeight(worksheed_pointer->page[_Tasks]) - worksheed_pointer->WCO_Worksheet_baseboardThreashold;

    }

}

/*
*   Creas a sheed with the solutions
*/
void WCO_Worksheet_Create_SolutionSheed(struct worksheed *worksheed_pointer)
{
    WCO_Worksheet_Creat_Baseboard(worksheed_pointer, _Solutions);

    int size_counter = HPDF_Page_GetHeight(worksheed_pointer->page[_Solutions]) - worksheed_pointer->WCO_Worksheet_baseboardThreashold;
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

            WCO_PDF_WriteText(worksheed_pointer, x, size_counter, worksheed_pointer->WCO_Worksheet_solutionArray[task_counter], _Solutions);

            task_counter++;

            size_counter = size_counter - 50;

            //printf("-> %s \n", worksheed_pointer->WCO_Worksheet_solutionArray[task_counter]);
        }

        size_counter = HPDF_Page_GetHeight(worksheed_pointer->page[_Solutions]) - worksheed_pointer->WCO_Worksheet_baseboardThreashold;

    }

}


/*
*   This function creats random math task and writes it into a struct defined string
*/
void WCO_Worksheet_Create_RandomTask(struct worksheed *worksheed_pointer, int counter)
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

    /*
    *   Generate a operand
    *   If All OperandFlags are false this while-loop will be skipped
    *   If one, two, or three Operand Flags are false this will-loop will generate random typs of operands untill a not denied one appears
    */
    while(!operand_check)
    {
        operand = rand() % 4;

        if( !worksheed_pointer->WCO_Worksheet_additionEnableFlag &&
            !worksheed_pointer->WCO_Worksheet_subtractionEnableFlag &&
            !worksheed_pointer->WCO_Worksheet_multiplicationEnableFlag&&
            !worksheed_pointer->WCO_Worksheet_divisonEnableFlag) break;

        switch(operand)
        {
            case 0:
                    if (worksheed_pointer->WCO_Worksheet_additionEnableFlag) operand_check = true;
                    if (!worksheed_pointer->WCO_Worksheet_additionEnableFlag) operand_check = false;
            break;

            case 1:
                    if (worksheed_pointer->WCO_Worksheet_subtractionEnableFlag) operand_check = true;
                    if (!worksheed_pointer->WCO_Worksheet_subtractionEnableFlag) operand_check = false;
            break;

            case 2:
                    if (worksheed_pointer->WCO_Worksheet_multiplicationEnableFlag) operand_check = true;
                    if (!worksheed_pointer->WCO_Worksheet_multiplicationEnableFlag) operand_check = false;
            break;

            case 3:
                    if (worksheed_pointer->WCO_Worksheet_divisonEnableFlag) operand_check = true;
                    if (!worksheed_pointer->WCO_Worksheet_divisonEnableFlag) operand_check = false;
            break;

            default: break;
        }
    }

    /*
    *   This part
    */
    int number1Digit;
    int number2Digit;

    switch(operand)
    {
        case 0: number1Digit = worksheed_pointer->WCO_Worksheet_number1_additionDigit;
                number2Digit = worksheed_pointer->WCO_Worksheet_number2_additionDigit;
        break;

        case 1: number1Digit = worksheed_pointer->WCO_Worksheet_number1_subtractionDigit;
                number2Digit = worksheed_pointer->WCO_Worksheet_number2_subtractionDigit;
        break;

        case 2: number1Digit = worksheed_pointer->WCO_Worksheet_number1_multiplicationDigit;
                number2Digit = worksheed_pointer->WCO_Worksheet_number2_multiplicationDigit;
        break;

        case 3: number1Digit = worksheed_pointer->WCO_Worksheet_number1_divisionDigit;
                number2Digit = worksheed_pointer->WCO_Worksheet_number2_divisionDigit;
        break;

        default: break;
    }

    switch(number1Digit)
    {
        case 1: max_rand_1 = 10; break;
        case 2: max_rand_1 = 100; break;
        case 3: max_rand_1 = 1000; break;
        case 4: max_rand_1 = 10000; break;
        case 5: max_rand_1 = 100000; break;
        default: break;
    }

    switch(number2Digit)
    {
        case 1: max_rand_2 = 10; break;
        case 2: max_rand_2 = 100; break;
        case 3: max_rand_2 = 1000; break;
        case 4: max_rand_2 = 10000; break;
        case 5: max_rand_2 = 100000; break;
        default: break;
    }

    /*
    *   This part generates random numbers until the generated number is higher than zero
    *   Secondly the int number is casted into float datatyp
    */
    do
    {
        first_num = rand() % max_rand_1;
        second_num = rand() % max_rand_2;
        first_num_float = (float)first_num;
        second_num_float = (float)second_num;
    }while(max_rand_1 < 0 && max_rand_2 < 0);

    /*
    *   If all operationflags are disabled the creat button disappears and a warning message appears
    */
    while(!worksheed_pointer->WCO_GUI_controllCreatButtonFlag)
    {
        gtk_label_set_text(MyLabel1, "Sie müssen auf jeden Fall einen Operator auswählen!");
    }

    /*
    *   stores the DecimalPlaces dependent of the operand into a local var "localDecimalPlaces"
    */
    int localDecimalPlaces;
    switch(operand)
    {
        case 0: localDecimalPlaces = worksheed_pointer->WCO_Worksheet_additionDecimalPlaces; break;
        case 1: localDecimalPlaces = worksheed_pointer->WCO_Worksheet_subtractionDecimalPlaces; break;
        case 2: localDecimalPlaces = worksheed_pointer->WCO_Worksheet_multiplicationDecimalPlaces; break;
        case 3: localDecimalPlaces = worksheed_pointer->WCO_Worksheet_divisionDecimalPlaces; break;
    }

    /*
    *   if the current DecimalPlaces count is zero the task is print as a integer
    *   Otherwise the task is print as a float with the demanded decimal place
    */
    if (localDecimalPlaces == 0)
    {
        switch(operand)
        {
            case 0: task_operand = '+'; solution = first_num_float + second_num_float; break;
            case 1: task_operand = '-'; solution = first_num_float - second_num_float; break;
            case 2: task_operand = '*'; solution = first_num_float * second_num_float; break;
            case 3: task_operand = ':'; solution = first_num_float / second_num_float; break;
            default: break;
        }

        sprintf(worksheed_pointer->WCO_Worksheet_taskArray[counter], "%d %c %d = ", first_num, task_operand, second_num);

        sprintf(worksheed_pointer->WCO_Worksheet_solutionArray[counter], "%d %c %d = %.2f", first_num, task_operand, second_num, solution);

    }else{

        switch(localDecimalPlaces)
        {
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

        switch(localDecimalPlaces)
        {
            case 1:
                    sprintf(worksheed_pointer->WCO_Worksheet_taskArray[counter], "%.1f %c %.1f = ", first_num_float, task_operand, second_num_float);
                    sprintf(worksheed_pointer->WCO_Worksheet_solutionArray[counter], "%.1f %c %.1f = %.2f", first_num_float, task_operand, second_num_float, solution);
            break;

            case 2:
                    sprintf(worksheed_pointer->WCO_Worksheet_taskArray[counter], "%.2f %c %.2f = ", first_num_float, task_operand, second_num_float);
                    sprintf(worksheed_pointer->WCO_Worksheet_solutionArray[counter], "%.2f %c %.2f = %.2f", first_num_float, task_operand, second_num_float, solution);
            break;

            case 3:
                    sprintf(worksheed_pointer->WCO_Worksheet_taskArray[counter], "%.3f %c %.3f = ", first_num_float, task_operand, second_num_float);
                    sprintf(worksheed_pointer->WCO_Worksheet_solutionArray[counter], "%.3f %c %.3f = %.2f", first_num_float, task_operand, second_num_float, solution);
            break;

            case 4:
                    sprintf(worksheed_pointer->WCO_Worksheet_taskArray[counter], "%.4f %c %.4f = ", first_num_float, task_operand, second_num_float);
                    sprintf(worksheed_pointer->WCO_Worksheet_solutionArray[counter], "%.4f %c %.4f = %.2f", first_num_float, task_operand, second_num_float, solution);
            break;

            case 5:
                    sprintf(worksheed_pointer->WCO_Worksheet_taskArray[counter], "%.5f %c %.5f = ", first_num_float, task_operand, second_num_float);
                    sprintf(worksheed_pointer->WCO_Worksheet_solutionArray[counter], "%.5f %c %.5f = %.2f", first_num_float, task_operand, second_num_float, solution);
            break;

            default: break;
        }
    }
}


/*
*   This function creats a baseboard "Kopfzeile" with up to date date and the possibility to handwrite your name
*/
void WCO_Worksheet_Creat_Baseboard(struct worksheed *worksheed_pointer, int page_counter)
{
    if (worksheed_pointer->WCO_Worksheet_baseboardEnableFlag)
    {
        int startx1 = HPDF_Page_GetWidth(worksheed_pointer->page[page_counter]) - (HPDF_Page_GetWidth(worksheed_pointer->page[page_counter]) * 0.9);
        int startx2 = HPDF_Page_GetWidth(worksheed_pointer->page[page_counter]) - (HPDF_Page_GetWidth(worksheed_pointer->page[page_counter]) * 0.5);
        int startx3 = HPDF_Page_GetWidth(worksheed_pointer->page[page_counter]) - (HPDF_Page_GetWidth(worksheed_pointer->page[page_counter]) * 0.3);

        worksheed_pointer->WCO_Worksheet_baseboardThreashold = 150;

        WCO_PDF_WriteText(worksheed_pointer, startx1, 775, "Name:", page_counter);
        WCO_PDF_DrawSolutionLine(worksheed_pointer, "Name:  ", startx1, 770, 150, page_counter);

        if(page_counter == _Tasks)
        {
            WCO_PDF_WriteText(worksheed_pointer, startx2, 775, "AUFGABEN", page_counter);
        }else{
            WCO_PDF_WriteText(worksheed_pointer, startx2, 775, "SOLUTION", page_counter);
        }

        time_t now;
        time(&now);
        struct tm *tm_instance;
        tm_instance = localtime(&now);
        char tmp[20];
        sprintf(tmp, "Datum: %d.%d.%d", tm_instance->tm_mday, tm_instance->tm_mon + 1, tm_instance->tm_year + 1900);
        WCO_PDF_WriteText(worksheed_pointer, startx3, 775, tmp, page_counter);

        WCO_PDF_DrawLine(worksheed_pointer, 50, 750, HPDF_Page_GetWidth(worksheed_pointer->page[page_counter]) - 50, 750, page_counter);

    }else{
        worksheed_pointer->WCO_Worksheet_baseboardThreashold = 0;
    }
}






