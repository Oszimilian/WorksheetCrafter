Softwaretool für generating random math training worksheets. Based on LibHaru for generating a output pdf and gtk for having a GUI. Written in c.

For Compiling the GTK-Part do this:
gcc -o WorksheetCrafter main.c -Wall 'pkg-config --cflags --libs gtk+-3.0` -export-dynamic /usr/local/lib/libhpdf.a -lz -lm
