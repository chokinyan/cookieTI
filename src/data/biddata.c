#include "bigdata.h"
#include <string.h>
#include <ti/real.h>
#include <ti/sprintf.h>

#pragma region init
void BigNum_Init(BigNum_t *b, double val) {
  b->exponent = 0;
  b->mantissa = val;

  while (b->mantissa >= 1e13) {
    b->mantissa /= 1e13;
    b->exponent++;
  }
}
#pragma endregion

#pragma region math
void BigNum_Add(BigNum_t *b, double val) {
  b->mantissa += val;

  while (b->mantissa >= 1e13) {
    b->mantissa /= 1e13;
    b->exponent++;
  }
}

void BigNum_Sub(BigNum_t *b, double val) {
  b->mantissa -= val;

  /* Eviter boucle infinie si mantissa == 0.0 */
  if (b->mantissa == 0.0) {
    b->exponent = 0;
    return;
  }

  while (b->mantissa < 1.0) {
    b->mantissa *= 1e13;
    b->exponent--;
  }
}

void BigNum_Mul(BigNum_t *b, double val) {
  b->mantissa *= val;
  while (b->mantissa >= 1e13) {
    b->mantissa /= 1e13;
    b->exponent++;
  }
}

void BigNum_Div(BigNum_t *b, double val) {
  if (val == 0.0) return; /* Division par zero */
  b->mantissa /= val;

  /* Eviter boucle infinie si mantissa == 0.0 */
  if (b->mantissa == 0.0) {
    b->exponent = 0;
    return;
  }

  while (b->mantissa < 1.0) {
    b->mantissa *= 1e13;
    b->exponent--;
  }
}

/* Convertit un float en string via les routines OS TI */
static void mantissa_to_str(double val, char *out) {
  real_t r = os_FloatToReal((float)val);
  /* os_RealToStr(dest, real, length, dispMode, digits)
     dispMode 1 = normal, digits 0 = max precision */
  os_RealToStr(out, &r, 10, 1, 0);
}

void BigNum_ToString(const char *prefix, BigNum_t *b, char *buffer) {
  char num_str[20];
  mantissa_to_str(b->mantissa, num_str);

  /* Copier le prefix puis coller le nombre */
  strcpy(buffer, prefix);
  strcat(buffer, num_str);

  if (b->exponent != 0) {
    /* Ajouter l'exposant : "e+XX" via boot_sprintf (int supporte %d) */
    char exp_str[12];
    boot_sprintf(exp_str, "e+%d", b->exponent * 13);
    strcat(buffer, exp_str);
  }
}

#pragma endregion
