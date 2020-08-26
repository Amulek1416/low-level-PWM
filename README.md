# low-level-PWM
A fully customizable PWM library for arduino

This library was originally going to be a part of another project to just control some PWM signals at a low level. It eventually started become complicated enough to where a serperate repository was needed.

The library is contained in `PWM-lib` and examples for using the library can be found in `examples`

Within `PWM-lib` is the library's header file. In order to provide greater functionality to multiple boards, the definitions for the function prototypes will be sorted into sub directories names after the board type. 

There is also a `board_types.h` file in `PWM-lib` that MUST be used to determine what board is being used, and if the code inside the `.cpp` files should be included in the compilation. This is to avoid the error of having one function declared multiple times.

# THIS IS STILL IN DEVELOPMENT AND THE MASTER BRANCH ISN'T A FUNCTIONAL LIBRARY
