#ifndef VIRTUAL_MACHINE_STRUCTURE_H
#define VIRTUAL_MACHINE_STRUCTURE_H
#include <stdbool.h>

struct VirtualMachine {
    int *ram;  
    int *bytecodes_array;   
    int *stack;    
    int fraime_pointer;
    int program_counter;       
    int stack_pointer;      
    bool continue_interpretation;
    void (* delete_vm)(struct VirtualMachine *);
    void (* run_interpretation_loop)(struct VirtualMachine *);
};

struct VirtualMachine* new_vm(int *, int, int);
void delete_vm(struct VirtualMachine *); 
void run_interpretation_loop(struct VirtualMachine *);

#endif
