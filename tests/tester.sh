#!/bin/bash

MYSHELL="$PWD/mysh"
REFER="/bin/tcsh -f"
TRAPSIG=0

CAT=`which cat`
GREP=`which grep`
SED=`which sed`
RM=`which rm`
TR=`which tr`
HEAD=`which head`
TAIL=`which tail`
WC=`which wc`
CHMOD=`which chmod`
EXPR=`which expr`
MKDIR=`which mkdir`
CP=`which cp`

for i in `env | grep BASH_FUNC_ | cut -d= -f1`; do
    f=`echo $i | sed s/BASH_FUNC_//g | sed s/%%//g`
    unset -f $f
done

disp_test()
{
  id=$1
  $CAT tests/test | $GREP -A1000 "\[$id\]" | $GREP -B1000 "^\[$id-END\]" | $GREP -v "^\[.*\]"
}

run_script()
{
  SC="$1"
  echo "$SC" > /tmp/.tmp.$$
  . /tmp/.tmp.$$
  $RM -f /tmp/.tmp.$$
}

prepare_test()
{
  local testfn="/tmp/.tester.$$"
  local runnerfn="/tmp/.runner.$$"
  local refoutfn="/tmp/.refer.$$"
  local shoutfn="/tmp/.shell.$$"

  WRAPPER="$runnerfn"

  echo "#!/bin/bash" > $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "/bin/bash -c '"$testfn" | "$MYSHELL" ; echo Shell exit with code \$?' > "$shoutfn" 2>&1" >> $runnerfn
  echo "$CLEAN" >> $runnerfn
  echo "$SETUP" >> $runnerfn
  echo "$TCSHUPDATE" >> $runnerfn
  echo "/bin/bash -c '"$testfn" | "$REFER" ; echo Shell exit with code \$?' > "$refoutfn" 2>&1" >> $runnerfn
  echo "$CLEAN" >> $runnerfn

  echo "#!/bin/bash" > $testfn
  echo "$TESTS" | $TR "²" "\n" >> $testfn

  chmod 755 $testfn
  chmod 755 $runnerfn
}

load_test()
{
  id=$1
  debug=$2
  SETUP=`disp_test "$id" | $GREP "SETUP=" | $SED s/'SETUP='// | $SED s/'"'//g`
  CLEAN=`disp_test "$id" | $GREP "CLEAN=" | $SED s/'CLEAN='// | $SED s/'"'//g`
  NAME=`disp_test "$id" | $GREP "NAME=" | $SED s/'NAME='// | $SED s/'"'//g`
  TCSHUPDATE=`disp_test "$id" | $GREP "TCSHUPDATE=" | $SED s/'TCSHUPDATE='// | $SED s/'"'//g`
  TESTS=`disp_test "$id" | $GREP -v "SETUP=" | $GREP -v "CLEAN=" | $GREP -v "NAME=" | $GREP -v "TCSHUPDATE=" | $GREP -v "TESTS=" | $TR "\n" "²" | $SED s/"²$"//`
  prepare_test
  $WRAPPER
  nb=`$CAT /tmp/.refer.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $WC -l`
  i=1
  ok=1
  while [ $i -le $nb ]
  do
    l=`$CAT /tmp/.refer.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $HEAD -$i | $TAIL -1`
    a=`$CAT /tmp/.shell.$$ | $GREP -v '^_=' | $GREP -v '^\[1\]' | $GREP -- "$l$" | $WC -l`
    if [ $a -eq 0 ]
    then
      ok=0
    fi
    i=`$EXPR $i + 1`
  done

  if [ $id == 100 ]
  then
     echo -e "\e[1;36mtest minishell 2\e[0m"
  fi

  if [ $id == 01 ]
  then
    echo -e "\e[1;36mtest minishell 1\e[0m"
  fi

  if [ $ok -eq 1 ]
  then
    if [ $debug -ge 1 ]
    then
      echo -e "\e[1;32mTest $id : OK\e[0m"
      if [ $debug -eq 2 ]
      then
        echo "Output $MYSHELL :"
        $CAT -e /tmp/.shell.$$
        echo ""
        echo "Output $REFER :"
        $CAT -e /tmp/.refer.$$
        echo ""
      fi
    else
      echo "OK"
    fi
  else
    if [ $debug -ge 1 ]
    then
      echo -e "\e[1;31mTest $id : KO - Check output in /tmp/test.$$/$id/\e[0m"
      $MKDIR -p /tmp/test.$$/$id 2>/dev/null
      $CP /tmp/.shell.$$ /tmp/test.$$/$id/mysh.out
      $CP /tmp/.refer.$$ /tmp/test.$$/$id/tcsh.out
      diff /tmp/test.$$/$id/mysh.out /tmp/test.$$/$id/tcsh.out
    else
      echo "KO"
    fi
  fi
}


