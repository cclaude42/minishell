# minishell

42 project, recoding our own little bash. A program capable of parsing a prompt and launching executables with arguments, along with a few built-in functions.

<p align="center">
  <img src="https://i.imgur.com/En13A7p.png" width="100%" />
</p>

## Final grade : 100/115

Mandatory part : 100/100

Bonus : 0/15

### How to use it

Using ``make`` will create the ``minishell`` executable.

Simply run it with :

```
./minishell
```

### Available options

Minishell runs executables from an absolute, relative or environment PATH (``/bin/ls`` or ``ls``), including arguments or options. ``'`` and ``"`` work the same as bash, except for multiline commands.

You can separate commands with ``;``, as well as use redirections ``>`` ``>>`` ``<`` and pipes ``|``.

Environment variables are handled, like ``$HOME``, including the return code ``$?``.

Finally, you can use ``Ctrl-C`` to interrupt and ``Ctrl-\`` to quit a program, as well as ``Ctrl-D`` to throw an EOF, same as in bash.

A few of the functions are "built-in", meaning we don't call the executable, we re-coded them directly. It's the case for ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset`` and ``exit``.

### Credit

This two-person project was done with [macrespo](https://github.com/macrespo42).

I was responsible for the parsing, argument checking, execution, redirection and piping.

Macrespo took care of the environment variables, built-in functions, and signal handling.
