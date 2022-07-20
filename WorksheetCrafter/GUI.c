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



void *WCO_GUI_Start(void *vargp)
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
    MySpinButton1 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MySpinButton1"));
    MySpinButton2 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MySpinButton2"));
    MySpinButton3 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MySpinButton3"));
    MySpinButton4 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MySpinButton4"));
    MySpinButton5 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MySpinButton5"));
    MySpinButton6 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MySpinButton6"));
    MySpinButton7 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MySpinButton7"));
    MySpinButton8 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MySpinButton8"));
    MySpinButton9 = GTK_WIDGET(gtk_builder_get_object(MyBuilder, "MySpinButton9"));

    worksheed_instanze.init_complete = WCO_Worksheet_Adjust_InitWorksheetSettings(&worksheed_instanze);

    gtk_builder_connect_signals(MyBuilder, NULL);

    gtk_widget_show(MyWindow1);

    gtk_main();

    return EXIT_SUCCESS;
}

void exitApp()
{
    WCO_GUI_ClosePDF(&worksheed_instanze);
}

void MyButton1_Clicked(GtkButton *b)
{
    worksheed_instanze.WCO_GUI_showPDFViewerFlag = 0;

    printf("Button One is clicked! \n");

    WCO_PDF_SetFilename(&worksheed_instanze, 0, "Aufgaben.pdf");
    WCO_PDF_SetFilename(&worksheed_instanze, 1, "Lösungen.pdf");

    worksheed_instanze.WCO_GUI_showPDFViewerFlag = 1;

    WCO_Worksheet_Create_Start(&worksheed_instanze);


}

void MyButton2_Clicked(GtkButton *b)
{
    WCO_GUI_ClosePDFViewer(&worksheed_instanze);
}

void MyCheckButton1_Toggled(GtkCheckButton *b)
{
    WCO_Worksheet_Adjust_ChangeWorksheetSettings(&worksheed_instanze, _Addition);
}

void MyCheckButton2_Toggled(GtkCheckButton *b)
{
    WCO_Worksheet_Adjust_ChangeWorksheetSettings(&worksheed_instanze, _Subtraction);
}

void MyCheckButton3_Toggled(GtkCheckButton *b)
{
    WCO_Worksheet_Adjust_ChangeWorksheetSettings(&worksheed_instanze, _Multiplication);
}

void MyCheckButton4_Toggled(GtkCheckButton *b)
{
    WCO_Worksheet_Adjust_ChangeWorksheetSettings(&worksheed_instanze, _Division);
}

void MyCheckButton5_Toggled(GtkCheckButton *b)
{
    WCO_Worksheet_Adjust_ChangeWorksheetSettings(&worksheed_instanze, _Baseboard);
}

void MyRadioButton1_Toggled(GtkRadioButton *b)
{
    WCO_Worksheet_Adjust_ChangeWorksheetSettings(&worksheed_instanze, _Zahlentyp);
    worksheed_instanze.update_number_type = false;
}

void MyRadioButton2_Toggled(GtkRadioButton *b)
{
    //Not relevant because it is connected in with RadioButton1 int the glade file and also in the programm
    worksheed_instanze.update_number_type = false;
}

void MySpinButton1_Changed(GtkSpinButton *s)
{
    gdouble spin_value = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MySpinButton1));
    worksheed_instanze.WCO_Worksheet_decimalPlaces = (int)spin_value;
    worksheed_instanze.update_WCO_Worksheet_decimalPlaces = false;
}




/*
*   function changes the max count of digits for the first part of the addition
*/
void MySpinButton2_Changed(GtkSpinButton *s)
{
    gdouble spin_value = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MySpinButton2));
    worksheed_instanze.WCO_Worksheet_number1_additionDigit = (int)spin_value;
}

/*
*   function changes the max count of digits for the second part of the addition
*/
void MySpinButton8_Changed(GtkSpinButton *s)
{
    gdouble spin_value = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MySpinButton8));
    worksheed_instanze.WCO_Worksheet_number2_additionDigit = (int)spin_value;
}

