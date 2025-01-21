# Ph0wn Labs 01

Welcome to **Ph0wn Labs 01**! 

1. Beginner tutorial on Radare2
2. Hack to meet Pico le Croco -- with Radare2
3. CTF, fun and more at https://ph0wn.shl.contact/

Bonus Ideas *and earn a Pico le Croco sticker*:

- Design the *SHL r2 cheatsheet* and share
- 3D print an object for *Ph0wn Labs or r2*
- Create a *Windows* or *MacOS* crackme to reverse with r2

Ph0wn News:

- https://ph0wn.org
- Discord: https://discord.gg/ddspM9deeu
- Next CTF: March 13-14 20**26**
- Want to contribute or sponsor? Contact @BetterCallPaul, @BlackB0x or @cryptax.

## Radare2

- Install radare2: https://www.radare.org/n/radare2.html
- Binary for my demo: **TODO**

10 commands to memorize:

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

References:

- [r2wiki](https://r2wiki.readthedocs.io/en/latest/)
- [The Official Radare2 Book](https://book.rada.re/refcard/intro.html)
- [Cheatsheet](https://github.com/radareorg/radare2-cheatsheets/releases/download/0.1/radare2-cheatsheet.pdf)

## Hack to meet Pico le Croco

![https://pico.masdescrocodiles.fr](./images/pico-at-shl-300.png)

Instructions:

- Get the binary `./bins/meet-pico` and try to solve each level.
- Use **Radare2** :)
- Each level is independant. In this crackme, you are meant to disassemble and understand each function `level1`, `level2`, `level3` etc one after the other.
- This is a *Beginner Tutorial*. **There is no difficult algorithm and no obfuscation.**

Setup your laptop:

- Install radare2: https://www.radare.org/n/radare2.html
- `./bins/meet-pico` is an ELF binary for Linux. You only need to run the binary to confirm you passed levels. If you don't care about confirmation, you don't need anything apart Radare2. 

If you're not on Linux *and* want to run the ELF binary, use the *Ph0wn Labs* Docker container.

- Install [Docker](https://docs.docker.com/get-started/get-docker/) and **Docker Compose**
- Run the Docker container for Ph0wn Labs:
```
cd docker
mkdir workspace
docker compose up -d --build
docker exec -it ph0wnlabs /bin/bash
```
- Share the binary in the `./workspace` directory


To stop the container: 

```
cd docker
docker compose stop
```






