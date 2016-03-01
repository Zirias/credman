#include <utils/int.h>
#include <utils/common.h>

static char *int_FormatToStringRecursive(
	unsigned int base, int quotient, size_t position, char **str);

char *
int_ToString(int self)
{
    return int_FormatToString(self, 10);
}

char *
int_FormatToString(int self, unsigned int base)
{
    if (!self) return copyString("0");
    char *result = 0;
    int_FormatToStringRecursive(base, self, 1, &result);
    return result;
}

static char *
int_FormatToStringRecursive(
	unsigned int base, int quotient, size_t length, char **str)
{
    int residue = quotient % base;
    char *pos;
    if (quotient /= base)
    {
	pos = int_FormatToStringRecursive(base, quotient, length + 1, str);
    }
    else
    {
	*str = xmalloc(length + 1);
	(*str)[length] = 0;
	pos = *str;
    }

    char digit = '0' + residue;
    if (digit > '9') digit += 'a' - '9' - 1;
    *pos++ = digit;
    return pos;
}

