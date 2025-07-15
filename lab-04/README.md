In this session, you have a couple of CrackMe binaries. The goal of the session is to solve them using AI, either with Radare's R2AI plugin, or with GhidraMCP.

Please install [Exegol](https://github.com/ThePorgs/Exegol), which contain both Ghidra and Radare2. Alternatively, you may install manually [Ghidra](https://github.com/NationalSecurityAgency/ghidra) and [Radare2](https://www.radare.org/n/radare2.html).

# Installing the AI components

## R2AI

Once Radare2 is installed on your system:

```
r2pm -ci r2ai decai
```

## GhidraMCP

Follow the [install instructions](https://github.com/LaurieWired/GhidraMCP)

## API keys

- Get free API keys from [Mistral](https://console.mistral.ai) or [Groq](https://console.groq.com) and store the keys on your host, e.g `~/.r2ai-mistral.key`, `~/.r2ai-groq.key`.

- [Anthropic Claude Sonnet 3.5+](https://console.anthropic.com/) are (honestly) incomparably better for code. If you can afford it, get an API key. You don't need more than 5 USD on your account.


# CrackMe binaries

Explore Space with our CrackMe binaries:

- Space GPS system. Written in Go.
- Docking authorization code. Written in Rust.
- Mars Orbital Solar Alignment System. Written in C.
- Break My ARM (Ph0wn 2019). 

NB. If you have experience in reverse engineering, you won't find those difficult to solve. The goal of the workshop is to *learn to solve them with r2ai or ghidramcp*.



