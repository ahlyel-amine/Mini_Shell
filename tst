((ls && echo lol) && ls -la) || echo nan
==> SEGV on unknown address
cmd "";
==> heap-use-after-free;



--------- diff in bash : -----------

< Makefile (ls && cd ) | ls | << EOF
<<EOF | < Makefile (ls && cd ) | ls


------------ ERR --------------
        ls<out