# Simple Shell

![Repo size](https://img.shields.io/github/repo-size/Elmahdi1962/simple_shell)

This is a simple Unix shell implemented in __C__.

## How To Use

Run the command below to build the shell.

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

Then run `$ ./hsh` to startup the shell in interactive mode. To start the shell in non-interactive mode, run `$ ./hsh file`, where `file` is a text-encoded file containing a list of commands to be executed.
