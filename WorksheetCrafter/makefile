HeaderDir = -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
ObjectFiles = GUI_manager.o main.o PDF_Generator.o PDF_Manager.o Worksheed_Generator.o Worksheed_Manager.o
LiberyLink = -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -export-dynamic  /usr/local/lib/libhpdf.a -lz -lm -lpthread
KP = -Wall -g $(LiberyLink) $(HeaderDir)

prog: $(ObjectFiles)
	gcc -o prog $(ObjectFiles) $(LiberyLink)

main.o: main.c
	gcc $(KP) -c main.c

GUI_manager.o: GUI_manager.c
	gcc $(KP) -c GUI_manager.c

PDF_Manager.o: PDF_Manager.c
	gcc $(KP) -c PDF_Manager.c

PDF_Generator.o: PDF_Generator.c
	gcc $(KP) -c PDF_Generator.c

Worksheed_Manager.o: Worksheed_Manager.c
	gcc $(KP) -c Worksheed_Manager.c

Worksheed_Generator.o: Worksheed_Generator.c
	gcc $(KP) -c Worksheed_Generator.c 

clean:
	rm *.o 
