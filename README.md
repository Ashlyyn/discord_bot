Discord bot created in C++ with Sleepy Discord.

Variable Naming Convention:
Class members prefixed with "m\_", excepting objects with an overloaded operator=() intended to be used like a function call
Static variables prefixed with "s\_"
Global variables prefixed with "g\_"
Function arguments prefixed with 'a'
Local variables prefixed with 'l'
Const variables prefixed with 'c'
Pointers prefixed with 'p'
Double pointers prefixed with "pp"
Function pointers prefixed with "fp"
References prefixed with 'r'

Precedence follows the order listed above (i.e. [m\_|s\_|g\_][a|l][c][p|fp][r]

All functions and variables are to be in camelCase, excepting functions which may be ambiguous with variables, which may be prefixed with "fn\_"

Classes and structs are to be in CapitalCase.
Enums and enum entries are to be in ALL\_CAPS\_SNAKE\_CASE.
