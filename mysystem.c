/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース

char *execpath = "/bin/sh";
// system関数のクローン
int mysystem(char *command) {
  int status = 0;
  int pid = 0;
  if(command == NULL){
    return 1;
  }
  if((pid = fork()) < 0){
    return -1;
  }
  if(pid != 0){
    while(wait(&status) != pid);
  } else{
    execl(execpath, "sh", "-c", command, NULL);
    perror(execpath);
    exit(127);
  }
  return status;
}

/* 実行例

ここに実行例を書く
コンパイル：
% make
cc -Wall -std=c99 -o mysysmain mysysmain.c  mysystem.c

実行：
①コマンドラインで実行
ls -l
total 616
-rw-r--r--  1 domino  staff     143  7  4 10:14 Makefile
-rw-r--r--  1 domino  staff    2795  7  4 10:14 README.md
-rw-r--r--  1 domino  staff  238232  7  4 10:14 README.pdf
-rwxr-xr-x  1 domino  staff   50406  7  9 22:21 mysysmain
-rw-r--r--  1 domino  staff     925  7  4 10:14 mysysmain.c
-rw-r--r--  1 domino  staff     809  7  9 22:22 mysystem.c
-rw-r--r--  1 domino  staff      90  7  4 10:14 mysystem.h

②mysystemで実行し検証してみる
% ./mysysmain "ls -l"
mysystem:
total 616
-rw-r--r--  1 domino  staff     143  7  4 10:14 Makefile
-rw-r--r--  1 domino  staff    2795  7  4 10:14 README.md
-rw-r--r--  1 domino  staff  238232  7  4 10:14 README.pdf
-rwxr-xr-x  1 domino  staff   50406  7  9 22:21 mysysmain
-rw-r--r--  1 domino  staff     925  7  4 10:14 mysysmain.c
-rw-r--r--  1 domino  staff    1278  7  9 22:23 mysystem.c
-rw-r--r--  1 domino  staff      90  7  4 10:14 mysystem.h
retval = 00000000
system:
total 616
-rw-r--r--  1 domino  staff     143  7  4 10:14 Makefile
-rw-r--r--  1 domino  staff    2795  7  4 10:14 README.md
-rw-r--r--  1 domino  staff  238232  7  4 10:14 README.pdf
-rwxr-xr-x  1 domino  staff   50406  7  9 22:21 mysysmain
-rw-r--r--  1 domino  staff     925  7  4 10:14 mysysmain.c
-rw-r--r--  1 domino  staff    1278  7  9 22:23 mysystem.c
-rw-r--r--  1 domino  staff      90  7  4 10:14 mysystem.h
retval = 00000000

③引数を入力せずにmysystemを実行
% ./mysysmain 
使い方 : ./mysysmain コマンド文字列
*/
