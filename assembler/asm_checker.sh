#!/usr/bin/sh

if [[ $# -eq 1 && $1 == "--clean" && -d asm_checker/ ]]; then
  rm -rf asm_checker/
  printf "\e[34m# Directory asm_checker deleted\e[0m\n"
  make fclean &>/dev/null
  printf "\e[34m# Make fclean execution\e[0m\n"
  printf "\e[92m> Asm repository cleaned\e[0m\n"
  exit
elif [[ $# -eq 1 && $1 == "--clean" && ! -d asm_checker/ ]]; then
  printf "\e[91m# Nothing to clean\e[0m\n"
  exit
fi

# preliminary check
if [[ ! -f asm ]];then
  printf "\e[35m[ Compilation of asm executable starting ]\e[0m\n\n"
  make &>/dev/null
  printf "\e[92m> ASM compilation done\e[0m\n\n"
else
  printf "\e[91m! ASM executable already exists\e[0m\n\n"
fi

if [[ ! -d asm_checker/ ]];then
  mkdir asm_checker/
  printf "\e[33m# Directory asm_checker created\e[0m\n"
  mkdir asm_checker/our_cor && mkdir asm_checker/zaz_cor
  printf "\e[33m# Subdirectories our_cor and zaz_cor created\e[0m\n\n"
fi

# compilation of .s files with both zaz and our asm binary
# our asm program looping through all .s files
COUNT=0
TOTAL=0
printf "\e[35m[ Compilation of .s files with our asm starting ]\e[0m\n\n"
for i in resources/champions/*; do
  if [[ ! $(ls asm_checker/our_cor) ]];then
    ./asm $i &>/dev/null
    if [[ $? -ne 0 ]];then
      echo "\033[00;91m# Compilation error with our asm program\033[0m\033[00;36m  > $i \033[00;91mis invalid for some reasons\033[0m"
      let "COUNT++"
    fi
    let "TOTAL++"
  fi
done

if [[ ! $(ls asm_checker/our_cor) ]];then
  mv resources/champions/*.cor asm_checker/our_cor/.
  echo "\n\033[00;92m> Compilation done with our asm program, $COUNT/$TOTAL files have been successfully compiled\033[0m\n"
else
  printf "\e[36m! Directory asm_checker/our_cor/ already populated\e[0m\n\n"
fi
# zaz asm program looping through all .s files
COUNT=0
TOTAL=0
printf "\e[35m[ Compilation of .s files with zaz asm starting ]\e[0m\n\n"
for i in resources/champions/*; do
  if [[ ! $(ls asm_checker/zaz_cor) ]];then
    ./resources/asm $i &>/dev/null
    if [[ $? -ne 0 ]];then
      echo "\033[00;91m# Compilation error with zaz asm program\033[0m\033[00;36m  > $i \033[00;91mis invalid for some reasons\033[0m"
      let "COUNT++"
    fi
    let "TOTAL++"
  fi
done

if [[ ! $(ls asm_checker/zaz_cor) ]];then
  mv resources/champions/*.cor asm_checker/zaz_cor/.
  echo "\n\033[00;92m> Compilation done with zaz asm program, $COUNT/$TOTAL files have been successfully compiled\033[0m\n"
else
  printf "\e[36m! Directory asm_checker/zaz_cor/ already populated\e[0m\n\n"
fi
DIFF_MESS=$(diff -rq asm_checker/our_cor/ asm_checker/zaz_cor/)
printf "\e[35m[ Check diff between output files starting ]\e[0m\n\n"
if [[ ! $DIFF_MESS ]];then
  printf "\e[92m> No diff detected between zaz and our .cor files\e[0m\n\n"
else
  printf "\e[91m> Diff detected .cor files\e[0m\n"
  echo "\033[00;35m# $DIFF_MESS...\033[0m\n"
fi
  