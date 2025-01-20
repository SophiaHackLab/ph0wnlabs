# CrackMe Baby 3

- `./labs-01/bins/crackme-baby3`

> This is an ELF executable for Linux. 
> Non-Linux users: you don't need to execute it to solve the CrackMe. No worry.

```
$ ./crackme-baby3
=== I am the Loch Ness Monster ===
Password: 
```

The encrypted password is `/CUVGT4CFCTG`. 

1. Work out the encryption algorithm (it is a very simple one) around 0x00001222
2. Invoke a Python REPL (or any other solution  you prefer) to find the decrypted password.

## Guided solution

<details>
<summary>Spoiler</summary>

The algorithm perform -0x1e to each character (see 0x00001227).
So, we need to do the opposite with Python:

```
[0x000010a0]> !python3
>>> s = '/CUVGT4CFCTG'
>>> [ chr(ord(x) + 0x1e) for x in s ]
['M', 'a', 's', 't', 'e', 'r', 'R', 'a', 'd', 'a', 'r', 'e']
>>> quit()
```
</details>
