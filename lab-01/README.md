# Ph0wn Lab 01

## Radare 2

### Setup

On Linux:

- Install radare2: https://www.radare.org/n/radare2.html

On other OS:

- Install [Docker](https://docs.docker.com/get-started/get-docker/) and **Docker Compose**
- Build the Docker container for Ph0wn Labs:

```
cd docker
mkdir workspace
docker compose up -d --build
docker exec -it ph0wnlabs /bin/bash
```

To stop the container: 

```
cd docker
docker compose stop
```


### 10 commands to memorize

1. **Help**: `?`, or detailed help on a command `a?`, `pd?`...
2. **Analyze**: `aa`, or deeper `aaa`, or even deeper `aaaa`...
3. **List functions**: `afl`
4. **Go To**: `s addr` goes to the given address (can be a name, flag too).
5. **Disassemble**: `pd 5` disassemble N (e.g 5) instructions, and `pdf` to disassemble an entire function. 
6. **Strings**: `iz` show strings in data section, `izz` show strings in the entire binary
7. **Cross references**: `axt`: find data/code references *to* this address, `axf` *from* this address.
8. **Add a comment**: `CC this is my comment @ addr`
9. **Flags**: r2 associates names to offsets (symbols, functions etc) and calls that *flags*. List all flags with `f`, or grep for a given name with `f~NAME`.
10. **Search**: `/ STRING` search for `STRING` everywhere, `/i STRING` for case insensitive, and `/x 04030201` to search bytes

### References

- [r2wiki](https://r2wiki.readthedocs.io/en/latest/)
- [The Official Radare2 Book](https://book.rada.re/refcard/intro.html)
- [Cheatsheet](https://github.com/radareorg/radare2-cheatsheets/releases/download/0.1/radare2-cheatsheet.pdf)

### Try on your own

- [CrackMe Baby 01](./01-crackme-baby.md) (very easy). First steps with Radare2.
- [CrackMe Baby 02](./02-crackme-baby.md): search for strings, evaluate operations.





