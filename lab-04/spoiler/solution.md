# Solution to the Dockcode Lab on reversing Rust

## 1

```
$ r2 ./dockcode
```

## 2

```
[0x000079b0]> iI
arch     x86
baddr    0x0
binsz    460071
bintype  elf
bits     64
canary   false
injprot  false
class    ELF64
compiler GCC: (Debian 12.2.0-14+deb12u1) 12.2.0 rustc version 1.88.0 (6b00bc388 2025-06-23)
crypto   false
endian   little
havecode true
intrp    /lib64/ld-linux-x86-64.so.2
laddr    0x0
lang     rust
linenum  true
lsyms    true
machine  AMD x86-64 architecture
nx       true
os       linux
pic      true
relocs   true
relro    full
rpath    NONE
sanitize false
static   false
stripped false
subsys   linux
va       true
```

Radare2 see the programming language is probably rust.

## 3

```
[0x000079b0]> aaa
INFO: Analyze all flags starting with sym. and entry0 (aa)
INFO: Analyze imports (af@@@i)
INFO: Analyze entrypoint (af@ entry0)
INFO: Analyze symbols (af@@@s)
WARN: Cannot find basic block for switch case at 0x0002c7dd bbdelta = 14
WARN: Cannot find basic block for switch case at 0x0002c1a6 bbdelta = 3
WARN: Cannot find basic block for switch case at 0x0002af01 bbdelta = 7
WARN: Cannot find basic block for switch case at 0x00028b01 bbdelta = 7
WARN: Cannot find basic block for switch case at 0x00028a8d bbdelta = 3
WARN: Cannot find basic block for switch case at 0x00028655 bbdelta = 3
INFO: Analyze all functions arguments/locals (afva@@@F)
INFO: Analyze function calls (aac)
INFO: Analyze len bytes of instructions for references (aar)
INFO: Finding and parsing C++ vtables (avrr)
INFO: Analyzing methods (af @@ method.*)
INFO: Recovering local variables (afva@@@F)
INFO: Type matching analysis for all functions (aaft)
INFO: Propagate noreturn information (aanr)
INFO: Use -AA or aaaa to perform additional experimental analysis
```

Several functions are called main:

```
[0x000079b0]> afl~main
0x00009fc0    1     34 sym.dockcode::main::__u7b__u7b_closure_u7d__u7d_::h560398bf3b728de1
0x00009b90   27    785 sym.dockcode::main::h786b1da3968f45ab
0x0000dca0    7    352 sym.core::slice::sort::stable::driftsort_main::hdaacefc17bdcf8f3
0x0000de00    7    368 sym.core::slice::sort::stable::driftsort_main::he67d38f1f0a3c5df
0x0000db40    7    352 sym.core::slice::sort::stable::driftsort_main::hd4a8d5e06126e738
0x0000d9e0    7    352 sym.core::slice::sort::stable::driftsort_main::h5ec73e94468e5cd8
0x0000d880    9    319 sym.core::slice::sort::stable::driftsort_main::h4f31c087e98163bf
0x00009ff0    1     23 main
```

The last one is interesting, but we quickly see it's a Rust init:

