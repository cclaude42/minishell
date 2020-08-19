# TO DO

* 16 bytes leaks ??
* invalid read/write in expansion (classic case like $HOME)
* echo "\$TEST"
* echo    $TEST lol $TEST
* echo $TEST $TEST ✅
* export = ✅
* ctrl-D in command type "wc" ✅

## COMMANDS THAT WORK DIFFERENT TO BASH

* protect malloc in parsings function + norme
* norm ft_abs and type.c (bug ??)
* mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd ----??NO CRASH, IS A REAL PROB??
* echo $TEST$TEST=lol$TEST""lol
* export TEST ; export | sort (missing the invalid exports, like =, that aren't in env. try "export =" and then "export", see the diff) -------------Not an export prob
* ;; test
* > ls ✅

## MAYBE TO DO

* some strange bug ??
* some leaks / invalid read/write with others features (pipe / redir / builtins etc...)
