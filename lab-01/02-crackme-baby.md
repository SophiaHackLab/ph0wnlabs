# CrackMe Baby 2

- `./labs-01/bins/crackme-baby2`

> This is an ELF executable for Linux. 
> Non-Linux users: you don't need to execute it to solve the CrackMe. No worry.

```
$ ./crackme-baby2
=== This is a secret base ===
Password: 
```

Load the binary:

```
$ r2 ./crackme-baby2
```

- Analyze: `aaa`, list functions `afl`, spot the main, disassemble it `pdf @ main`.
- Consider that we have `Rvfcfd` in `s2` (see 0x00001199)
- At 0x00001214, consider our algorithm adds + 1 to each character
- **Decrypt the expected password using Radare2**

## Guided solution

Search for the string `Rvfc`:

```
[0x00001189]> / Rvfc
0x0000119c hit2_0 .SHH}HuERvfcEcfdHZH.
```

Show the string at 0x00001199

```
[0x00001189]> ps @ 0x0000119c
Rvfc
```

### Solution with the evaluation operator 

Use for example the evaluation operator to work out the expected password:

```
[0x00001189]> ? 'R' -1
```

This is character `Q`:

```
int32   81
uint32  81
hex     0x51
octal   0121
unit    81
segment 0000:0051
string  "Q"
fvalue  81.0
float   0.000000000000000f
double  0.000000000000000
binary  0b01010001
base36  0_29
ternary 0t10000
```

Continue for the next characters:

```
[0x00001189]> ? 'v' -1
[0x00001189]> ? 'f' -1
[0x00001189]> ? 'c' -1
[0x00001189]> ? 'd' -1
```

You should get: `Q`, `u`, `e`, `b`, `e`, `c`.

### Solution with rahash2

Adding or substracting 1 to each character is close to an *alphabet rotation* if we don't fall in cases where we loop to the beginning of the alphabet.

Check what `rahash2` can do (`man rahash2`):

- Select algorithm `rot`: `-E rot`
- Set the key: `-S s:1`

```
$ rahash2 -s Rvfcfd -E rot -S s:1
Quebec
```

### Solution by invoking Python
**Alternative**: invoke a Python:

```
[0x000010a0]> !python3
Python 3.10.14 (main, Jul 15 2024, 10:50:06) [GCC 12.2.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> >>> s = 'Rvfcfd'
>>> ''.join([ chr(ord(x) -1) for x in s ])
'Quebec'
```

