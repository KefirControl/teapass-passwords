# Teapass - Passwords Generator
---
### General
Teapass - is a simple password generator written in C.
I've created this program to practice my C skills. And I'm a beginner...
---
### Installation
There's no installation required. Simply download latest release and use it in your terminal!
### Usage
Teapass works in format like this: `teapass -l <LENGTH> -t <PASSWD_TYPE>`.
As described above, it accepts two arguments that define desired length of a password and a generation type.

- `-l` flag > accepts integer numbers from 4 to 256;
- `-t` flag > accepts "general" and "pin" values;
Type of generation defines which characters will be used in a password.
**General** - Includes special characters, upper- / lower-case literals and digits.
**PIN** - Includes only digits.
