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
*   This function is a official error handler
*   Error-codes can be found on the git-hub-repo
*/
void Error_Handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%d\n", (unsigned int) error_no, (int) detail_no);
    longjmp (env, 1); /* invoke longjmp() on error */
}

/*
*   This function checks if pointer to the pdf-doc-struct is avalible
*/
int Check_Pdf(struct worksheed *worksheed_pointer)
{
    if (!worksheed_pointer->pdf)
    {
        printf ("ERROR: cannot create pdf object.\n");
        return 1;
    }

    if (setjmp(env))
    {
        HPDF_Free (worksheed_pointer->pdf);
        return 1;
    }

    return 0;
}
/*
*   Generates a new slide of a pdf or in case of previous called HPDF_NewDoc function it will generate a new pdf
*/
void Setup_Page(struct worksheed *worksheed_pointer, int page_count)
{
    worksheed_pointer->page[page_count] = HPDF_AddPage(worksheed_pointer->pdf);
    HPDF_Font font = HPDF_GetFont(worksheed_pointer->pdf, "Helvetica", NULL);
    HPDF_Page_SetFontAndSize(worksheed_pointer->page[page_count], font, 14);
}

/*
*   Writes some text on the pdf
*/
void Write_Text(struct worksheed *worksheed_pointer, int x, int y, char text[20], int page_count)
{
    HPDF_Page_BeginText(worksheed_pointer->page[page_count]);
    HPDF_Page_TextOut(worksheed_pointer->page[page_count], x, y, text);
    HPDF_Page_EndText(worksheed_pointer->page[page_count]);
    printf("Text wurde hinzugefügt\n");
}

/*
*   Set the filename for task and solution pdf global
*/
void Set_Filename(struct worksheed *worksheed_pointer, int nummer,  char name[20])
{
    sprintf(worksheed_pointer->file_names[nummer], "%s", name);
    printf("Set_Filename: %s\n", worksheed_pointer->file_names[nummer]);
    sprintf(worksheed_pointer->file_names_commands[0], "okular %s", worksheed_pointer->file_names[0]);
    sprintf(worksheed_pointer->file_names_commands[1], "okular %s", worksheed_pointer->file_names[1]);
}

/*
*   Saves the pdf // it is nesecarely to hand the full file name over .pdf
*/
void Save_Pdf(struct worksheed *worksheed_pointer, char text[])
{
    //Saves the pdf
    HPDF_SaveToFile(worksheed_pointer->pdf, text);
    printf("Save_Pdf: %s\n", text);
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

/*
*   Closes the PDF-Viewer
*/
void Close_PDF(struct worksheed *worksheed_pointer)
{
    worksheed_pointer->show_flag = 0;
    system("killall okular");
}

/*
*   Will close the Hole Programm
*/
void Close_WorksheedCrafter(struct worksheed *worksheed_pointer)
{
    Close_PDF(&worksheed_instanze);
    gtk_main_quit();
    exit(0);
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
    Setup_Page(worksheed_pointer, 0);

    //Wirte some text
    Write_Text(worksheed_pointer, 100, 100, worksheed_pointer->test_text, 0);

    //Save pdf and show it witch okular viewer
    //Save_Pdf(&worksheed_instanze, worksheed_instanze->file_names[0]);
    Save_Pdf(worksheed_pointer, "Test3.pdf");

    //Neue PDF wird erzeugt
    HPDF_NewDoc(worksheed_pointer->pdf);


    //Generatign a new pdf
    Setup_Page(worksheed_pointer, 1);

    Write_Text(worksheed_pointer, 100, 100,  worksheed_pointer->test_text, 1);

    //Save_Pdf(&worksheed_instanze, worksheed_instanze->file_names[1]);
    Save_Pdf(worksheed_pointer, "Test4.pdf");

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


