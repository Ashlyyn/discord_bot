Discord bot created in C++ with Sleepy Discord.

### Branches
`main` - guaranteed to be compiling, tested, and with all features working as intended unless noted otherwise.
`develop` - guaranteed to be compiling; features may or may not be fully implemented and tested. 
`experimental` - no guarantees; may or may not even be compiling.

### Setup
Create a directory for the project, clone it, and navigate into it.
Create a directory called `build` and navigate into it.
Run cmake on the parent directory (`cmake ..`). If dependencies of Sleepy Discord are missing (this project has no external dependencies besides Sleepy Discord), acquire them.
Run `make`.
Assuming no errors (the main and develop branches *should* always be compiling, at least with my build environment; if there is some error specific to a compiler that isn't gcc, make sure to report it), you'll now have the executable.
Open `config.json` and replace the `"token"` and "`ownerID`" fields with the correct info (the owner ID isn't necessary, it's just there to make the commands tagged with `noOwner`, like kick, ban, etc., not affect the owner; the token, however, is absolutely necessary, for obvious reasons).


### Variable Naming Convention

Class members are to be prefixed with "m\_", excepting objects with an overloaded operator() intended to be used like a function call

Static variables are to be prefixed with "s\_"

Global variables are to be prefixed with "g\_"

Function arguments are to be prefixed with 'a'

Local variables are to be prefixed with 'l'

Const variables are to be prefixed with 'c'

References are to be prefixed with 'r'

Pointers are to be prefixed with 'p'

Double pointers are to be prefixed with "pp"

Function pointers are to be prefixed with "fp"

Precedence follows the order listed above (i.e. [m\_|s\_|g\_|a|l][c][r][p|pp|fp]

All functions and variables are to be in camelCase, excepting functions which may be ambiguous with variables, which may be prefixed with "fn\_"

Classes and structs are to be in PascalCase.
Enums and enum entries are to be in ALL\_CAPS\_SNAKE\_CASE.
