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

#define _Addition_Min 0
#define _Addition_Max 1
#define _Subtraction_Min 2
#define _Subtraction_Max 3
#define _Multiplication_Min 4
#define _Multiplication_Max 5
#define _Division_Min 6
#define _Division_Max 7
#define _Addition_DecimalPlaces 8
#define _Subtraction_DecimalPlaces 9
#define _Multiplication_DecimalPlaces 10
#define _Division_DecimalPlaces 11


GtkBuilder *MyBuilder;
GtkWidget *MyWindow1;
GtkWidget *MyFixed1;
GtkLabel  *MyLabel1;
GtkLabel  *MyLabel2;
GtkLabel  *MyLabel3;
GtkLabel  *MyLabel4;
GtkLabel  *MyLabel5;
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
GtkWidget *MySpinButton10;
GtkWidget *MySpinButton11;
GtkWidget *MySpinButton12;
GtkWidget *MySpinButton13;


//GUI
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
void MySpinButton10_Changed(GtkSpinButton *s);
void MySpinButton11_Changed(GtkSpinButton *s);
void MySpinButton12_Changed(GtkSpinButton *s);
void MySpinButton13_Changed(GtkSpinButton *s);



/*
*   Struct for the PDF
*/



struct worksheed{
    HPDF_Doc pdf;
    HPDF_Page page[20];

    char WCO_Worksheet_taskArray[50][40];
    char WCO_Worksheet_solutionArray[50][40];

    char WCO_PDF_fileNamesCommand[2][40];
    char WCO_PDF_fileNames[2][30];

    int WCO_GUI_showPDFViewerFlag;
    int WCO_GUI_controllCreatButtonFlag;

    int WCO_Worksheet_additionEnableFlag;
    int WCO_Worksheet_subtractionEnableFlag;
    int WCO_Worksheet_multiplicationEnableFlag;
    int WCO_Worksheet_divisonEnableFlag;
    int WCO_Worksheet_zNumberEnableFlag;
    int WCO_Worksheet_rNumberEnableFlag;


    int WCO_Worksheet_number1_additionDigit;
    int WCO_Worksheet_number2_additionDigit;
    int WCO_Worksheet_number1_subtractionDigit;
    int WCO_Worksheet_number2_subtractionDigit;
    int WCO_Worksheet_number1_multiplicationDigit;
    int WCO_Worksheet_number2_multiplicationDigit;
    int WCO_Worksheet_number1_divisionDigit;
    int WCO_Worksheet_number2_divisionDigit;

    int WCO_Worksheet_additionDecimalPlaces;
    int WCO_Worksheet_subtractionDecimalPlaces;
    int WCO_Worksheet_multiplicationDecimalPlaces;
    int WCO_Worksheet_divisionDecimalPlaces;

    //int WCO_Worksheet_decimalPlaces;

    int WCO_Worksheet_baseboardEnableFlag;
    int WCO_Worksheet_baseboardThreashold;

    int WCO_Worksheet_initWorksheetComplete;
    int WCO_Background_updateDecimalPlacesComplete;

    int WCO_Background_updateWorksheetSettingsComplete;
}worksheed_instanze;

//For jumping through the sourcecode
jmp_buf env;




//GUI
void *WCO_GUI_Start(void *vargp);
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
void WCO_Worksheet_Adjust_ChangeWorksheetValues(struct worksheed *worksheed_pointer, int count, int value);

//WORSHEED_CREATE
void WCO_Worksheet_Create_Start(struct worksheed *worksheed_pointer);
void WCO_Worksheet_Creat_TaskSheet(struct worksheed *worksheed_pointer);
void WCO_Worksheet_Create_SolutionSheed(struct worksheed *worksheed_pointer);
void WCO_Worksheet_Create_RandomTask(struct worksheed *worksheed_pointer, int counter);
void WCO_Worksheet_Creat_Baseboard(struct worksheed *worksheed_pointer, int page_counter);



#endif // WORKSHEEDCRAFTER_H_INCLUDED
