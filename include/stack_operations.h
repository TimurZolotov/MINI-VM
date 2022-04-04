#ifndef STACK_OPERATIONS_H
#define STACK_OPERATIONS_H
#include "virtual_machine_structure.h"

void push_the_sum_of_two_numbers(struct VirtualMachine *);
void push_the_difference_of_numbers(struct VirtualMachine *);
void push_the_product_of_numbers(struct VirtualMachine *);
void push_the_quotien_of_numbers(struct VirtualMachine *);
void push_powered_number(struct VirtualMachine *);
void push_square_root_of_number(struct VirtualMachine *);
void push_less_than_boolean_result(struct VirtualMachine *);
void push_equivalent_boolean_result(struct VirtualMachine *);
void set_program_counter_certainly(struct VirtualMachine *);
void set_programm_counter_if_true(struct VirtualMachine *);
void set_program_counter_if_false(struct VirtualMachine *);
void push_local_variable_by_address_from_ram(struct VirtualMachine *);
void push_global_variable_by_address_from_ram(struct VirtualMachine *);
void create_local_variable_with_address_in_ram(struct VirtualMachine *);
void create_global_variable_with_address_in_ram(struct VirtualMachine *);
void print_int32(struct VirtualMachine *);
void delete_value_from_stack_top(struct VirtualMachine *);
void push_value_to_stack_top(struct VirtualMachine *);
void get_out_of_the_interpretation_loop(struct VirtualMachine *);
void call_subprogram(struct VirtualMachine *);
void exit_from_subprogram(struct VirtualMachine *);
void push_increased_number(struct VirtualMachine *);
void push_decreased_number(struct VirtualMachine *);
void print_ch(struct VirtualMachine *);
void push_less_then_or_equal_to_boolean_result(struct VirtualMachine *);
void push_more_then_boolean_result(struct VirtualMachine *);
void push_more_then_or_equal_to_boolean_result(struct VirtualMachine *); 
void stopped_programm(struct VirtualMachine *);

#endif
