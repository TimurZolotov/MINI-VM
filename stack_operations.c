#include "include/stack_operations.h"
#include "include/virtual_machine_structure.h"
#include "include/algorithms.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>


#define PUSH(virtual_machine, stack_top_value) virtual_machine -> stack[++virtual_machine -> stack_pointer] = stack_top_value
#define POP(virtual_machine) virtual_machine -> stack[virtual_machine -> stack_pointer--] 
#define NCODE(virtual_machine) virtual_machine -> bytecodes_array[virtual_machine -> program_counter++]

void push_the_sum_of_two_numbers(struct VirtualMachine *vm) { 
    PUSH(vm, POP(vm) + POP(vm));
}

void push_the_difference_of_numbers(struct VirtualMachine *vm) {
    PUSH(vm, POP(vm) - POP(vm));
}

void push_the_product_of_numbers(struct VirtualMachine *vm) {
    PUSH(vm, POP(vm) * POP(vm));
}

void push_the_quotien_of_numbers(struct VirtualMachine *vm) {
    PUSH(vm, POP(vm) / POP(vm));
}

void push_powered_number(struct VirtualMachine *vm) {
    int exhibitor = POP(vm);
    PUSH(vm, binary_power(POP(vm), exhibitor));
}

void push_square_root_of_number(struct VirtualMachine *vm) {
    PUSH(vm, sqrt(POP(vm)));
}

void push_less_than_boolean_result(struct VirtualMachine *vm) {
    PUSH(vm, (POP(vm) < POP(vm)) ? 1 : 0);
}

void push_equivalent_boolean_result(struct VirtualMachine *vm) {
    PUSH(vm, (POP(vm) == POP(vm)) ? 1 : 0);
}

void set_program_counter_certainly(struct VirtualMachine *vm) {
    vm -> program_counter = NCODE(vm);
}
void set_programm_counter_if_true(struct VirtualMachine *vm) {     
    if (POP(vm))
        vm -> program_counter = NCODE(vm);
    else
        ++vm -> program_counter;
}

void set_program_counter_if_false(struct VirtualMachine *vm) { 
    if (!POP(vm))
        vm -> program_counter = NCODE(vm);
    else
        ++vm -> program_counter;
}

void push_local_variable_by_address_from_ram(struct VirtualMachine *vm) { 
    PUSH(vm, vm -> ram[vm -> fraime_pointer + NCODE(vm)]);
}

void push_global_variable_by_address_from_ram(struct VirtualMachine *vm) { 
    int variable_address = POP(vm);
    PUSH(vm, vm -> ram[variable_address]);
    ++vm -> program_counter;
}

void create_local_variable_with_address_in_ram(struct VirtualMachine *vm) { 
    int local_variable_value = POP(vm);
    vm -> ram[vm -> fraime_pointer + NCODE(vm)] = local_variable_value;
}

void create_global_variable_with_address_in_ram(struct VirtualMachine *vm) {
    int global_variable_value = POP(vm);
    vm -> ram[NCODE(vm)] = global_variable_value;
}

void print_int32(struct VirtualMachine *vm) {
    printf("%i", POP(vm));
}

void delete_value_from_stack_top(struct VirtualMachine *vm) { 
    --vm -> stack_pointer;
}

void push_value_to_stack_top(struct VirtualMachine *vm) {
    PUSH(vm, NCODE(vm));
}

void get_out_of_the_interpretation_loop(struct VirtualMachine *vm) {
    vm -> continue_interpretation = false;
}

void call_subprogram(struct VirtualMachine *vm) {    
    int jump_address = NCODE(vm);
    PUSH(vm, vm -> fraime_pointer);
    PUSH(vm, vm -> program_counter);
    vm -> fraime_pointer = vm -> stack_pointer;
    vm -> program_counter = jump_address;
}

void exit_from_subprogram(struct VirtualMachine *vm) { 
    int return_value = POP(vm);
    vm -> stack_pointer = vm -> fraime_pointer;
    vm -> program_counter = POP(vm);
    vm -> fraime_pointer = POP(vm);
    PUSH(vm, return_value);
}

void push_increased_number(struct VirtualMachine *vm) {
    PUSH(vm, POP(vm) + 1);
}

void push_decreased_number(struct VirtualMachine *vm) {
    PUSH(vm, POP(vm) - 1);
}

void print_ch(struct VirtualMachine *vm) {
    fprintf(stdout, "%c", POP(vm));
}

void push_less_then_or_equal_to_boolean_result(struct VirtualMachine *vm) {
    PUSH(vm, (POP(vm) <= POP(vm)) ? 1 : 0); 
}

void push_more_then_boolean_result(struct VirtualMachine *vm) {
    PUSH(vm, (POP(vm) > POP(vm)) ? 1 : 0);
}

void push_more_then_or_equal_to_boolean_result(struct VirtualMachine *vm) {
    PUSH(vm, (POP(vm) >= POP(vm)) ? 1 : 0);
}
