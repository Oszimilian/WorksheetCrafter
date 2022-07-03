#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <time.h>
#include <setjmp.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "hpdf.h"

jmp_buf env;

void error_handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
    printf ("ERROR: error_no=%04X, detail_no=%d\n",
      (unsigned int) error_no, (int) detail_no);
    longjmp (env, 1); /* invoke longjmp() on error */
}

GtkWidget *MyWindow1;
GtkWidget *MyFixed1;
GtkWidget *MyButton1;
GtkBuilder *MyBuilder;

void *myThreadFun(void *vargp)
{
    //sleep(1);
    //printf("Printing GeeksQuiz from Thread \n");
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


void *myThreadFun2(void *vargp)
{
    gtk_init(NULL, NULL);

    MyBuilder = gtk_builder_new_from_file("MyApp.glade");

    MyWindow1 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyWindow"));
    MyFixed1 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyFixed1"));
    MyButton1 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyButton1"));

    gtk_builder_connect_signals(MyBuilder, NULL);

    gtk_widget_show(MyWindow1);

    gtk_main();

    return 0;
}

int main(int argc, char *argv[])
{

    pthread_t thread_id;
    pthread_t thread_id2;
    printf("Before Thread\n");

    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_create(&thread_id2, NULL, myThreadFun2, NULL);

    pthread_join(thread_id, NULL);
    pthread_join(thread_id2, NULL);
    printf("After Thread\n");












    //return EXIT_SUCCESS;
    exit(0);
}

void exitApp()
{
    gtk_main_quit();
}

void MyButtonOneClicked()
{
    printf("Button One is clicked! \n");
    //gtk_label_set_text(MyLabel1, "Wie kann ich dir Helfen");
}

