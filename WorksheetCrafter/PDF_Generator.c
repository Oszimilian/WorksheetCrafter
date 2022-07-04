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

void Setup_Page(struct worksheed *worksheed_pointer, int page_count)
{
    worksheed_pointer->page[page_count] = HPDF_AddPage(worksheed_pointer->pdf);
    HPDF_Font font = HPDF_GetFont(worksheed_pointer->pdf, "Helvetica", NULL);
    HPDF_Page_SetFontAndSize(worksheed_pointer->page[page_count], font, 14);
}

void Write_Text(struct worksheed *worksheed_pointer, int x, int y, char text[20], int page_count)
{
    HPDF_Page_BeginText(worksheed_pointer->page[page_count]);
    HPDF_Page_TextOut(worksheed_pointer->page[page_count], x, y, text);
    HPDF_Page_EndText(worksheed_pointer->page[page_count]);
}

void Save_Pdf(struct worksheed *worksheed_pointer, char text[])
{
    HPDF_SaveToFile(worksheed_pointer->pdf, text);
    char command[20] = {"okular " };
    strcat(command, text);
    system(command);
}


void *Init_Pdf()
{
    //Init Worksheet-Sturct
    struct worksheed worksheed_instanze;

    //Initialize a pdf-Doc
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
    Setup_Page(&worksheed_instanze, 0);

    //Wirte some text
    Write_Text(&worksheed_instanze, 100, 100, "Hallo", 0);

    //Save pdf and show it witch okular viewer
    Save_Pdf(&worksheed_instanze, "test.pdf");

    //Neue PDF wird erzeugt
    HPDF_NewDoc(worksheed_instanze.pdf);

    //Generatign a new pdf
    Setup_Page(&worksheed_instanze, 1);

    Write_Text(&worksheed_instanze, 100, 100, "Servus", 1);

    Save_Pdf(&worksheed_instanze, "test2.pdf");


    HPDF_Free(worksheed_instanze.pdf);

}


