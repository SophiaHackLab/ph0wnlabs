# Ph0wn Labs 04

## Workshop Docker Container :whale:

Please pull the workshop's container: `docker pull cryptax/ph0wnlabs:4`.
It bundles a working r2 and r2ai.

Then, run the container:

- with docker compose: `docker compose run --rm ph0wnlabs-4`
- or directly with docker: `docker run -it --rm --name ph0wnlabs-4 cryptax/ph0wnlabs:4`

Alternatives:

- If you don't want to pull the container, you can build it: `docker compose build`
- Or you can install the latest [Radare2](https://www.radare.org/n/radare2.html) and r2ai (see `Dockerfile` to see how).

## API keys :key:

- Get free API keys from [Groq](https://console.groq.com) and put it in a file named `~/.r2ai.groq-key`. 

- Share the key with your container: `docker cp ~/.r2ai.groq-key <CONTAINERID>:/home/work`. :warning: **Don't forget to put it in `/home/work`!**

```
$ docker ps
CONTAINER ID   IMAGE                 COMMAND                  CREATED         STATUS         PORTS                                         NAMES
6b7d2c56470b   cryptax/ph0wnlabs:4   "/bin/bash"              6 seconds ago   Up 6 seconds                                                 lab-04-ph0wnlabs-4-run-67bf1d22bfdd
...
$ docker cp ~/.r2ai.groq-key 6b7d2c56470b:/home/work
Successfully copied 2.05kB to 6b7d2c56470b:/home/work
```


- :moneybag: [Anthropic Claude Sonnet 3.5+](https://console.anthropic.com/) are (honestly) incomparably better for code. If you can afford it, get an API key. You don't need more than 5 USD on your account.

## CrackMe binary :lock:

Explore the Space with our **Docking Station** :rocket:, written in Rust. 
You need to find the correct docking authorization code... :satellite:

Reverse engineering *Rust* is said to be relatively challenging, even for experienced reverse engineers. Get help from the Artificial Intelligence! :brain:

> The goal of this lab is to solve the CrackMe with **assistance** from **Artificial Intelligence**. We demonstrate a solution with r2ai, the AI plugin of Radare2, but you are *welcome to use any sort of Artificial Intelligence* and share your findings with others. 
> In particular, if you know about them, you might want to use adequate *MCP servers*. We won't have time to discuss that in this lab, but it's a perfectly valid solution.

```
./dockcode 
Enter docking authorization code: hello
Authorization failed. Access denied.
```

## Useful references :books:

- :link: [Rust in your disassembler](https://cryptax.medium.com/rust-in-your-disassembler-1aa700c3b041)
- Follow my talk at :link: [r2con 2025](https://www.radare.org/con/2025/)!
- :link: [Deconstructing Hello World](https://rayoflightz.github.io/re/rust/2020/05/19/Bite-Sized-Rust-RE-1-Deconstructing-Hello-World.html)
- :link: [Rust binary analysis](https://research.checkpoint.com/2023/rust-binary-analysis-feature-by-feature/)

## Guided Lab with r2ai :test_tube:

1. Launch radare2 on the binary:  `r2 ./dockcode` :computer:
2. Which programming language does this binary use? Hint: `iI`
3. Analyze the binary (`aaa`) :mag_right:, list the functions (`afl`), go to the function which is the **main** of our program

> **r2 help**:
> In r2, to go to a given address/function, use `s ADDR`
> To *grep* output, use `~WORD`. For example to find all functions that contain the word "main": `afl~main`
> To disassemble a function: `pdf @ FUNCNAME`, or `s FUNCNAME` and then `pdf`.

> What is the **main of our program**? In many languages (C, Rust...), it's not the entrypoint of the binary, but called a bit later. You shouldn't have too much trouble locating it.


4. Set up Groq in r2ai: `r2ai -e api=groq`. Then, try various models to decompile the main, until you get code that shows an *authorization code* (we'll test afterwards if it's correct or not, don't bother at this stage).

> **r2ai help**
> To list models for a given provider: `r2ai -e model=?`
> To set a given model: `r2ai -e model=MODELNAME`
> To decompile the current function: `r2ai -d`
> Help? `r2ai -h`

We are reversing **Rust**. 
You may want to set the decompiled output to Rust: `r2ai -e lang=rust`.


- **Question 5**. If you can, test this authorization code. If it works, congrats! Most probably though, it will be incorrect... (and that's perfectly normal).

> **Not on Linux** :penguin:? Perhaps you can run the binary using QEMU + Docker to emulate a foreign architecture [see here](https://forums.docker.com/t/run-x86-intel-and-arm-based-images-on-apple-silicon-m1-macs/117123).

> **Catch Up!** If you failed to get a source code that produces something that looks like an authorization code, read [`./spoiler/dockcode-main.rs`](./spoiler/dockcode-main.rs) and assume this was returned by your model.

- **Question 6**. Is that incorrect authorization code a hallucination? Check it out in the binary!

> Hint: no, it's *not* a hallucination. Look at the very beginning of the function.

- **Question 7**. Using radare2, locate where string comparison occurs :microscope:

> Hint: how can I search for the call of a given function in another?
>- `axf` lists all calls *from* a given function, but it doesn't always work well.
>- `pdf` shows the disassembly of a given function. So you can grep the output for `cmp`, e.g `pdf~cmp`.
>- There are many other ways, like `pdc~cmp`. Or search globally for a `cmp` function with `afl~cmp`, then search who is using that function with `axt @ funcname`.


- **Question 8**. Once you have located the address where string comparison occurs, work out **which strings are being compared**.

> **r2 help**
>- Get details on the current calling convention with r2 command `afci`. This tells you in which registers arguments for functions are stored.
>- To move a few bytes before where you are, `s-BYTES`.
>- You may find the visual mode handy to see what happens before string comparison. To switch to visual mode, use `VV`.
>- Find where variables are read or written with `axv~VARIABLE_NAME`

You should have worked out:

1. The user input string variable
2. The fixed string it is compared with.

This fixed string emanates from a character array (in many cases, this is what the AI took for the authorization code at first), but it is modified in a *closure*.

- **Question 9**. Search for **closures** in our binary. 

> *Hint: search for functions containing the name "dockcode"*.
> Don't know what a *closure* is? Ask ChatGPT.

- **Question 10**. Get the call stack for this closure using command `axg FUNCTION_NAME`. Where is this function called in our main? Is it modifying the fixed string, or the user input?
- **Question 11**. Use Groq and model `moonshotai/kimi-k2-instruct` and ask for explanations **on the closure**. 

> *Hint: r2ai -x*

- **Question 12** :flags:. Based on your understanding of the closure, generate the correct authorization code :rocket: :tada: :medal_sports:

