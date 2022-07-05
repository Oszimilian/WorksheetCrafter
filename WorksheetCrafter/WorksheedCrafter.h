#ifndef WORKSHEEDCRAFTER_H_INCLUDED
#define WORKSHEEDCRAFTER_H_INCLUDED

#define false 0
#define true 1

#define _Addition 0
#define _Subtraction 1
#define _Multiplication 2
#define _Division 3
#define _Zahlentyp 4


GtkWidget *MyBuilder;
GtkWidget *MyWindow1;
GtkWidget *MyFixed1;
GtkWidget *MyButton1;
GtkWidget *MyButton2;
GtkWidget *MyButton3;
GtkWidget *MyCheckButton1;
GtkWidget *MyCheckButton2;
GtkWidget *MyCheckButton3;
GtkWidget *MyCheckButton4;
GtkWidget *MyRadioButton1;
GtkWidget *MyRadioButton2;

void *Start_GUI(void *vargp);
void exitApp();
void MyButton1_Clicked(GtkButton *b);
void MyCheckButton1_Toggled(GtkCheckButton *b);
void MyCheckButton2_Toggled(GtkCheckButton *b);
void MyCheckButton3_Toggled(GtkCheckButton *b);
void MyCheckButton4_Toggled(GtkCheckButton *b);
void MyRadioButton1_Toggled(GtkRadioButton *b);
void MyRadioButton2_Toggled(GtkRadioButton *b);


/*
*   Struct for the PDF
*/

struct worksheed{
    char mathTaskArray[48][20];
    HPDF_Doc pdf;
    HPDF_Page page[20];
    char file_names_commands[2][40];
    char file_names[2][30];
    int show_flag;
    char test_text[40];

    int addition_flag;
    int subtraction_flag;
    int multiplication_flag;
    int division_flag;
    int Z_flag;
    int R_flag;
}worksheed_instanze;

//For jumping through the sourcecode
jmp_buf env;

void Error_Handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data);
int Check_Pdf(struct worksheed *worksheed_pointer);
void Setup_Page(struct worksheed *worksheed_pointer, int page_count);
void Write_Text(struct worksheed *worksheed_pointer, int x, int y, char text[20], int page_count);
void Set_Filename(struct worksheed *worksheed_pointer, int nummer,  char name[20]);
void Save_Pdf(struct worksheed *worksheed_pointer, char text[]);
static void *View_PDF_1();
static void *View_PDF_2();
void Close_PDF(struct worksheed *worksheed_pointer);
void Close_WorksheedCrafter(struct worksheed *worksheed_pointer);
void Start_Pdf(struct worksheed *worksheed_pointer);
void *Handle_PDF_Viewer();


void Init_Task_Settings(struct worksheed *worksheed_pointer);
void Change_Task_Settings(struct worksheed *worksheed_pointer, int setting);

#endif // WORKSHEEDCRAFTER_H_INCLUDED
