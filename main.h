#ifndef MAIN_H
#define MAIN_H

/* Libraries */
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

/* MACROS - STATE */
#define NORM_STATE 0
#define FORM_STATE 1


/* MACROS - SUB STATE */
#define FLAGS_SUB_STATE 0
#define LEN_SUB_STATE 1
#define PREC_SUB_STATE 2
#define SPEC_SUB_STATE 3

#define FLAGS_PLUS 4
#define FLAGS_SPACE 5

#define FLAGS_SHARP 6 
#define FLAGS_SHARP_OCTAL 61
#define FLAGS_SHARP_HEXA 62
#define FLAGS_SHARP_HEXA_CAPS 63

#define PREC_POINT 7

#define LEN_L 8
#define LEN_H 9

#define BUFFERSIZE 1024

/**
 * struct mods - keeps track of active modifiers
 * 
 * @f: flags modifiers: +, space or #
 * @p: precision modifieras: . followed by digits
 * @l: len modifiers: l or h
 * 
 */
typedef struct mods
{
	int f;
	int p;
	int l;
} mods;

/**
 * struct format_print - choose functions format
 *
 * @fo: format
 * @write_fun: pointer function
 *
 */
typedef struct format_print
{
	char *fo;
	int (*write_fun)(va_list, char *, unsigned int, mods*);
} f_print;

/* prototypes */
int _printf(const char *format, ...);
int (*get_format_func(const char *, int))(va_list, char *, unsigned int, mods*);
int check_state(char);
int check_sub_state(char);
int check_sharp_state(char c);

int get_sub_mod(const char c, int mod);
int flags_modifier(char *main_buffer, unsigned int index, mods*);
unsigned int push_char(char *, char, unsigned int);
unsigned int write_buffer(char *r, unsigned int);
int check_overflow(char *, unsigned int, unsigned int);


int convert_base(char *, unsigned int, int, unsigned int, int);
char *_strncpy(char *, char *, int);
int _strlen(char *);

int write_str(va_list, char *, unsigned int, mods*);
int write_char(va_list, char *, unsigned int, mods*);
int write_num(va_list, char *, unsigned int, mods*);
int write_bin(va_list, char *, unsigned int, mods*);
int write_hexa(va_list, char *, unsigned int, mods*);
int write_HEXA(va_list, char *, unsigned int, mods*);
int write_octal(va_list, char *, unsigned int, mods*);
int write_unint(va_list, char *, unsigned int, mods*);

#endif
