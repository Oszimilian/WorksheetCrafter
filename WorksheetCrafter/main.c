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






int main()
{
    worksheed_instanze.init_complete = false;

    sprintf(worksheed_instanze.test_text, "Mein Name ist Main: \n");

    pthread_t thread_id1;
    pthread_t thread_id2;
    pthread_t thread_id5;


    pthread_create(&thread_id1, NULL, Handle_PDF_Viewer, NULL);
    pthread_create(&thread_id2, NULL, Start_GUI, NULL);
    pthread_create(&thread_id5, NULL, Handle_Worksheed, NULL);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id5, NULL);

    return EXIT_SUCCESS;
    //exit(0);
}