/*
*   function changes the max count of digits for the first part of the subtraction
*/
void MySpinButton5_Changed(GtkSpinButton *s)
{
    gdouble spin_value = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MySpinButton5));
    worksheed_instanze.WCO_Worksheet_number1_subtractionDigit = (int)spin_value;
}

/*
*   function changes the max count of digits for the second part of the subtraction
*/
void MySpinButton9_Changed(GtkSpinButton *s)
{
    gdouble spin_value = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MySpinButton9));
    worksheed_instanze.WCO_Worksheet_number2_subtractionDigit = (int)spin_value;
}

/*
*   function changes the max count of digits for the first part of the multiplication
*/
void MySpinButton3_Changed(GtkSpinButton *s)
{
    gdouble spin_value = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MySpinButton3));
    worksheed_instanze.WCO_Worksheet_number1_multiplicationDigit = (int)spin_value;
    worksheed_instanze.update_WCO_Worksheet_decimalPlaces = false;
}

/*
*   function changes the max count of digits for the second part of the multiplication
*/
void MySpinButton4_Changed(GtkSpinButton *s)
{
    gdouble spin_value = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MySpinButton4));
    worksheed_instanze.WCO_Worksheet_number2_multiplicationDigit = (int)spin_value;
    worksheed_instanze.update_WCO_Worksheet_decimalPlaces = false;
}

/*
*   function changes the max count of digits for the first part of the division
*/
void MySpinButton6_Changed(GtkSpinButton *s)
{
    gdouble spin_value = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MySpinButton6));
    worksheed_instanze.WCO_Worksheet_number1_divisionDigit = (int)spin_value;
}

/*
*   function changes the max count of digit for the second part of the division
*/
void MySpinButton7_Changed(GtkSpinButton *s)
{
    gdouble spin_value = gtk_spin_button_get_value(GTK_SPIN_BUTTON(MySpinButton7));
    worksheed_instanze.WCO_Worksheet_number2_divisionDigit = (int)spin_value;
}

/*
*   This task initialices the base for making the math-pdf and wait for the call to start generating a pdf
*/

/*
*   Shows the final task-pdf
*/
static void *WCO_GUI_PDFViewer_1_Start()
{
    //Calling via a System call the okular pdf-viewer
    system(worksheed_instanze.WCO_PDF_fileNamesCommand[0]);
    printf("View_PDF_1: %s\n", worksheed_instanze.WCO_PDF_fileNamesCommand[0]);
    return NULL;
}

/*
*   Shows the final solution-pdf
*/
static void *WCO_GUI_PDFViewer_2_Start()
{
    //Calling via a System call the ocular pdf-viewer
    system(worksheed_instanze.WCO_PDF_fileNamesCommand[1]);
    printf("View_PDF_2: %s\n", worksheed_instanze.WCO_PDF_fileNamesCommand[1]);
    return NULL;
}

void *WCO_GUI_PDFViewer()
{
    worksheed_instanze.WCO_GUI_showPDFViewerFlag = 0;
    while(1)
    {
        while(worksheed_instanze.WCO_GUI_showPDFViewerFlag)
        {
            //initialising tow instanzes of Threads
            pthread_t thread_id3;
            pthread_t thread_id4;

            //Creat the Thread and teeling the function the function which have to be execute
            pthread_create(&thread_id3, NULL, WCO_GUI_PDFViewer_1_Start, NULL);
            pthread_create(&thread_id4, NULL, WCO_GUI_PDFViewer_2_Start, NULL);

            //Joining the Threads
            pthread_join(thread_id3, NULL);
            pthread_join(thread_id4, NULL);
        }
    }
}



/*
*   Will close the Hole Programm
*/
void WCO_GUI_ClosePDF(struct worksheed *worksheed_pointer)
{
    WCO_GUI_ClosePDFViewer(&worksheed_instanze);
    gtk_main_quit();
    exit(0);
}

/*
*   Closes the PDF-Viewer
*/
void WCO_GUI_ClosePDFViewer(struct worksheed *worksheed_pointer)
{
    worksheed_pointer->WCO_GUI_showPDFViewerFlag = 0;
    system("killall okular");
}

