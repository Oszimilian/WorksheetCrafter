#ifndef WORKSHEEDCRAFTER_H_INCLUDED
#define WORKSHEEDCRAFTER_H_INCLUDED

#define false 0
#define true 1

#define _Tasks 0
#define _Solutions 1

#define  _NULL 0

#define _Addition 0
#define _Subtraction 1
#define _Multiplication 2
#define _Division 3
#define _Zahlentyp 4
#define _Baseboard 5


GtkBuilder *MyBuilder;
GtkWidget *MyWindow1;
GtkWidget *MyFixed1;
GtkLabel  *MyLabel1;
GtkWidget *MyButton1;
GtkWidget *MyButton2;
GtkWidget *MyButton3;
GtkWidget *MyCheckButton1;
GtkWidget *MyCheckButton2;
GtkWidget *MyCheckButton3;
GtkWidget *MyCheckButton4;
GtkWidget *MyCheckButton5;
GtkWidget *MyRadioButton1;
GtkWidget *MyRadioButton2;
GtkWidget *MySpinButton1;
GtkWidget *MySpinButton2;
GtkWidget *MySpinButton3;
GtkWidget *MySpinButton4;
GtkWidget *MySpinButton5;
GtkWidget *MySpinButton6;
GtkWidget *MySpinButton7;
GtkWidget *MySpinButton8;
GtkWidget *MySpinButton9;


void exitApp();
void MyButton1_Clicked(GtkButton *b);
void MyButton2_Clicked(GtkButton *b);
void MyCheckButton1_Toggled(GtkCheckButton *b);
void MyCheckButton2_Toggled(GtkCheckButton *b);
void MyCheckButton3_Toggled(GtkCheckButton *b);
void MyCheckButton4_Toggled(GtkCheckButton *b);
void MyCheckButton5_Toggled(GtkCheckButton *b);
void MyRadioButton1_Toggled(GtkRadioButton *b);
void MyRadioButton2_Toggled(GtkRadioButton *b);
void MySpinButton1_Changed(GtkSpinButton *s);
void MySpinButton2_Changed(GtkSpinButton *s);
void MySpinButton3_Changed(GtkSpinButton *s);
void MySpinButton4_Changed(GtkSpinButton *s);
void MySpinButton5_Changed(GtkSpinButton *s);
void MySpinButton6_Changed(GtkSpinButton *s);
void MySpinButton7_Changed(GtkSpinButton *s);
void MySpinButton8_Changed(GtkSpinButton *s);
void MySpinButton9_Changed(GtkSpinButton *s);



/*
*   Struct for the PDF
*/



struct worksheed{
    char mathTaskArray[50][40];
    char mathSolutionArray[50][40];
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

    int number_range;
    int number_addition_digit_1;
    int number_addition_digit_2;
    int number_subtraction_digit_1;
    int number_subtraction_digit_2;
    int number_multiplication_digit_1;
    int number_multiplication_digit_2;
    int number_division_digit_1;
    int number_division_digit_2;
    int decimal_places;

    int baseboard_flag;
    int baseboard_treashold;

    int init_complete;
    int update_decimal_places;
    int update_number_type;
}worksheed_instanze;

//For jumping through the sourcecode
jmp_buf env;




//GUI
void *WCO_GUI_Start(void *vargp);
    //static void *WCO_GUI_PDFViewer_1_Start();
    //static void *WCO_GUI_PDFViewer_2_Start();
void *WCO_GUI_PDFViewer();
void WCO_GUI_ClosePDF(struct worksheed *worksheed_pointer);
void WCO_GUI_ClosePDFViewer(struct worksheed *worksheed_pointer);

//BACKGROUND
void *WCO_Background_Handle();
void WCO_Background_Controll_DecimalPlaces(struct worksheed *worksheed_pointer);
void WCO_Background_Controll_Visibility(struct worksheed *worksheed_pointer);

//PDF
void Error_Handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data);
int WCO_PDF_Check(struct worksheed *worksheed_pointer);
void WCO_PDF_SetupPage(struct worksheed *worksheed_pointer, int page_count);
void WCO_PDF_SetFilename(struct worksheed *worksheed_pointer, int nummer,  char name[20]);
void WCO_PDF_WriteText(struct worksheed *worksheed_pointer, int x, int y, char text[0], int page_count);
void WCO_PDF_SavePDF(struct worksheed *worksheed_pointer, int page_count);
void WCO_PDF_DrawSolutionLine(struct worksheed *worksheed_pointer,char tmp[], int x1, int y1, int line_lengh, int page_counter);
void WCO_PDF_DrawLine(struct worksheed *worksheed_pointer, int x1, int y1, int x2, int y2, int page_counter);

//WORKSHEED_ADJUST
void WCO_Worksheet_Adjust_ChangeWorksheetSettings(struct worksheed *worksheed_pointer, int setting);
int WCO_Worksheet_Adjust_InitWorksheetSettings(struct worksheed *worksheed_pointer);

//WORSHEED_CREATE
void WCO_Worksheet_Create_Start(struct worksheed *worksheed_pointer);
void WCO_Worksheet_Creat_TaskSheet(struct worksheed *worksheed_pointer);
void WCO_Worksheet_Create_SolutionSheed(struct worksheed *worksheed_pointer);
void WCO_Worksheet_Create_RandomTask(struct worksheed *worksheed_pointer, int counter);
void WCO_Worksheet_Creat_Baseboard(struct worksheed *worksheed_pointer, int page_counter);




#endif // WORKSHEEDCRAFTER_H_INCLUDED
