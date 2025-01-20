# Ph0wn Lab 01

## Radare 2

### Install 

> Install instructions: https://www.radare.org/n/radare2.html

### 10 commands to memorize

1. **Help**: `?`, or detailed help on a command `a?`, `pd?`...
2. **Analyze**: `aa`, or deeper `aaa`, or even deeper `aaaa`...
3. **List functions**: `afl`
4. **Go To**: `s addr` goes to the given address (can be a name, flag too).
5. **Disassemble**: `pd 5` disassemble N (e.g 5) instructions, and `pdf` to disassemble an entire function. 
6. **Strings**: `iz` show strings in data section, `izz` show strings in the entire binary
7. **Cross references**: `axt`: find data/code references *to* this address, `axf` *from* this address.
8. **Add a comment**: `CC this is my comment @ addr`
9. **Entry point**: `ie`
10. **Search**: `/ STRING` search for `STRING` everywhere, `/i STRING` for case insensitive, and `/x 04030201` to search bytes

### Try on your own

- [CrackMe Baby 01](./01-crackme-baby.md) (very easy). First steps with Radare2.
- [CrackMe Baby 02](./02-crackme-baby.md): search for strings, evaluate operations.





