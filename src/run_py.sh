#!/bin/bash

# 入力ファイルのリストを取得
output_files=$(ls test-data/outputs)
echo ""
echo "+-----------------------------+"
echo "| Start: Run All Output Files |"
echo "+-----------------------------+"
echo ""
echo "==================================================="

for output_file in $output_files
do
    echo "[Start]: Run $output_file"
    python3 test-data/outputs/$output_file > test-data/run-logs/${output_file%.py}.txt 2> test-data/run-error-logs/${output_file%.py}.txt
    echo "[Finish]: Successfully Run"
    echo "==================================================="
done

# combined-run-log.txt が存在する場合は削除
if [ -e test-data/combined-run-log.txt ]; then
    rm test-data/combined-run-log.txt
fi
# cobined-run-error-log.txt が存在する場合は削除
if [ -e test-data/combined-run-error-log.txt ]; then
    rm test-data/combined-run-error-log.txt
fi

# combined-run-log.txt に全ての実行ログを書き込む
for output_file in $output_files
do
    # 空だったらスキップ
    if [ ! -s test-data/run-logs/${output_file%.py}.txt ]; then
        continue
    fi
    echo "==================== $output_file ====================" >> test-data/combined-run-log.txt
    cat test-data/run-logs/${output_file%.py}.txt >> test-data/combined-run-log.txt
    echo "" >> test-data/combined-run-log.txt
done

# combined-run-error-log.txt に全てのエラーログを書き込む
for output_file in $output_files
do
    # 空だったらスキップ
    if [ ! -s test-data/run-error-logs/${output_file%.py}.txt ]; then
        continue
    fi
    echo "==================== $output_file ====================" >> test-data/combined-run-error-log.txt
    cat test-data/run-error-logs/${output_file%.py}.txt >> test-data/combined-run-error-log.txt
    echo "" >> test-data/combined-run-error-log.txt
done

echo ""
echo "+------------------------------+"
echo "| Finish: Run All Output Files |"
echo "+------------------------------+"
echo ""
