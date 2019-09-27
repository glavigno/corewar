#!/usr/bin/sh

if [[ $# -eq 1 && $1 == "--clean" ]]; then
  rm champs/*.cor
  rm champs/examples/*.cor
  printf "\e[92m> Directory champs/ cleaned\e[0m\n"
  exit
fi

# our asm program looping through all .s files
COUNT=0
TOTAL=0
printf "\e[35m[ Compilation of .s files with our asm starting ]\e[0m\n\n"
cd champs/
for i in *.s; do
    ../../assembler/asm $i &>/dev/null
    if [[ $? -ne 0 ]];then
      echo "\033[00;91m# Compilation error with our asm program\033[0m\033[00;36m  > $i \033[00;91mis invalid for some reasons\033[0m"
      let "COUNT++"
    fi
    let "TOTAL++"
done

cd examples/
for i in *.s; do
    ../../../assembler/asm $i &>/dev/null
    if [[ $? -ne 0 ]];then
      echo "\033[00;91m# Compilation error with our asm program\033[0m\033[00;36m  > $i \033[00;91mis invalid for some reasons\033[0m"
      let "COUNT++"
    fi
    let "TOTAL++"
done

echo "\n\033[00;92m> Compilation done with our asm program, $COUNT/$TOTAL files have been successfully compiled\033[0m\n"