#!/bin/bash

PASS=0
FAIL=0
TOTAL=0
FTLS="./ft_ls"

GREEN="\033[0;32m"
RED="\033[0;31m"
RESET="\033[0m"

mkdir -p tmp

run_test()
{
	desc="$1"
	shift
	TOTAL=$((TOTAL + 1))
	ls "$@" > tmp/ls_out.txt 2>tmp/ls_err.txt
	$FTLS "$@" > tmp/ftls_out.txt 2>tmp/ftls_err.txt
	if diff -q tmp/ls_out.txt tmp/ftls_out.txt > /dev/null 2>&1; then
		printf "  ${GREEN}✓${RESET} %s\n" "$desc"
		PASS=$((PASS + 1))
	else
		printf "  ${RED}✗${RESET} %s\n" "$desc"
		echo "    expected vs got:"
		diff --side-by-side --width=60 tmp/ls_out.txt tmp/ftls_out.txt | head -5 | sed 's/^/    /'
		FAIL=$((FAIL + 1))
	fi
}

echo ""
echo "No flags"
echo "--------"
run_test "no args" 
run_test "srcs/" srcs/
run_test "/etc" /etc
run_test "two dirs" srcs/ includes/

echo ""
echo "-a flag"
echo "--------"
run_test "-a srcs/" -a srcs/
run_test "-a /etc" -a /etc
run_test "-a two dirs" -a srcs/ includes/

echo ""
echo "-r flag"
echo "--------"
run_test "-r srcs/" -r srcs/
run_test "-r /etc" -r /etc
run_test "-r two dirs" -r srcs/ includes/

echo ""
echo "-a -r combined"
echo "--------"
run_test "-ar srcs/" -ar srcs/
run_test "-ar /etc" -ar /etc
run_test "-ra srcs/" -ra srcs/

echo ""
echo "-R flag"
echo "--------"
run_test "-R (current dir)" -R
run_test "-R srcs/" -R srcs/
run_test "-R /usr" -R /usr

echo ""
echo "-R combined"
echo "--------"
run_test "-Ra srcs/" -Ra srcs/
run_test "-Rr srcs/" -Rr srcs/
run_test "-Rar srcs/" -Rar srcs/

echo ""
echo "============================="
if [ $FAIL -eq 0 ]; then
	printf "${GREEN}All $TOTAL tests passed${RESET}\n"
else
	printf "${RED}$FAIL failed${RESET}, ${GREEN}$PASS passed${RESET} out of $TOTAL\n"
fi
echo "============================="