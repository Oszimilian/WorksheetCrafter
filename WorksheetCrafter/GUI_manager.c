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
    MyLabel1 = GTK_LABEL(gtk_builder_get_object(MyBuilder, "MyLabel1"));
    MyButton1 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyButton1"));
    MyButton2 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyButton2"));
    MyButton3 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyButton3"));
    MyCheckButton1 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyCheckButton1"));
    MyCheckButton2 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyCheckButton2"));
    MyCheckButton3 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyCheckButton3"));
    MyCheckButton4 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyCheckButton4"));
    MyCheckButton5 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MyCheckButton5"));
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

    Set_Filename(&worksheed_instanze, 0, "Aufgaben.pdf");
    Set_Filename(&worksheed_instanze, 1, "Lösungen.pdf");

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
}

void MyCheckButton2_Toggled(GtkCheckButton *b)
{
    Change_Task_Settings(&worksheed_instanze, _Subtraction);
}

void MyCheckButton3_Toggled(GtkCheckButton *b)
{
    Change_Task_Settings(&worksheed_instanze, _Multiplication);
}

void MyCheckButton4_Toggled(GtkCheckButton *b)
{
    Change_Task_Settings(&worksheed_instanze, _Division);
}

void MyCheckButton5_Toggled(GtkCheckButton *b)
{
    Change_Task_Settings(&worksheed_instanze, _Baseboard);
}

void MyRadioButton1_Toggled(GtkRadioButton *b)
{
    Change_Task_Settings(&worksheed_instanze, _Zahlentyp);
}

void MyRadioButton2_Toggled(GtkRadioButton *b)
{

}


