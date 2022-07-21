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







int main(void)
{
    worksheed_instanze.WCO_Worksheet_initWorksheetComplete = false;


    pthread_t thread_id1;
    pthread_t thread_id2;
    pthread_t thread_id5;


    pthread_create(&thread_id1, NULL, WCO_GUI_PDFViewer, NULL);
    pthread_create(&thread_id2, NULL, WCO_GUI_Start, NULL);
    pthread_create(&thread_id5, NULL, WCO_Background_Handle, NULL);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id5, NULL);

    return EXIT_SUCCESS;
    //exit(0);
}




