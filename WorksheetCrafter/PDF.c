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
int WCO_PDF_Check(struct worksheed *worksheed_pointer)
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
void WCO_PDF_SetupPage(struct worksheed *worksheed_pointer, int page_count)
{
    worksheed_pointer->page[page_count] = HPDF_AddPage(worksheed_pointer->pdf);
    HPDF_Font font = HPDF_GetFont(worksheed_pointer->pdf, "Helvetica", NULL);
    HPDF_Page_SetFontAndSize(worksheed_pointer->page[page_count], font, 14);
}

/*
*   Set the filename for task and solution pdf global
*/
void WCO_PDF_SetFilename(struct worksheed *worksheed_pointer, int nummer,  char name[20])
{
    sprintf(worksheed_pointer->file_names[nummer], "%s", name);
    printf("Set_Filename: %s\n", worksheed_pointer->file_names[nummer]);
    sprintf(worksheed_pointer->file_names_commands[0], "okular %s", worksheed_pointer->file_names[0]);
    sprintf(worksheed_pointer->file_names_commands[1], "okular %s", worksheed_pointer->file_names[1]);
}

/*
*   Writes some text on the pdf
*/
void WCO_PDF_WriteText(struct worksheed *worksheed_pointer, int x, int y, char text[0], int page_count)
{
    HPDF_Page_BeginText(worksheed_pointer->page[page_count]);
    HPDF_Page_TextOut(worksheed_pointer->page[page_count], x, y, text);
    HPDF_Page_EndText(worksheed_pointer->page[page_count]);
}

/*
*   Saves the pdf // it is nesecarely to hand the full file name over .pdf
*/
void WCO_PDF_SavePDF(struct worksheed *worksheed_pointer, int page_count)
{
    //Saves the pdf
    HPDF_SaveToFile(worksheed_pointer->pdf, worksheed_pointer->file_names[page_count]);
    printf("Save_Pdf: %s\n", worksheed_pointer->file_names[page_count]);
}



/*
*   This function draws a line after every math-task to note down the handwritten answer
*/
void WCO_PDF_DrawSolutionLine(struct worksheed *worksheed_pointer,char tmp[], int x1, int y1, int line_lengh, int page_counter)
{
    int task_lengh = strlen(tmp) + 1;
    int pattern_lengh = 6;
    int x2 = x1;
    int y2 = y1;

    //printf("Task_Lengh: %d -> %s \n", task_lengh, tmp);

    x1 = x1 + (task_lengh * pattern_lengh);
    x2 = x2 + (task_lengh * pattern_lengh) + line_lengh;

    HPDF_Page_MoveTo(worksheed_pointer->page[page_counter], x1, y1);
    HPDF_Page_LineTo(worksheed_pointer->page[page_counter], x2, y2);
    HPDF_Page_Stroke(worksheed_pointer->page[page_counter]);

}

/*
*   This function draws a line from point a to b
*/
void WCO_PDF_DrawLine(struct worksheed *worksheed_pointer, int x1, int y1, int x2, int y2, int page_counter)
{
    HPDF_Page_MoveTo(worksheed_pointer->page[page_counter], x1, y1);
    HPDF_Page_LineTo(worksheed_pointer->page[page_counter], x2, y2);
    HPDF_Page_Stroke(worksheed_pointer->page[page_counter]);
}



