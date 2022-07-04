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






int main(int *argc, char *argv[])
{

    pthread_t thread_id1;
    pthread_t thread_id2;


    pthread_create(&thread_id1, NULL, Init_Pdf, NULL);
    pthread_create(&thread_id2, NULL, Start_GUI, NULL);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);



    return EXIT_SUCCESS;
    //exit(0);
}


