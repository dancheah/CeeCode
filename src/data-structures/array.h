#ifndef _ARRAY_H
#define _ARRAY_H

typedef unsigned int data_t;
typedef struct array array_t;

array_t* new_array(void);
void delete_array(array_t* a);
void print_array_info(array_t* a);
void print_data(data_t* d);
void append(array_t* a, data_t d); 
data_t* get(array_t* a, unsigned int pos);

#endif // _ARRAY_H
