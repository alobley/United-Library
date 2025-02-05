## The United Library
This is a C/C++ library that allows C syntax to remain consistent across multiple compilers and C standards, from ANSI C onwards.
Just add united.h to your C project and follow its syntax rules to make C code that can run on almost all used compilers, including C++ compilers!

## Syntax
The United library changes some syntax around, but was designed to be both readable and nonobstructive to your coding experience.

- **Attributes**
    - Most compiler-specific attributes are defined like `_[attribute]_` or `_[attribute]_(args)`. It is meant to be easy to understand.

- The `__asm__` keyword has been simplified to just `asm`, but inline assembly is unsupported by MSVC, so keep that in mind if you use it.

- **Long long integers**
    - The United library provides a consistent interface for interacting with long long (at least 64 bit width) integers, allowing ANSI C code to use them 
    and still be compiled with compilers that have later standards

- **Keywords**
    - The United library aims to bridge the gaps between C standards, and part of that is keywords. Depending on the C standard used, it defines the missing keywords
    from the standard being used all the way up to C23.

- It is best practice to always declare `c_style` at your entry point function, in the case of a freestanding binary with a C++ compiler or a 
specifically defined entry point.

- **For Loops and Local Variables**
    - ANSI C has difficult restrictions with its local variables, so the `_for_` macro aims to make a very intuitive for loop interface for making loops.
    It is best practice for you to use the `_for_` macro for your for loops instead of the built-in C ones for maximum compatibility.

    - ANSI C's variable problems also extend to other varibales, so the `localvar` macro intends to allow local variables to be declared and used anywhere
    in your code, as long as everything that uses it is inside of the macro's context.

## Contributing
Contributing is always welcome! The library is still incomplete and likely has a few mistakes I missed, and documentation should be made for it too.
The ultimate goal is to make the ideal interface for C programming where your C code doesn't have to change in any way when compiled in different ways.

## License
- This software is licensed under the **MIT License**. See the `LICENSE` file in the root directory for more information.