# TO DO

* SEGFAULT IN EXPANSIONS since recent fixed, don't know why
* invalid read/write in expansion (classic case like $HOME)
* echo    $TEST lol $TEST
* echo $TEST$TEST=lol$TEST""lol
* export TEST ; export | grep TEST

## DONE
* 16 bytes leaks ?? leaks in sort env, export, env_init ✅
* echo $TEST $TEST ✅
* export = ✅
* ctrl-D in command type "wc" ✅
* protect malloc in parsings function + norme ✅
* norm ft_abs and type.c (bug ??) ✅
* echo "\$TEST" ✅
* > ls ✅

## MAYBE TO DO

* some strange bug ??
* some leaks / invalid read/write with others features (pipe / redir / builtins etc...)
* mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd (Error messages?)
* ;; test