printf "\e[49m \e[38;5;124;49m▄\e[38;5;160;49m▄▄▄▄▄▄▄▄▄\e[49m                                 \e[38;5;160;49m▄▄▄▄▄▄▄\e[49m                                       \e[m
\e[49m \e[38;5;124;48;5;124m▄\e[38;5;160;48;5;160m▄▄▄▄▄▄▄▄\e[38;5;124;48;5;160m▄\e[49m \e[38;5;124;48;5;124m▄\e[38;5;160;48;5;124m▄▄▄▄▄▄\e[49m \e[38;5;167;48;5;167m▄\e[38;5;160;48;5;124m▄▄▄▄▄\e[38;5;160;49m▄\e[49m    \e[38;5;160;48;5;124m▄\e[38;5;160;48;5;160m▄\e[38;5;160;48;5;124m▄▄\e[38;5;131;49m▄\e[49m        \e[38;5;124;48;5;160m▄\e[38;5;160;48;5;160m▄▄▄▄▄▄▄\e[38;5;124;49m▄\e[49;38;5;174m▀\e[38;5;160;48;5;124m▄▄\e[38;5;160;48;5;131m▄\e[49m \e[38;5;209;49m▄\e[38;5;160;48;5;124m▄▄\e[38;5;124;48;5;124m▄\e[38;5;160;48;5;124m▄▄▄▄▄▄▄▄\e[38;5;124;48;5;124m▄\e[49m \e[38;5;160;48;5;124m▄▄▄▄▄▄\e[38;5;124;48;5;124m▄\e[49m  \e[38;5;160;49m▄\e[38;5;160;48;5;124m▄▄\e[38;5;160;48;5;160m▄\e[38;5;160;48;5;124m▄\e[38;5;160;49m▄\e[49m   \e[m
\e[49m \e[49;38;5;173m▀\e[49;38;5;172m▀▀\e[38;5;179;48;5;172m▄\e[38;5;208;48;5;208m▄▄\e[38;5;172;48;5;208m▄\e[49;38;5;172m▀▀\e[49;38;5;173m▀\e[49m \e[38;5;172;48;5;208m▄\e[38;5;208;48;5;208m▄▄\e[49;38;5;208m▀▀▀▀\e[49m \e[38;5;179;48;5;215m▄\e[38;5;208;48;5;208m▄▄\e[38;5;94;48;5;208m▄\e[49;38;5;208m▀\e[38;5;208;48;5;208m▄▄▄\e[49m   \e[38;5;208;48;5;208m▄▄▄▄\e[38;5;172;48;5;172m▄\e[49m        \e[38;5;172;48;5;208m▄\e[38;5;208;48;5;208m▄▄\e[38;5;172;48;5;172m▄\e[49;38;5;172m▀\e[38;5;172;48;5;172m▄\e[38;5;208;48;5;208m▄▄\e[38;5;172;48;5;172m▄\e[49m \e[49;38;5;173m▀\e[38;5;208;48;5;208m▄▄\e[38;5;172;49m▄\e[38;5;208;48;5;208m▄▄▄\e[49m \e[49;38;5;208m▀▀▀\e[38;5;208;48;5;208m▄▄▄\e[49;38;5;208m▀▀\e[49;38;5;172m▀\e[49m \e[38;5;208;48;5;208m▄▄\e[38;5;172;48;5;208m▄\e[49;38;5;208m▀▀▀\e[49;38;5;172m▀\e[49m \e[38;5;172;48;5;208m▄\e[38;5;208;48;5;208m▄▄\e[49;38;5;208m▀\e[38;5;95;48;5;208m▄\e[38;5;208;48;5;208m▄▄▄\e[49m  \e[m
\e[49m    \e[38;5;221;48;5;185m▄\e[38;5;220;48;5;11m▄\e[38;5;11;48;5;11m▄\e[38;5;221;48;5;220m▄\e[49m    \e[38;5;220;48;5;220m▄\e[38;5;11;48;5;220m▄\e[38;5;220;48;5;11m▄\e[38;5;11;49m▄\e[38;5;220;49m▄▄▄\e[49m \e[38;5;185;48;5;221m▄\e[38;5;220;48;5;11m▄\e[38;5;11;48;5;11m▄\e[38;5;11;48;5;101m▄\e[38;5;11;49m▄\e[38;5;11;48;5;11m▄\e[38;5;11;48;5;220m▄\e[38;5;220;48;5;11m▄\e[49m  \e[38;5;221;48;5;221m▄\e[38;5;220;48;5;11m▄\e[38;5;11;48;5;11m▄\e[38;5;220;48;5;220m▄\e[38;5;11;48;5;11m▄\e[38;5;220;48;5;11m▄\e[49m        \e[38;5;221;48;5;220m▄\e[38;5;220;48;5;11m▄\e[38;5;11;48;5;11m▄\e[38;5;11;48;5;220m▄\e[38;5;11;48;5;221m▄\e[38;5;11;48;5;220m▄\e[38;5;220;48;5;11m▄\e[38;5;11;48;5;220m▄\e[49;38;5;11m▀\e[49m  \e[38;5;185;48;5;220m▄\e[38;5;220;48;5;11m▄\e[38;5;11;48;5;11m▄\e[38;5;220;48;5;11m▄\e[38;5;11;48;5;220m▄\e[49m     \e[38;5;11;48;5;11m▄▄\e[38;5;220;48;5;220m▄\e[49m    \e[38;5;11;48;5;11m▄\e[38;5;220;48;5;220m▄\e[38;5;220;48;5;11m▄\e[38;5;11;49m▄\e[38;5;220;49m▄▄\e[38;5;221;49m▄\e[49m \e[38;5;220;48;5;220m▄\e[38;5;11;48;5;11m▄\e[38;5;11;48;5;220m▄\e[38;5;11;49m▄\e[38;5;220;49m▄▄\e[49m    \e[m
\e[49m    \e[38;5;72;48;5;107m▄\e[38;5;2;48;5;2m▄▄\e[38;5;2;48;5;22m▄\e[49m    \e[38;5;2;48;5;2m▄▄▄▄▄▄▄\e[49m \e[38;5;65;48;5;65m▄\e[38;5;2;48;5;2m▄▄▄▄▄▄\e[38;5;238;49m▄\e[49m  \e[38;5;2;48;5;2m▄▄▄\e[49;38;5;58m▀\e[38;5;2;48;5;2m▄▄\e[38;5;239;49m▄\e[49m       \e[38;5;29;48;5;64m▄\e[38;5;2;48;5;2m▄▄▄▄▄▄\e[38;5;2;48;5;235m▄\e[38;5;2;49m▄\e[49m   \e[38;5;23;48;5;2m▄\e[38;5;2;48;5;2m▄▄\e[49;38;5;58m▀\e[49m     \e[38;5;2;48;5;2m▄▄▄\e[49m    \e[38;5;2;48;5;2m▄▄▄▄▄▄\e[38;5;236;48;5;237m▄\e[49m \e[49;38;5;64m▀\e[38;5;29;48;5;2m▄\e[38;5;2;48;5;2m▄▄▄▄▄\e[38;5;2;49m▄\e[49m  \e[m
\e[49m    \e[38;5;68;48;5;67m▄\e[38;5;27;48;5;24m▄▄\e[38;5;26;48;5;24m▄\e[49m    \e[38;5;27;48;5;24m▄▄▄\e[49m     \e[38;5;68;48;5;67m▄\e[38;5;27;48;5;24m▄▄\e[38;5;61;48;5;240m▄\e[49m \e[38;5;27;48;5;24m▄▄▄\e[49m \e[38;5;110;49m▄\e[38;5;27;48;5;24m▄▄▄\e[38;5;27;48;5;25m▄\e[38;5;27;48;5;24m▄▄▄\e[49m       \e[38;5;27;48;5;24m▄▄▄\e[38;5;26;48;5;24m▄\e[49m \e[38;5;62;48;5;6m▄\e[38;5;27;48;5;24m▄▄▄\e[49m   \e[38;5;26;48;5;24m▄\e[38;5;27;48;5;24m▄▄\e[49m      \e[38;5;27;48;5;24m▄▄▄\e[49m    \e[38;5;27;48;5;24m▄▄▄\e[49m     \e[38;5;26;49m▄▄▄\e[49m  \e[38;5;27;48;5;24m▄▄▄\e[49m  \e[m
\e[49m    \e[38;5;133;48;5;104m▄\e[38;5;5;48;5;27m▄\e[38;5;5;48;5;26m▄\e[38;5;53;48;5;26m▄\e[49m    \e[38;5;54;48;5;26m▄\e[38;5;5;48;5;27m▄▄▄\e[38;5;5;48;5;26m▄▄▄\e[49m \e[38;5;97;48;5;68m▄\e[38;5;5;48;5;27m▄▄\e[38;5;242;48;5;60m▄\e[49m \e[38;5;5;48;5;26m▄▄\e[38;5;5;48;5;27m▄\e[49m \e[38;5;5;48;5;61m▄\e[38;5;5;48;5;27m▄▄\e[49;38;5;26m▀\e[49;38;5;27m▀\e[38;5;5;48;5;27m▄▄\e[38;5;5;48;5;26m▄\e[49m       \e[38;5;90;48;5;62m▄\e[38;5;5;48;5;27m▄\e[38;5;54;48;5;27m▄\e[38;5;5;48;5;27m▄▄▄▄\e[38;5;5;48;5;26m▄\e[49;38;5;26m▀\e[49m   \e[38;5;5;48;5;62m▄\e[38;5;5;48;5;27m▄▄\e[49m      \e[38;5;5;48;5;27m▄▄\e[38;5;5;48;5;26m▄\e[49m    \e[38;5;5;48;5;26m▄\e[38;5;5;48;5;27m▄\e[38;5;5;48;5;26m▄\e[38;5;5;48;5;27m▄▄\e[38;5;5;48;5;26m▄\e[38;5;5;48;5;62m▄\e[49m \e[38;5;139;48;5;26m▄\e[38;5;5;48;5;26m▄\e[38;5;5;48;5;27m▄\e[38;5;5;48;5;26m▄\e[38;5;5;48;5;27m▄▄▄\e[38;5;54;48;5;26m▄\e[49m  \e[m
\e[49m    \e[49;38;5;133m▀\e[49;38;5;5m▀▀▀\e[49m    \e[49;38;5;54m▀\e[49;38;5;5m▀▀▀▀▀▀\e[49m \e[49;38;5;97m▀\e[49;38;5;5m▀▀\e[49;38;5;242m▀\e[49m \e[49;38;5;5m▀▀▀\e[49m \e[49;38;5;5m▀▀▀\e[49m  \e[49;38;5;96m▀\e[49;38;5;5m▀▀\e[49;38;5;96m▀\e[49m      \e[49;38;5;5m▀▀▀▀▀▀▀\e[49m     \e[49;38;5;53m▀\e[49;38;5;5m▀▀\e[49m      \e[49;38;5;5m▀▀▀\e[49m    \e[49;38;5;5m▀▀▀▀▀▀\e[49;38;5;53m▀\e[49m  \e[49;38;5;103m▀\e[49;38;5;5m▀▀▀▀\e[49;38;5;241m▀\e[49m   \e[m
\e[49m                                                                                          \e[m
\n\n";
if [ $TRAPSIG -eq 1 ]
then
  for sig in `trap -l`
  do
    echo "$sig" | grep "^SIG" >/dev/null 2>&1
    if [ $? -eq 0 ]
    then
      trap "echo Received signal $sig !" $sig
    fi
  done
fi

if [ ! -f tests/test ]
then
  echo "No test file. Please read README.ME" >&2
  exit 1
fi

if [ ! -f $MYSHELL ]
then
  echo "$MYSHELL not found" >&2
  exit 1
fi

# if [ $# -eq 2 ]
# then
#   echo "Debug mode" >&2
#   echo "Shell : $MYSHELL" >&2
#   echo "Reference : $REFER" >&2
#   echo ""
# fi

if [ $# -eq 0 ]; then
  for lst in $(cat tests/test | grep "^\[.*\]$" | grep -vi end | sed 's/\[//; s/\]//'); do
    path_backup=$PATH
    load_test "$lst" 1
    export PATH=$path_backup
  done
elif [ $# -eq 1 ] && [ "$1" == "minishell1" ]; then
  for lst in $(cat tests/test | grep "^\[.*\]$" | grep -vi end | sed 's/\[//; s/\]//'); do
    path_backup=$PATH
    if [ "$1" == "minishell1" ] && [ "$lst" -ge 0 ] && [ "$lst" -le 99 ]; then
      load_test "$lst" 1
    fi
    export PATH=$path_backup
  done
elif [ $# -eq 1 ] && [ "$1" == "minishell2" ]; then #copier et remplacer la derniere variable
  for lst in $(cat tests/test | grep "^\[.*\]$" | grep -vi end | sed 's/\[//; s/\]//'); do
    path_backup=$PATH
    if [ "$lst" -ge 100 ] && [ "$lst" -le 200 ]; then #changez les valeurs pour mettre celles de vos tests
      load_test "$lst" 1
    fi
    export PATH=$path_backup
  done
fi
echo -e "\n\e[31mm\e[33ma\e[32md\e[36me\e[34m \e[35mb\e[31my\e[33m \e[32mn\e[36mi\e[34mc\e[35mo\e[0m\e[31ml\e[33ma\e[32ms\e[36m\e[34m\e[35m"
