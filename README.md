# minishell

42 project, recoding our own little bash. A program capable of parsing a prompt and launching executables with arguments, along with a few built-in functions.

## Final grade : 100/115

Mandatory part : 100/100

Bonus : 0/15

/bin/ls
echo "<  Hello World !  >" > file.txt
cat file.txt
ls -la | grep ll
echo $HOME ; fffff
echo $?
exit

<p align="center">
  <img src="https://imgur.com/a/ro4WvYF" width="60%" />
</p>

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
