**SPOILERS**

# Demo

- Source file: `demo.c`
- Compile: `make demo`

# Meet Pico

- Sources: `level1-4.c` (each level), `crackme.c` (main wrapper), `base64.c` (base64 implementation)
- Compile: `make meet-pico`

Tests:

- Test individually each level: `./levelN.sh level1` ... 
- Test all levels: `./auto_crackme.sh`

Solutions:

Play the videos with [Asciinema](https://asciinema.org) `asciinema play ./level1.cast` (1 for each level)

<script src="https://asciinema.org/a/0A5GuJHNFTqbrSN8zexBv6DgB.js" id="asciicast-0A5GuJHNFTqbrSN8zexBv6DgB" async="true"></script>

For level 4, reading the disassembly you should understand that you need to create a file that is translated as `p1coEl1te`. Function `sym.process_file` reads the file line by line, and each line is translated by `sym.convert_to_integer`. Each line is expected to be 8 characters. `#` will be 1s, and the rest 0s. The 8-bit value is converted to an integer... ASCII character.

```
$ python3 level4_solve.py p1coEl1te qr.txt
Fake QR code saved as qr.txt
$ cat qr.txt
 ###    
  ##   #
 ##   ##
 ## ####
 #   # #
 ## ##  
  ##   #
 ### #  
 ##  # #
```





