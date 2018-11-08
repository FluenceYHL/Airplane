#include "common_sys.h"
#include "General_Data.h"

#ifndef  CONTROL_H
#define CONTROL_H

void init_emergency();

void Add_emergency(int NO);

void print_emergency();

void Add_passager(buffer *head,int count);

int lenth(buffer *head);

void print_ID(buffer *head);

int deletehead(buffer *head);

void *add_passager(branch *head,int NO,int window_ID);

void creat(window *head);

int Lenth(branch *head);
void print_window(window *Head);

void Cycle_output();

void Add_window(window *head);

void Delete_Passager(branch *head);

void Allocate_Passager(branch *Que);

void Update_window(window *WINDOW);

void A_pattern(window *WINDOW,buffer *Buffer_list);

void B_pattern(window *head,buffer *Buffer_list);

void control_Window(window *WINDOW,buffer *Buffer_list);

void control_Buffer(window *WINDOW,buffer *Buffer_list);

void control_delete(window *WINDOW);

void control_emergency();

void control(window *WINDOW,buffer *Buffer_list);

void print_message(window *WINDOW,buffer *Buffer_list);

void countLen(window *WINDOW);

void Finish();

#endif


