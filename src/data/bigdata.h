#ifndef BIGDATA_H
#define BIGDATA_H

#include <stdint.h>

typedef struct {
  double mantissa;
  int16_t exponent;
} BigNum_t;

void BigNum_Init(BigNum_t *b, double val);
void BigNum_Add(BigNum_t *b, double val);
void BigNum_Mul(BigNum_t *b, double val);
void BigNum_Div(BigNum_t *b, double val);

void BigNum_ToString(const char *prefix, BigNum_t *b, char *buffer);

#endif