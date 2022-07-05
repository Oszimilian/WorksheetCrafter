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



void *Start_GUI(void *vargp)
{
    gtk_init(NULL, NULL);

    MyBuilder = gtk_builder_new_from_file("MyApp.glade");

    MyWindow1 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyWindow"));
    MyFixed1 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyFixed1"));
    MyButton1 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyButton1"));
    MyButton2 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyButton2"));
    MyButton3 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyButton3"));
    MyCheckButton1 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyCheckButton1"));
    MyCheckButton2 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyCheckButton2"));
    MyCheckButton3 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyCheckButton3"));
    MyCheckButton4 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyCheckButton4"));
    MyRadioButton1 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyRadioButton1"));
    MyRadioButton2 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyRadioButton2"));

    Init_Task_Settings(&worksheed_instanze);

    gtk_builder_connect_signals(MyBuilder, NULL);

    gtk_widget_show(MyWindow1);

    gtk_main();
}

void exitApp()
{
    Close_WorksheedCrafter(&worksheed_instanze);
}

void MyButton1_Clicked(GtkButton *b)
{
    //worksheed_instanze.show_flag = 0;

    printf("Button One is clicked! \n");

    Set_Filename(&worksheed_instanze, 0, "Test3.pdf");
    Set_Filename(&worksheed_instanze, 1, "Test4.pdf");

    worksheed_instanze.show_flag = 1;

    Start_Pdf(&worksheed_instanze);
}

void MyButton2_Clicked(GtkButton *b)
{
    Close_PDF(&worksheed_instanze);
}

void MyCheckButton1_Toggled(GtkCheckButton *b)
{
    Change_Task_Settings(&worksheed_instanze, _Addition);
    sprintf(worksheed_instanze.test_text, "Hallo mein Name ist Button1:");
}

void MyCheckButton2_Toggled(GtkCheckButton *b)
{
    Change_Task_Settings(&worksheed_instanze, _Subtraction);
    sprintf(worksheed_instanze.test_text, "Hallo mein Name ist Button2:");
}

void MyCheckButton3_Toggled(GtkCheckButton *b)
{
    Change_Task_Settings(&worksheed_instanze, _Multiplication);
    sprintf(worksheed_instanze.test_text, "Hallo mein Name ist Button3:");
}

void MyCheckButton4_Toggled(GtkCheckButton *b)
{
    Change_Task_Settings(&worksheed_instanze, _Division);
    sprintf(worksheed_instanze.test_text, "Hallo mein Name ist Button4:");
}

void MyRadioButton1_Toggled(GtkRadioButton *b)
{
    Change_Task_Settings(&worksheed_instanze, _Zahlentyp);
}

void MyRadioButton2_Toggled(GtkRadioButton *b)
{

}


