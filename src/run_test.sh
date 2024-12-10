#!/bin/bash
g++ main.cpp -o a.out

# 入力ファイルのリストを取得
input_files=$(ls test-data/inputs)
echo "==================================================="
for input_file in $input_files
do
    echo "[Start]: Test $input_file"
    dos2unix test-data/inputs/$input_file # 改行コードを変換
    ./a.out test-data/inputs/$input_file test-data/outputs/$input_file >& test-data/log/$input_file
    echo "[Finish]: Successfully Translated"
    echo "==================================================="
done
