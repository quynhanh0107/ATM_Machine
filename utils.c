#include <stdio.h>
#include "utils.h"

void clearBuffer(void) {
    while (fgetc(stdin) != '\n');
}
