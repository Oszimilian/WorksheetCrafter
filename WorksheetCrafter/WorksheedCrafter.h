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

void *Start_GUI(void *vargp);
void exitApp();
void MyButton1_Clicked(GtkButton *b);
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

void Error_Handler (HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data);
int Check_Pdf(struct worksheed *worksheed_pointer);
void Setup_Page(struct worksheed *worksheed_pointer, int page_count);
void Write_Text(struct worksheed *worksheed_pointer, int x, int y, char text[20], int page_count);
void Set_Filename(struct worksheed *worksheed_pointer, int nummer,  char name[20]);
void Save_Pdf(struct worksheed *worksheed_pointer, int page_count);

void Close_PDF(struct worksheed *worksheed_pointer);
void Close_WorksheedCrafter(struct worksheed *worksheed_pointer);
void Draw_Solution_Line(struct worksheed *worksheed_pointer,char tmp[], int x1, int y1, int line_lengh, int page_counter);
void Draw_Line(struct worksheed *worksheed_pointer, int x1, int y1, int x2, int y2, int page_counter);
void Start_Pdf(struct worksheed *worksheed_pointer);
void *Handle_PDF_Viewer();
void *Handle_Worksheed();
void Update_Number_Type(struct worksheed *worksheed_pointer);
void Update_Decimal_Places(struct worksheed *worksheed_pointer);


int Init_Task_Settings(struct worksheed *worksheed_pointer);
void Change_Task_Settings(struct worksheed *worksheed_pointer, int setting);
void Create_Task_Sheed(struct worksheed *worksheed_pointer);
void Creat_Solution_Sheed(struct worksheed *worksheed_pointer);
void Create_Random_Task(struct worksheed *worksheed_pointer, int counter);
void Create_Baseboard(struct worksheed *worksheed_pointer, int page_counter);

#endif // WORKSHEEDCRAFTER_H_INCLUDED
