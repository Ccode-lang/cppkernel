#define _GLIBCXX_USE_CXX11_ABI 0
#include "includes/colors.h"
#include "includes/keymap.h"
#include <string>


extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);

using namespace std;

char *vidptr = (char*)0xb8000;
// location on screen in bytes
int location = 0;
// a counter used for everything
int counter = 0;
string string1 = "Hello ";
void clear() {
	counter = 0;
	location = 0;
	while(counter < 80 * 25 * 2) {
		// fill screen with blanks
		vidptr[counter] = ' ';
		// makes characters grey.
		vidptr[counter+1] = 0x07; 		
		counter = counter + 2;
	}
}

void kprint(const char *str, int color) {
	counter = 0;
	//run until end of string is found
	while(str[counter] != '\0') {
		// ascii of character written to the memory
		vidptr[location] = str[counter];
		// gives color to letter
		vidptr[location+1] = color;
		++counter;
		location = location + 2;
	}
}

extern "C"
void kmain() {
	clear();
	string1 = string1 + "World";
	kprint(string1.c_str(), VGA_COLOR_GREEN);
}
