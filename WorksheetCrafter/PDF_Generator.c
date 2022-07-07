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

/*
*   This task initialices the base for making the math-pdf and wait for the call to start generating a pdf
*/
void *Handle_PDF_Viewer()
{
    worksheed_instanze.show_flag = 0;
    while(1)
    {
        while(worksheed_instanze.show_flag)
        {
            //initialising tow instanzes of Threads
            pthread_t thread_id3;
            pthread_t thread_id4;

            //Creat the Thread and teeling the function the function which have to be execute
            pthread_create(&thread_id3, NULL, View_PDF_1, NULL);
            pthread_create(&thread_id4, NULL, View_PDF_2, NULL);

            //Joining the Threads
            pthread_join(thread_id3, NULL);
            pthread_join(thread_id4, NULL);
        }
    }
}

/*
*   Shows the final task-pdf
*/
static void *View_PDF_1()
{
    //Calling via a System call the okular pdf-viewer
    system(worksheed_instanze.file_names_commands[0]);
    printf("View_PDF_1: %s\n", worksheed_instanze.file_names_commands[0]);
    return NULL;
}

/*
*   Shows the final solution-pdf
*/
static void *View_PDF_2()
{
    //Calling via a System call the ocular pdf-viewer
    system(worksheed_instanze.file_names_commands[1]);
    printf("View_PDF_2: %s\n", worksheed_instanze.file_names_commands[1]);
    return NULL;
}


