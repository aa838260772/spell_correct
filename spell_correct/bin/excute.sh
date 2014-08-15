#!/bin/bash
function start
{
   ./main >> ../log/log.txt
}
function stop
{
    killall -9 main
}
function restart
{
    killall -9 main
    ./main &
}
function stat
{
    ps -ef | grep main
}
case $1 in
start) start;;
stop ) stop;;
restart) restart;;
stat) stat;;
*) echo "Ignore...";;
esac
