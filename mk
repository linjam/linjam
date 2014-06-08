#!/bin/bash

LINJAM_BIN="./Builds/Linux/build/LinJam"
GDB_COMMANDS_FILE="../gdb-launch-commands"

RUN_CMD="$LINJAM_BIN"
#RUN_CMD="gdb $LINJAM_BIN -x $GDB_COMMANDS_FILE"

cd ./Builds/Linux/ && make && cd ../../ && $RUN_CMD
