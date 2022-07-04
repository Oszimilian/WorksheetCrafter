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
void *myThreadFun(void *vargp)
{
    //sleep(1);
    printf("Printing GeeksQuiz from Thread \n");
    HPDF_Doc pdf;
    pdf = HPDF_New (error_handler, NULL);

    if (!pdf) {
        printf ("ERROR: cannot create pdf object.\n");
        return 1;
    }

    if (setjmp(env)) {
        HPDF_Free (pdf);
        return 1;
    }

    HPDF_Page page_1;
    page_1 = HPDF_AddPage (pdf);
    HPDF_SaveToFile(pdf, "test1.pdf");



    HPDF_NewDoc(pdf);


    HPDF_Page page_2;
    page_2 = HPDF_AddPage(pdf);

    HPDF_SaveToFile(pdf, "test2.pdf");
    HPDF_Free(pdf);

    system("okular test1.pdf");
    system("okular test2.pdf");

    return NULL;
}

*/




int main(int *argc, char *argv[])
{

    pthread_t thread_id1;
    pthread_t thread_id2;
    printf("Before Thread\n");

    pthread_create(&thread_id1, NULL, Init_Pdf, NULL);
    pthread_create(&thread_id2, NULL, Start_GUI, NULL);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    printf("After Thread\n");


    return EXIT_SUCCESS;
    //exit(0);
}


