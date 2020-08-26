# TO DO
Ready to turn in

## DONE
* echo    $TEST lol $TEST ✅
* export TEST ; export | grep TEST ✅
* SEGFAULT IN EXPANSIONS (export test=lol ; echo $test) ✅
* invalid read/write in expansion (classic case like $HOME) ✅
* 16 bytes leaks ?? leaks in sort env, export, env_init ✅
* echo $TEST $TEST ✅
* export = ✅
* ctrl-D in command type "wc" ✅
* protect malloc in parsings function + norme ✅
* norm ft_abs and type.c (bug ??) ✅
* echo "\$TEST" ✅
* > ls ✅
* Warning: invalid file descriptor -1 in syscall close() ✅

## MAYBE TO DO

* some strange bug ??
* some leaks / invalid read/write with others features (pipe / redir / builtins etc...)
* mkdir test_dir ; cd test_dir ; rm -rf ../test_dir ; cd . ; pwd ; cd . ; pwd ; cd .. ; pwd (Error messages?)
* ;; test
* 2 bytes "still reachable"
* ~10,000 bytes "still reachable" when trying bad command
* echo $TEST$TEST=lol$TEST""lol
