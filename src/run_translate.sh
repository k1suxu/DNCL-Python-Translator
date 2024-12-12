#!/bin/bash
g++ main.cpp -o a.out

# 入力ファイルのリストを取得
input_files=$(ls test-data/inputs)
echo ""
echo "+----------------------------------+"
echo "| Start: Translate All Input Files |"
echo "+----------------------------------+"
echo ""
echo "==================================================="

for input_file in $input_files
do
    echo "[Start]: Translate $input_file"
    dos2unix test-data/inputs/$input_file # 改行コードを変換
    ./a.out test-data/inputs/$input_file test-data/outputs/${input_file%.txt}.py > test-data/translate-logs/$input_file 2> test-data/translate-error-logs/$input_file
    echo "[Finish]: Successfully Translated"
    echo "==================================================="
done

echo ""
echo "+-----------------------------------+"
echo "| Finish: Translate All Input Files |"
echo "+-----------------------------------+"
echo ""
