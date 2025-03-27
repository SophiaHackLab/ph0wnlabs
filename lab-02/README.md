# Ph0wn Labs 02

:tada: Welcome to **Ph0wn Labs 02**! 

1. Installation of Pico SDK for Raspberry Pico
2. Repair Pico's car and solve "Pico PCB 2" at https://ph0wn.shl.contact/
3. Implement, flash and share your best April Fool program for Raspberry Pico.

:newspaper: Ph0wn News:

- https://ph0wn.org
- Discord: https://discord.gg/ddspM9deeu
- :date: Next CTF: March 13-14 20**26**
- Want to contribute :pencil: or sponsor :dollar: ? Contact @BetterCallPaul, @BlackB0x or @cryptax.

## Documentation de référence

- [Getting started with Pico](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)
- [Raspberry Pi Pico series C/C++ SDK](https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf)
- [Pico-SDK](https://github.com/raspberrypi/pico-sdk)
- [Hardware design with RP2040](https://datasheets.raspberrypi.com/rp2040/hardware-design-with-rp2040.pdf)
- [Ph0wn SHL CTF](https://ph0wn.shl.contact)

## Installer le Pico SDK

This will install the necessary packages (apt-get...) and clone the SDK as a sub-directory of `~/softs`:

```
cd softs
wget https://raw.githubusercontent.com/raspberrypi/pico-setup/master/pico_setup.sh`
chmod u+x pico_setup.h
./pico_setup.sh
export PICO_SDK_PATH=~/softs/pico/pico-sdk
```

## Ph0wn 2024 Pico PCB 2

- Récupérez un board Pico le Croco
- Connectez-vous à [Ph0wn SHL CTF](https://ph0wn.shl.contact)
- Cherchez le challenge Pico PCB 2, et résolvez le !

Conseil: 

- Si vous avez déjà un environnement de CTF, installez juste [Ghidra](https://github.com/NationalSecurityAgency/ghidra/releases) ou le désassembleur de votre choix.
- Si vous n'avez pas d'environnement CTF, installez [Exegol](https://exegol.readthedocs.io/en/latest/)

- Installez 

> Spoiler: [write-up](https://github.com/ph0wn/writeups/blob/master/2024/pico-pcb/solution/stage2/writeup.md) - ne le regardez qu'à la fin du lab !

## 1er avril - Pico

Laissez votre créativité s'exprimer et programmez l'application de votre choix. On suggère qqch autour des blagues du 1er avril :tada:

1. Ecrivez votre code et compilez: "Programmer sur le RP2040"
2. Flashez votre firmware, pour cela consultez "PCB Pico le Croco Ph0wn 2024"
3. Enjoy :smiley:

### Programmer sur le RP2040

1. Write `yourprog.c`
2. Write `CMakeLists.txt`
3. Copy `pico_sdk_import.cmake` of `pico-sdk/external` (follow https://datasheets.raspberrypi.com/pico/getting-started-
with-pico.pdf page 38)

```
mkdir build
cd build
export PICO_SDK_PATH=~/softs/pico/pico-sdk
cmake ..
make
```

- [Ref page 361](https://0xinfection.github.io/reversing/reversing-for-everyone.pdf)
- [Ref page 15](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)

### PCB Pico le Croco Ph0wn 2024

![](./images/pico-pcb.png){ width=30% } 

- Schematics [PDF](./pcb-schematics.pdf)
- LEDs du PCB Pico le Croco: https://github.com/MrYsLab/NeoPixelConnect

#### Modes de boot

Pour flasher le RP2040, il faut booter en mode BOOTSEL. Il n'y a pas de bouton pour ça sur le board de ph0wn (par simplicité, coût), on utilise une *astuce* mentionnée dans le [Hardware design with RP2040](https://datasheets.raspberrypi.com/rp2040/hardware-design-with-rp2040.pdf) qui consiste à empêcher le RP2040 de lire la mémoire Flash. Pour cela, sur le board de ph0wn, on connecte pin 1 et pin 4 (cf image), puis on insère le PCB, on laisse 2-3 secondes le temps que cela boote et on relache le pont de connexion.

![](./images/passer-en-mode-boot.jpeg)

> if we simply place a jumper wire between the pins of J2 [USB_BOOT and GND], we pull QSPI_SS pin to ground, and if the device is then subsequently reset (e.g by toggling the RUN pin), RP2040 will restart in BOOTSEL mode instead of attempting to run the contents of the flash

**Comment savoir dans quel mode de boot on est? **

Normal boot mode:

```
$ lsusb
Bus 002 Device 005: ID 2e8a:000a Raspberry Pi Pico
```

BOOTSEL mode: 
```
$ lsusb
Bus 002 Device 005: ID 2e8a:000a Raspberry Pi RP2 Boot
```

#### Flasher le firmware

- Pre-requisite: Install PICO-SDK
- Boot the device in BOOTSEL mode
- `sudo $PICO_SDK_PATH/../picotool/build/picotool load ./firmware/firmware.0.15.uf2`

#### Dumper le firmware

- Pre-requisite: Install PICO-SDK
- Boot the device in BOOTSEL mode
- `sudo $PICO_SDK_PATH/../picotool/build/picotool save firmware.uf2`


