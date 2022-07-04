#ifndef WORKSHEEDCRAFTER_H_INCLUDED
#define WORKSHEEDCRAFTER_H_INCLUDED

GtkWidget *MyBuilder;
GtkWidget *MyWindow1;
GtkWidget *MyFixed1;
GtkWidget *MyButton1;

void *Start_GUI(void *vargp);
void exitApp();
void MyButtonOneClicked(GtkButton *b);


/*
*   Struct for the PDF
*/
struct worksheed{
    char mathTaskArray[48][20];
    HPDF_Doc pdf;
    HPDF_Page page[20];
};

//For jumping through the sourcecode
jmp_buf env;

void *Init_Pdf();
void Error_Handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data);
int Check_Pdf(struct worksheed *worksheed_pointer);
void Setup_Page(struct worksheed *worksheed_pointer, int page_count);


#endif // WORKSHEEDCRAFTER_H_INCLUDED
