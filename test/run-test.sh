#!/bin/sh
set -e

# $1 = compiler
EXT="rkt"

OUT="a.out"
OFILES=""
AS="riscv64-linux-gnu-as"
LD="riscv64-linux-gnu-ld"

# compile every rkt file
echo "Compiling..."
for file in ./src/*.${EXT}; do
    ASMfile="${file%."${EXT}"}.s"
    echo "$ $1" "$file" "$ASMfile"
           "$1" "$file" "$ASMfile" # compile file .rkt -> .s
done

# assemble
echo "Assembling..."
for file in ./src/*.s; do
    Ofile="${file%.s}.o"
    OFILES="$OFILES $Ofile"
    echo "$ $AS" "$file" "-o" "$Ofile"
           "$AS" "$file" "-o" "$Ofile" # assembly file .s -> .o
done

echo "Linking..."
# link
echo "$" "$LD $OFILES -o $OUT"
         "$LD" $OFILES -o $OUT

# remove .o files
rm src/*.o



