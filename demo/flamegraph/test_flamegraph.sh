#!/usr/bin/env bash

fg_perl=/home/vm_share/git/FlameGraph/flamegraph.pl
stack_stap=/home/vm_share/git/FlameGraph/stackcollapse-stap.pl

function usage ()
{
    cat << EOF
        $0 bin_file pid
EOF
}

function main ()
{
    if [ $# -ne 2 ]; then
        usage
    else
        stap --ldd -d $1 --all-modules -D MAXMAPENTRIES=10240 -D MAXACTION=20000 -D MAXTRACE=100 -D MAXSTRINGLEN=4096 -D MAXBACKTRACE=100 -x $2 trap.stp > tmp.out
        perl $stack_stap tmp.out > tmp.out.1
        perl $fg_perl tmp.out.1 > tmp.svg
    fi
}

main $*

