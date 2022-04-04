#include "include/algorithms.h"

int binary_power(double number, unsigned long long exhibitor) {
       double powered_number = 1.0;
       while(exhibitor != 0) {
              if((exhibitor & 1) != 0) {
                     powered_number *= number;
              }
              number *= number;
              exhibitor >>= 1;
       }
       return (int) powered_number;
}
