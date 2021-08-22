# Typing `ls -l *.c` In The Shell

When you type a line of command in the shell, it has to be processed by the underlying shell program and some result is produced. The result could mean either a successful or an unsuccessful output. However as programmers, computer geeks or just people with knowledge about the computer, we know there's a lot more that goes on behind the scenes for that to happen. I would be explaining much of what happens behind the scenes in the best way that I currently can.

When the shell is given a line of command(s), the line of command(s) are broken down into parts that can be individually processed. The main parts that the line of commands(s) are broken down into are *words* and *operators*. This is what we would call the *tokenization* stage.

Words are a contiguous block of characters that aren't quoted operators or whitespaces. Operators are a non-alphabetic set of characters and could include the characters `; < > | &`

At this stage, a simple syntax checking can be performed to ensure that the line of input has been written properly.

The substitution is performed before any parsing or expansion is done. This means that if you had typed any command that could change the outcome of a subsequent command, it wouldn't be in effect until the next line of commands are processed by the shell.

So, back to our command of focus (`ls -l *.c`)
The line of command can be split into 3 words, `ls`, `-l`, and `*.c`.

These words are then passed through the substitution stage, where they are compared with a list of words that can be substituted and if the context they appear in allows the substitution to occur, they would be replaced. This is because, although a word can be substituted because it matches the name of an alias, if the previous word did not end with a blank, an operator and it isn't the first word, it wouldn't be replaced. This is shown in the image below.

<!-- Image showing an alias word that isn't replaced -->

According to the shell semantic@@#$@$#$ rules, the first word on the line or after an operator has to be a command word. This means `ls` would have to be a command. The remaining words are then interpreted as arguments to the `ls` command.

After separating the words, they are passed through to the expansion phase. This stage is where quotes are removed, variables and parameters are substituted, tildes may be replaced, pathnames are expanded, and so on. If `ls` and `-l` weren't substituted in the substitution stage, they would remain the same in this stage as they're not susceptible to tilde, variable, pathname, or arithmetic expansion.

However, `*.c` would undergo some changes. It would be affected by the filename expansion. This is where files and directories whose names match the pattern `*.c` are retrieved and used to replace `*.c`. So if we had directories or filenames ending with `.c` in the current working directory (A.K.A **PWD**), they would be retrieved and replace the value of `*.c` in the program. Each file or directory name would have to be separated by a space (an operator cannot be used) to ensure that they're treated as separate words. If an operator were to be used to separate the file and directory names, it would lead to a different interpretation of the words. Spaces have no side effects, except separating words when they're unquoted. Operators have side effects which affect how commands are executed.

So, assuming my current working directory had the following files and folders.

<img src="./img-3.png" alt="Image of a directory structure having 4 files and 1 folder"/>

The line of command (`ls -l *.c`) would be expanded to

```bash
ls -l libs.c main.c str_utils.c xml_helpers.c
```

The final stage would involve the shell doing something about the expansion that has just taken place. This would be the execution phase.

The priority of execution is that a shell built-in command is executed over a system program. If the command `ls` is a built-in command, the shell calls the associated function and passes it the arguments it could retrieve. However if it isn't a built-in command, the shell searches the directories that are stored in the **PATH** environment variable in order to find the absolute path to the program. It stops on the first path that it finds, so if you want to prioritize the execution of one global program over another with the same filename in your shell, you would have to place its directory higher up in the list of directories stored in **PATH**.


After the shell was able to retrieve the absolute path, which could be `/bin/ls`, it would spawn a new process using the **fork** system call. After that, it would call one of the **exec** family of system calls to execute the program using the pathname it retrieved, a copy of the arguments to be passed to the program as well as a copy of the shell's current environment variables. In the new process, the return value of the **exec** syscall is passed to the **exit** function. This would allow sub-process to exit if it fails. The shell would have to wait for the newly spawned process using the **wait** system call and receive its exit code.



Everything that happens in the shell isn't always fixed. In the shell, it is possible to make `ls -l *.c` produce a different result using *aliases* as shown below:

```bash
alias ls='ls '
alias -l='-a --classify'
ls -l
```

I recently made a simple shell in **C** with my project partner Elmahdi Mamoun during my time at ALX. You can find the entire source code [here](https://github.com/Elmahdi1962/simple_shell) on GitHub. The shell performs some simple operations you would expect a shell to perform. It runs some built-in commands, performs variable expansions, executes programs and can read lines of commands from a text file. We learned so much whilst working on the project. Despite how much trouble it gave us, we believe the trouble we had to go through to make the shell program was completely worth it.