```
[0x000079b0]> s main
[0x00009ff0]> pdf
            ; ICOD XREF from entry0 @ 0x79c4(r)
┌ 23: int main (int argc, char **argv);
│ `- args(rdi, rsi)
│           0x00009ff0      50             push rax
│           0x00009ff1      4889f2         mov rdx, rsi                ; int64_t arg3
│           0x00009ff4      4863f7         movsxd rsi, edi             ; int64_t arg2
│           0x00009ff7      488d3d92fb..   lea rdi, [sym.dockcode::main::h786b1da3968f45ab] ; 0x9b90 ; "H\x81\xec\xd8\x01" ; int64_t arg1
│           0x00009ffe      31c9           xor ecx, ecx                ; int64_t arg4
│           0x0000a000      e8bbe1ffff     call sym.std::rt::lang_start::h0a6a356ee4a5ec17
│           0x0000a005      59             pop rcx
└           0x0000a006      c3             ret
```

It calls `sym.dockcode::main::h786b1da3968f45ab`. We go there: this is our main.

```
[0x00009ff0]> s sym.dockcode::main::h786b1da3968f45ab
[0x00009b90]> pdf 
...
```

## 4

[0x00009b90]> r2ai -e api=groq
[0x00009b90]> r2ai -e model=openai/gpt-oss-20b

returns pretty dummy code, without the expected authorization code:

```c
int main(void) {
    const char *prompt = "Enter docking authorization code: src/main.rsAuthorization fail";
    const char *expected = "EXPECTED_CODE";
    const char *success_msg = "Docking sequence authorized. 3\x8a\x04";
    const char *failure_msg = "Authorization failed. Access denied.\nDocking sequence authorize";

    printf("%s", prompt);
    fflush(stdout);

    char buffer[256];
    if (!fgets(buffer, sizeof buffer, stdin)) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    char *nl = strchr(buffer, '\n');
    if (nl) *nl = '\0';

    if (strcmp(buffer, expected) == 0) {
        printf("%s", success_msg);
    } else {
        printf("%s", failure_msg);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
```

Llama shows an authorization code, but it's not the right one. 

```
[0x00009b90]> r2ai -e model=llama-3.3-70b-versatile
[0x00009b90]> r2ai -e lang=rust
[0x00009b90]> r2ai -d
```

If Groq is not responding, you can also use Mistral with a free API key:

```
[0x00009b90]> r2ai -e api=mistral
[0x00009b90]> r2ai -e model=devstral-small-2507
```

```rust
fn main() {
    let mut buffer = [0u8; 200];
    let mut input = String::new();

    // Initialize buffer with specific values
    buffer[0] = 0x45; // 'E'
    buffer[4] = 0x70; // 'p'
    buffer[8] = 0x64; // 'd'
    buffer[12] = 0x6c; // 'l'
    buffer[16] = 0x50; // 'P'
    buffer[20] = 0x73; // 's'
    buffer[24] = 0x6a; // 'j'
    buffer[28] = 0x70; // 'p'
    buffer[32] = 0x6f; // 'o'
    buffer[36] = 0x3a; // ':'

    // Print prompt
    println!("Enter docking authorization code: src/main.rsAuthorization fail");

    // Read input
    std::io::stdin().read_line(&mut input).expect("Failed to read line");

    // Trim input
    let trimmed_input = input.trim();

    // Check if input matches expected value
    if trimmed_input == "EpdlPsjpo:" {
        println!("Docking sequence authorized. We are clear for landing.");
    } else {
        println!("Authorization failed. Access denied.\nDocking sequence aborted.");
    }
}
```

## 5

The authorization code we got is incorrect:

```
$ ./dockcode 
Enter docking authorization code: EpdlPsjpo:
Authorization failed. Access denied.
```

## 6

The source code returned by the model claims the expected authorization code is `EpdlsPjpo:`. While this is *not the correct code*, this is not a hallucination either: the string is present at the beginning of the "main" function (0x00009b90).

```
0x00009b90   sym.dockcode::main::h786b1da3968f45ab:
0x00009b90       4881ecd8010000  sub rsp, 0x1d8
0x00009b97     c744247845000000  mov dword [rsp + 0x78], 0x45
0x00009b9f     c744247c70000000  mov dword [rsp + 0x7c], 0x70
0x00009ba7 c784248000000064000000  mov dword [rsp + 0x80], 0x64
0x00009bb2 c78424840000006c000000  mov dword [rsp + 0x84], 0x6c
0x00009bbd c784248800000050000000  mov dword [rsp + 0x88], 0x50
0x00009bc8 c784248c00000073000000  mov dword [rsp + 0x8c], 0x73
0x00009bd3 c78424900000006a000000  mov dword [rsp + 0x90], 0x6a
0x00009bde c784249400000070000000  mov dword [rsp + 0x94], 0x70
0x00009be9 c78424980000006f000000  mov dword [rsp + 0x98], 0x6f
0x00009bf4 c784249c0000003a000000  mov dword [rsp + 0x9c], 0x3a
0x00009bff           488d7c2478  lea rdi, [rsp + 0x78]
0x00009c04           be0a000000  mov esi, 0xa
```

0x45 is ASCII for E, 0x70 is for p etc. Then, the top of the string is pushed in RDI, and its length (0xa) in ESI.

## 7

We search for calls to a `cmp` (compare) function in the main:

```
[0x00009b90]> pdf~cmp
0x00009cdf      4883fa00       cmp rdx, 0
0x00009f16      e8d5f3ffff     call sym.alloc::string::__impl_core::cmp::PartialEq_alloc::string::String__for_str_::eq::h3a77c5e8c96d89c8 ; alloc::string::_<impl core::cmp::PartialEq<alloc::string::String> for &str>::eq::h3a77c5e8c96d89c8
```

String comparison occurs in 0x9f16.

## 8

We are comparing var_110h and var_a0h:

```
0x00009f06     488dbc2410010000  lea rdi, [rsp + 0x110]
0x00009f0e     488db424a0000000  lea rsi, [rsp + 0xa0]
0x00009f16           e8d5f3ffff  call sym.alloc::string::__impl_core::cmp::PartialEq_alloc::string::String__for_str_::eq::h3a77c5e8c96d89c8
```

The current calling convention puts the first argument in RDI, and the second in RSI:

```
[0x00009b90]> afci
rax amd64 (rdi, rsi, rdx, rcx, r8, r9, xmm0, xmm1, xmm2, xmm3, xmm4);
```

So, the first argument is var_110h, and the second is var_a0h.
You can also see that with the `pd` command:

```
[0x00009b90]> pd 3 @ 0x9f06
0x00009f06      488dbc2410..   lea rdi, [var_110h]         ; int64_t arg1
0x00009f0e      488db424a0..   lea rsi, [var_a0h]          ; int64_t arg2
0x00009f16      e8d5f3ffff     call sym.alloc::string::__impl_core::cmp::PartialEq_alloc::string::String__for_str_::eq::h3a77c5e8c96d89c8 ; alloc::string::_<impl core::cmp::PartialEq<alloc::string::String> for &str>::eq::h3a77c5e8c96d89c8
```

With `VV`, you should quickly see that `var_110h` is the trimmed user input:

![](./images/r2-dockcode-trimmed.png)

Otherwise, search for uses of `var_110h`:

```
[0x00009b90]> axv~var_110h
  var_110h  0x9f06
  var_110h  0x9ef6
[0x00009b90]> pdi 5 @ 0x9ef6
0x00009ef6     48898c2410010000  mov qword [rsp + 0x110], rcx
0x00009efe     4889842418010000  mov qword [rsp + 0x118], rax
0x00009f06     488dbc2410010000  lea rdi, [rsp + 0x110]
0x00009f0e     488db424a0000000  lea rsi, [rsp + 0xa0]
0x00009f16           e8d5f3ffff  call sym.alloc::string::__impl_core::cmp::PartialEq_alloc::string::String__for_str_::eq::h3a77c5e8c96d89c8
[0x00009b90]> pdi 12 @ 0x9ef6-0x20
0x00009ed6           488b7c2428  mov rdi, qword [rsp + 0x28]
0x00009edb           e890ebffff  call sym.core::str::__impl_str_::trim::ha6de4e768c9fa07d
0x00009ee0           4889542410  mov qword [rsp + 0x10], rdx
0x00009ee5           4889442418  mov qword [rsp + 0x18], rax
0x00009eea                 eb00  jmp 0x9eec
0x00009eec           488b442410  mov rax, qword [rsp + 0x10]
0x00009ef1           488b4c2418  mov rcx, qword [rsp + 0x18]
0x00009ef6     48898c2410010000  mov qword [rsp + 0x110], rcx
0x00009efe     4889842418010000  mov qword [rsp + 0x118], rax
0x00009f06     488dbc2410010000  lea rdi, [rsp + 0x110]
0x00009f0e     488db424a0000000  lea rsi, [rsp + 0xa0]
0x00009f16           e8d5f3ffff  call sym.alloc::string::__impl_core::cmp::PartialEq_alloc::string::String__for_str_::eq::h3a77c5e8c96d89c8
```

The other variable, var_a0h, is used at those places:

```
[0x00009b90]> axv~var_a0h
   var_a0h  0x9c1c,0x9f0e,0x9f90
   var_a0h
```

For instance, here we see the variable gets its value from collect():

```
[0x00009b90]> pd 4 @ 0x9c1c
0x00009c1c      488dbc24a0..   lea rdi, [var_a0h]          ; int64_t arg1
0x00009c24      e877f1ffff     call sym.core::iter::traits::iterator::Iterator::collect::hb3cd1cba309388df
0x00009c29      488d3500e1..   lea rsi, reloc.fixup.Enter_docking_authorization_cod ; 0x57d30 ; int64_t arg2
0x00009c30      488dbc24b8..   lea rdi, [var_b8h]          ; int64_t arg1
```

Let's look around that, at the beginning of the function:

```
[0x00009b90]> pdi 20
0x00009b90   rip:
0x00009b90       4881ecd8010000  sub rsp, 0x1d8
0x00009b97     c744247845000000  mov dword [rsp + 0x78], 0x45
0x00009b9f     c744247c70000000  mov dword [rsp + 0x7c], 0x70
0x00009ba7 c784248000000064000000  mov dword [rsp + 0x80], 0x64
0x00009bb2 c78424840000006c000000  mov dword [rsp + 0x84], 0x6c
0x00009bbd c784248800000050000000  mov dword [rsp + 0x88], 0x50
0x00009bc8 c784248c00000073000000  mov dword [rsp + 0x8c], 0x73
0x00009bd3 c78424900000006a000000  mov dword [rsp + 0x90], 0x6a
0x00009bde c784249400000070000000  mov dword [rsp + 0x94], 0x70
0x00009be9 c78424980000006f000000  mov dword [rsp + 0x98], 0x6f
0x00009bf4 c784249c0000003a000000  mov dword [rsp + 0x9c], 0x3a
0x00009bff           488d7c2478  lea rdi, [rsp + 0x78]
0x00009c04           be0a000000  mov esi, 0xa
0x00009c09           e892f2ffff  call sym.core::slice::__impl__T__::iter::h9b7c7df855b8d0ad
0x00009c0e               4889c7  mov rdi, rax
0x00009c11               4889d6  mov rsi, rdx
0x00009c14           e877f1ffff  call sym.core::iter::traits::iterator::Iterator::map::hda29304d76915bf1
0x00009c19               4889c6  mov rsi, rax
0x00009c1c     488dbc24a0000000  lea rdi, [rsp + 0xa0]
0x00009c24           e877f1ffff  call sym.core::iter::traits::iterator::Iterator::collect::hb3cd1cba309388df
```

In 0x9c24, the call to collect() has "2 arguments":

- 1st argument: RDI contains var_a0h
- 2nd argument: RSI contains the result of map()

Actually, the function collect() returns a array  (Vec<T>) which cannot fit in the RAX register. So, here we are witnessing an *indirect structure return* where instead of returning something in RAX, the compiler allocates some space on the stack for the structure to be returned and provides it as first argument. So, in realitly, var_a0h will contain the result of collect().

Reading the few lines before we see that, it takes the fixed string, calls iter(), then map(), then collect(), which is a typicall Rust call such as:

```rust
let table = [ 'E', 'p', ...]
table.iter().map().collect();
```

... except that the Rust compiler has the habit of generating *specialized functions* when the code contains closures. For example, `sym.core::iter::traits::iterator::Iterator::map::hda29304d76915bf1` and `sym.core::iter::traits::iterator::Iterator::collect::hb3cd1cba309388df` are specialized map() and collect() functions.


# 9

```
[0x00009b90]> afl~dockcode
0x00009fc0    1     34 sym.dockcode::main::__u7b__u7b_closure_u7d__u7d_::h560398bf3b728de1
0x00009b90   27    785 sym.dockcode::main::h786b1da3968f45ab
```

There is obviously a closure in 0x9fc0.

## 10

```
[0x000079b0]> axg sym.dockcode::main::__u7b__u7b_closure_u7d__u7d_::h560398bf3b728de1
- 0x00009fc0 fcn 0x00009fc0 sym.dockcode::main::__u7b__u7b_closure_u7d__u7d_::h560398bf3b728de1
  - 0x00008e12 fcn 0x00008e00 sym.core::iter::adapters::map::map_fold::__u7b__u7b_closure_u7d__u7d_::h7f01f26bbfd3e300
  - 0x00008e00 fcn 0x00008e00 sym.core::iter::adapters::map::map_fold::__u7b__u7b_closure_u7d__u7d_::h7f01f26bbfd3e300
    - 0x000097c9 fcn 0x00009720 sym.__core::slice::iter::Iter_T__as_core::iter::traits::iterator::Iterator_::fold::h5b996dddf0b773d0
    - 0x00009720 fcn 0x00009720 sym.__core::slice::iter::Iter_T__as_core::iter::traits::iterator::Iterator_::fold::h5b996dddf0b773d0
      - 0x00007aa1 fcn 0x00007aa0 sym.__core::iter::adapters::map::Map_I_F__as_core::iter::traits::iterator::Iterator_::fold::hec80feded799dffb
      - 0x00007aa0 fcn 0x00007aa0 sym.__core::iter::adapters::map::Map_I_F__as_core::iter::traits::iterator::Iterator_::fold::hec80feded799dffb
        - 0x00008de1 fcn 0x00008de0 sym.core::iter::traits::iterator::Iterator::for_each::h4a9a3c3f30f95525
        - 0x00008de0 fcn 0x00008de0 sym.core::iter::traits::iterator::Iterator::for_each::h4a9a3c3f30f95525
          - 0x000096ef fcn 0x00009660 sym.__alloc::string::String_as_core::iter::traits::collect::Extend_char__::extend::ha4afb028aaeae2b4
          - 0x00009660 fcn 0x00009660 sym.__alloc::string::String_as_core::iter::traits::collect::Extend_char__::extend::ha4afb028aaeae2b4
            - 0x00009951 fcn 0x00009910 sym.__alloc::string::String_as_core::iter::traits::collect::FromIterator_char__::from_iter::h0db1dc0d3d78e0c7
            - 0x00009910 fcn 0x00009910 sym.__alloc::string::String_as_core::iter::traits::collect::FromIterator_char__::from_iter::h0db1dc0d3d78e0c7
              - 0x00008dab fcn 0x00008da0 sym.core::iter::traits::iterator::Iterator::collect::hb3cd1cba309388df
              - 0x00008da0 fcn 0x00008da0 sym.core::iter::traits::iterator::Iterator::collect::hb3cd1cba309388df
                - 0x00009c24 fcn 0x00009b90 sym.dockcode::main::h786b1da3968f45ab
                - 0x00009b90 fcn 0x00009b90 sym.dockcode::main::h786b1da3968f45ab
                  - 0x00009ff7 fcn 0x00009ff0 main
                  - 0x00009ff0 fcn 0x00009ff0 main
                    - 0x000079c4 fcn 0x000079b0 entry0
```

The closure is referenced at 0x9c24. This is at the beginning of the function, it is in the collect() function that manipulates the string:

```
[0x00009b90]> pdi 20
0x00009b90   rip:
0x00009b90       4881ecd8010000  sub rsp, 0x1d8
0x00009b97     c744247845000000  mov dword [rsp + 0x78], 0x45
0x00009b9f     c744247c70000000  mov dword [rsp + 0x7c], 0x70
0x00009ba7 c784248000000064000000  mov dword [rsp + 0x80], 0x64
0x00009bb2 c78424840000006c000000  mov dword [rsp + 0x84], 0x6c
0x00009bbd c784248800000050000000  mov dword [rsp + 0x88], 0x50
0x00009bc8 c784248c00000073000000  mov dword [rsp + 0x8c], 0x73
0x00009bd3 c78424900000006a000000  mov dword [rsp + 0x90], 0x6a
0x00009bde c784249400000070000000  mov dword [rsp + 0x94], 0x70
0x00009be9 c78424980000006f000000  mov dword [rsp + 0x98], 0x6f
0x00009bf4 c784249c0000003a000000  mov dword [rsp + 0x9c], 0x3a
0x00009bff           488d7c2478  lea rdi, [rsp + 0x78]
0x00009c04           be0a000000  mov esi, 0xa
0x00009c09           e892f2ffff  call sym.core::slice::__impl__T__::iter::h9b7c7df855b8d0ad
0x00009c0e               4889c7  mov rdi, rax
0x00009c11               4889d6  mov rsi, rdx
0x00009c14           e877f1ffff  call sym.core::iter::traits::iterator::Iterator::map::hda29304d76915bf1
0x00009c19               4889c6  mov rsi, rax
0x00009c1c     488dbc24a0000000  lea rdi, [rsp + 0xa0]
0x00009c24           e877f1ffff  call sym.core::iter::traits::iterator::Iterator::collect::hb3cd1cba309388df
```

## 11

```
[0x00009fc0]> r2ai -e model=moonshotai/kimi-k2-instruct
[0x00009fc0]> r2ai -x
[Assistant]

This function simply decrements the second argument by 1 and returns the result.
```

So, the closure simply substracts 1 to each element of the table.

## 12

```python
>>> encoded = 'EpdlPsjpo:'
>>> "".join(chr(ord(c) - 1) for c in encoded)
'DockOrion9'
```
