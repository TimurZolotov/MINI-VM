#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

#define STACK_SIZE 100
#define PUSH(virtual_machine, stack_top_value) virtual_machine -> stack[++virtual_machine -> stack_pointer] = stack_top_value
#define POP(virtual_machine) virtual_machine -> stack[virtual_machine -> stack_pointer--] 
#define NCODE(virtual_machine) virtual_machine -> bytecodes_array[virtual_machine -> program_counter++]

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

extern int errno;

struct VirtualMachine* new_vm(int *, int, int);
void delete_vm(struct VirtualMachine *);
void run_interpretation_loop(struct VirtualMachine *);
static inline int *set_values_of_bytecodes_array(const char *);


static inline void push_the_sum_of_two_numbers(struct VirtualMachine *);
static inline void push_the_difference_of_numbers(struct VirtualMachine *);
static inline void push_the_product_of_numbers(struct VirtualMachine *);
static inline void push_the_quotien_of_numbers(struct VirtualMachine *);
static inline void push_powered_number(struct VirtualMachine *);
static inline void push_square_root_of_number(struct VirtualMachine *);
static inline void push_less_than_boolean_result(struct VirtualMachine *);
static inline void push_equivalent_boolean_result(struct VirtualMachine *);
static inline void set_program_counter_certainly(struct VirtualMachine *);
static inline void set_programm_counter_if_true(struct VirtualMachine *);
static inline void set_program_counter_if_false(struct VirtualMachine *);
static inline void push_local_variable_by_address_from_ram(struct VirtualMachine *);
static inline void push_global_variable_by_address_from_ram(struct VirtualMachine *);
static inline void create_local_variable_with_address_in_ram(struct VirtualMachine *);
static inline void create_global_variable_with_address_in_ram(struct VirtualMachine *);
static inline void print_int32(struct VirtualMachine *);
static inline void delete_value_from_stack_top(struct VirtualMachine *);
static inline void push_value_to_stack_top(struct VirtualMachine *);
static inline void get_out_of_the_interpretation_loop(struct VirtualMachine *);
static inline void call_subprogram(struct VirtualMachine *);
static inline void exit_from_subprogram(struct VirtualMachine *);
static inline void push_increased_number(struct VirtualMachine *);
static inline void push_decreased_number(struct VirtualMachine *);
static inline void print_ch(struct VirtualMachine *);

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
    OP_PRINT_CH
};

void (*operations[])(struct VirtualMachine *) = {
    push_the_sum_of_two_numbers,
    push_the_difference_of_numbers,
    push_the_product_of_numbers,
    push_the_quotien_of_numbers,
    push_powered_number,
    push_square_root_of_number,
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
    print_ch
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



static inline void push_the_sum_of_two_numbers(struct VirtualMachine *vm) { 
    PUSH(vm, POP(vm) + POP(vm));
}

static inline void push_the_difference_of_numbers(struct VirtualMachine *vm) {
    PUSH(vm, POP(vm) - POP(vm));
}

static inline void push_the_product_of_numbers(struct VirtualMachine *vm) {
    PUSH(vm, POP(vm) * POP(vm));
}

static inline void push_the_quotien_of_numbers(struct VirtualMachine *vm) {
    PUSH(vm, POP(vm) / POP(vm));
}

static inline void push_powered_number(struct VirtualMachine *vm) {
    int degree = POP(vm);
    PUSH(vm, pow(POP(vm), degree));
}

static inline void push_square_root_of_number(struct VirtualMachine *vm) {
    PUSH(vm, sqrt(POP(vm)));
}

static inline void push_less_than_boolean_result(struct VirtualMachine *vm) {
    PUSH(vm, (POP(vm) < POP(vm)) ? 1 : 0);
}

static inline void push_equivalent_boolean_result(struct VirtualMachine *vm) {
    PUSH(vm, (POP(vm) == POP(vm)) ? 1 : 0);
}

static inline void set_program_counter_certainly(struct VirtualMachine *vm) {
    vm -> program_counter = NCODE(vm);
}
static inline void set_programm_counter_if_true(struct VirtualMachine *vm) {     
    if (POP(vm))
        vm -> program_counter = NCODE(vm);
    else
        ++vm -> program_counter;
}

static inline void set_program_counter_if_false(struct VirtualMachine *vm) { 
    if (!POP(vm))
        vm -> program_counter = NCODE(vm);
    else
        ++vm -> program_counter;
}

static inline void push_local_variable_by_address_from_ram(struct VirtualMachine *vm) { 
    PUSH(vm, vm -> ram[vm -> fraime_pointer + NCODE(vm)]);
}

static inline void push_global_variable_by_address_from_ram(struct VirtualMachine *vm) { 
    int variable_address = POP(vm);
    PUSH(vm, vm -> ram[variable_address]);
    ++vm -> program_counter;
}

static inline void create_local_variable_with_address_in_ram(struct VirtualMachine *vm) { 
    int local_variable_value = POP(vm);
    vm -> ram[vm -> fraime_pointer + NCODE(vm)] = local_variable_value;
}

static inline void create_global_variable_with_address_in_ram(struct VirtualMachine *vm) {
    int global_variable_value = POP(vm);
    vm -> ram[NCODE(vm)] = global_variable_value;
}

static inline void print_int32(struct VirtualMachine *vm) {
    printf("%i", POP(vm));
}

static inline void delete_value_from_stack_top(struct VirtualMachine *vm) { 
    --vm -> stack_pointer;
}

static inline void push_value_to_stack_top(struct VirtualMachine *vm) {
    PUSH(vm, NCODE(vm));
}

static inline void get_out_of_the_interpretation_loop(struct VirtualMachine *vm) {
    vm -> continue_interpretation = false;
}

static inline void call_subprogram(struct VirtualMachine *vm) {    
    int jump_address = NCODE(vm);
    PUSH(vm, vm -> fraime_pointer);
    PUSH(vm, vm -> program_counter);
    vm -> fraime_pointer = vm -> stack_pointer;
    vm -> program_counter = jump_address;
}

static inline void exit_from_subprogram(struct VirtualMachine *vm) { 
    int return_value = POP(vm);
    vm -> stack_pointer = vm -> fraime_pointer;
    vm -> program_counter = POP(vm);
    vm -> fraime_pointer = POP(vm);
    PUSH(vm, return_value);
}

static inline void push_increased_number(struct VirtualMachine *vm) {
    PUSH(vm, POP(vm) + 1);
}

static inline void push_decreased_number(struct VirtualMachine *vm) {
    PUSH(vm, POP(vm) - 1);
}

static inline void print_ch(struct VirtualMachine *vm) {
    fprintf(stdout, "%c", POP(vm));
}
