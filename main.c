#include "include/stack_operations.h"
#include "include/virtual_machine_structure.h"
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

extern int errno;

static inline int *set_values_of_bytecodes_array(const char *);


enum {
    OP_ADD_I32 = 1,
    OP_SUB_I32,
    OP_MUL_I32,
    OP_DIV_I32,
    OP_POW_I32 = 5,
    OP_SQRT_I32,
    OP_LT_I32,
    OP_EQ_I32,
    OP_JMP,
    OP_JMPT,
    OP_JMPF,
    OP_LOAD,
    OP_GLOAD = 13,
    OP_STORE,
    OP_GSTORE = 15,
    OP_PRINT,
    OP_POP,
    OP_PUSH,
    OP_HALT,
    OP_CALL,
    OP_RET,
    OP_INC_I32 = 22,
    OP_DEC_I32,
    OP_PRINT_CH,
    OP_LTOEQT_I32,
    OP_MT_I32,
    OP_MTOEQT_I32,
    OP_MICRO_SLEEP,
    OP_BIT_AND,
    OP_BIT_OR,
    OP_BIT_NOT,
    OP_BIT_XOR,
    OP_LEFT_SHIFT,
    OP_RIGHT_SHIFT
};

void (*operations[])(struct VirtualMachine *) = {
    push_the_sum_of_two_numbers,
    push_the_difference_of_numbers,
    push_the_product_of_numbers,
    push_the_quotien_of_numbers,
    push_powered_number,
    push_root_of_number,
    push_less_than_boolean_result,
    push_equivalent_boolean_result,
    set_program_counter_certainly,
    set_programm_counter_if_true,
    set_program_counter_if_false,
    push_local_variable_by_address_from_ram,
    push_global_variable_by_address_from_ram,
    create_local_variable_with_address_in_ram,
    create_global_variable_with_address_in_ram,
    print_int32,
    delete_value_from_stack_top,
    push_value_to_stack_top,
    get_out_of_the_interpretation_loop,
    call_subprogram,
    exit_from_subprogram,
    push_increased_number,
    push_decreased_number,
    print_ch,
    push_less_then_or_equal_to_boolean_result,
    push_more_then_boolean_result,
    push_more_then_or_equal_to_boolean_result, 
    stopped_programm, 
    push_bit_and_result,
    push_bit_or_result,
    push_bit_not_result,
    push_bit_xor_result,
    push_bit_left_shift_result,
    push_bit_right_shift_result
};

int main(int argc, char *argv[]) {
    int *bytecodes = set_values_of_bytecodes_array(argv[1]);
    struct VirtualMachine *vm = new_vm(bytecodes, 0, 1);
    vm -> run_interpretation_loop(vm);
    vm -> delete_vm(vm);
    return EXIT_SUCCESS;
}

static inline int *set_values_of_bytecodes_array(const char *path_to_file_with_bytecodes) {
    FILE *bytecodes_file = fopen(path_to_file_with_bytecodes, "r");
    int *bytecodes = (int *) malloc(sizeof(int));
    
    if (!bytecodes_file) {
        fprintf(stderr, "\033[1m\033[31mError opening file for interpretation:\033[0m\033[22m %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    for (register int i = 0; !feof(bytecodes_file); ++i) {
        int hex_value = 0;
        fscanf(bytecodes_file, "%x", &hex_value);
        bytecodes = (int *) realloc(bytecodes, (i + 1) * sizeof(int));
        bytecodes[i] = hex_value;
    }
    fclose(bytecodes_file);
    return bytecodes;
}
