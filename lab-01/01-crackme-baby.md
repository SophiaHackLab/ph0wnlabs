# CrackMe Baby 1

- `./labs-01/bins/crackme-baby1`

> This is an ELF executable for Linux. 
> Non-Linux users: you don't need to execute it to solve the CrackMe. No worry.

```
$ ./crackme-baby1 
=== This is a secret base ===
Password: 
```

**Goal: find the password using Radare2**

## Guided solution

```
$ r2 ./crackme-baby1 
WARN: Relocs has not been applied. Please use `-e bin.relocs.apply=true` or `-e bin.cache=true` next time
 -- Change the registers of the child process in this way: 'dr eax=0x333'
[0x00001090]> 
```

- Don't worry about the warnings you may (or may not) have at beginning
- A startup sentence changes at each run (`-- Change the registers of the child process in this way: 'dr eax=0x333'`)

Get some information on the binary:

```
[0x00001090]> i
```

It was compiled on Debian 12. It's for Linux 64 bits.

```
fd       3
file     ./crackme-baby1
size     0x3f48
humansz  15.8K
mode     r-x
format   elf64
iorw     false
block    0x100
type     DYN (Shared object file)
arch     x86
baddr    0x0
binsz    14211
bintype  elf
bits     64
canary   false
injprot  false
class    ELF64
compiler GCC: (Debian 12.2.0-14) 12.2.0
crypto   false
endian   little
havecode true
intrp    /lib64/ld-linux-x86-64.so.2
laddr    0x0
lang     c
linenum  true
lsyms    true
machine  AMD x86-64 architecture
nx       true
os       linux
pic      true
relocs   true
relro    partial
rpath    NONE
sanitize false
static   false
stripped false
subsys   linux
va       true
```

Analyze the binary:

```
[0x00001090]> aaa
```

List functions (`afl`)

```
[0x00001090]> afl
```

The main is at 0x00001179

```
0x00001030    1      6 sym.imp.puts
0x00001040    1      6 sym.imp.printf
0x00001050    1      6 sym.imp.strcspn
0x00001060    1      6 sym.imp.fgets
0x00001070    1      6 sym.imp.strcmp
0x00001080    1      6 sym.imp.__cxa_finalize
0x00001090    1     33 entry0
0x000010c0    4     34 sym.deregister_tm_clones
0x000010f0    4     51 sym.register_tm_clones
0x00001130    5     54 entry.fini0
0x00001170    1      9 entry.init0
0x00001234    1      9 sym._fini
0x00001179    5    187 main
0x00001000    3     23 sym._init
```

Alternatives:

- `afl~main`: grep the output of afl to show lines with word `main`
- Locate the entry point `ie`, disassemble it (`pdf`), see it calls `main`

Decompile the main:

```
[0x00001179]> pdf
```

or `pdf @ main`, or `pdf @ 0x00001179`

- What value does the binary write in `s2`?
- At 0x000011e7, the binary compares `s1` and `s2`. What is inside `s1`?
- If both strings are equal, `strcmp` returns 0, so eax will have value 0. Where do we jump?

> `test eax, eax` performs a bitwise AND operation on EAX with itself and updates the zero flag.

- What is the correct password?
