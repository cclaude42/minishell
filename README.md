# TO DO

* 16 bytes leaks ??
* invalid read/write in expansion (classic case like $HOME)
* protect malloc in parsings function + norme
* norm ft_abs and type.c (bug ??)

## COMMANDS THAT WORK DIFFERENT TO BASH
* mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd
* echo    $TEST lol $TEST
* echo $TEST$TEST=lol$TEST""lol
* echo "\$TEST"
* echo $TEST $TEST
* export =
* export TEST ; export | sort (missing the invalid exports, like =, that aren't in env. try "export =" and then "export", see the diff)
* ;; test
* ctrl-D in command type "wc"
* > ls

## MAYBE TO DO

* some strange bug ??
* some leaks / invalid read/write with others features (pipe / redir / builtins etc...)
