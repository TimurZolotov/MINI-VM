#include "include/virtual_machine_structure.h"
#include "include/globals.h"
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SIZE 100 
#define NCODE(virtual_machine) virtual_machine -> bytecodes_array[virtual_machine -> program_counter++]

struct VirtualMachine *new_vm(int *bytecodes_array, int program_counter, int data_size) {  
    struct VirtualMachine *vm = (struct VirtualMachine *) malloc(sizeof(struct VirtualMachine));
    vm -> bytecodes_array = bytecodes_array;
    vm -> program_counter = program_counter;
    vm -> fraime_pointer = 0;
    vm -> stack_pointer = -1;
    vm -> continue_interpretation = true;
    vm -> ram = (int *) malloc(sizeof(int) * data_size);
    vm -> stack = (int *) malloc(sizeof(int) * STACK_SIZE);
    vm -> delete_vm = &delete_vm;
    vm -> run_interpretation_loop = &run_interpretation_loop;
    return vm;
}

void delete_vm(struct VirtualMachine *vm) {
    free(vm -> ram);
    free(vm -> stack);
    free(vm);
}

void run_interpretation_loop(struct VirtualMachine *vm) {
    while (vm -> continue_interpretation) {
        int operation_code = NCODE(vm);
        (*operations[operation_code - 1])(vm);
    }
}
