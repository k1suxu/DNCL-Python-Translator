
# DNCL-Python-Translator
This tool translates code written in DNCL (2011) into Python.<br>

## About DNCL
DNCL Specification (2011 Edition): https://web.archive.org/web/20220707074107/https://www.dnc.ac.jp/albums/abm00004841.pdf<br>
(The original URL is no longer available, so an archived URL is provided.)

## How to run test
1. Clone this repository to your local environment.
2. Navigate to the `src` directory.
3. Run the `make` or `make test` command in the terminal.
4. The results (including output files and error logs) will be generated in the `src/test-data` directory. (See the `Explanation` section below for more details.)

# Explanation (説明)

<details><summary>For English Readers </summary>

## Notes

### Addition of String and Numeric Types
In DNCL 2011, the addition of string and numeric types is undefined. Therefore, you need to adjust the translated file as necessary.<br>
For example, if `number` is a numeric type and `text` is a string type, and the operation `number+text` is intended as string concatenation, you must modify the translated code from `number+text` to `str(number)+text`.

### Display Function
By default, the behavior of the display function in DNCL is as follows (unless otherwise specified):<br>
- No spaces between arguments.<br>
- A newline is added after output.<br>

In the translated Python code, you can modify the output formatting by adjusting the `print` function arguments:
- Use the `sep=''` parameter to change the separator between arguments.
- Use the `end='\n'` parameter to modify whether or not a newline is added after the output.

# Running Tests
By executing the `make` or `make test` command in the `src/` directory, a Docker container will launch, and the translation process will be applied to each file in `src/test-data/inputs/*`. The following output files will be generated:
- `src/test-data/outputs/*` (translation results)
- `src/test-data/translate-logs/*` (translation logs)
- `src/test-data/translate-error-logs/*` (error logs from translation)
- `src/test-data/run-outputs/*` (execution results of the generated Python files)
- `src/test-data/run-error-logs/*` (execution errors from the generated Python files)
- `src/test-data/combined-run-output.txt` (consolidated execution results of the Python files)
- `src/test-data/combined-run-error-log.txt` (consolidated execution errors of the Python files)

## Sample Code
The `src/test-data` directory contains sample DNCL (2011) code (`inputs/*.txt`) and their Python translation results (`outputs/*.py`). These DNCL (2011) samples are adapted versions of [Donkuri](https://dolittle.eplang.jp/dncl)'s sample programs modified to conform to the DNCL (2011) specification.

## Execution Results of Sample Code
The `src/test-data/run-outputs` directory contains execution results of the sample code. The file `src/test-data/combined-run-output.txt` contains the results of the translated Python code, while `src/test-data/expected-run-output.txt` contains the results of the original DNCL (2011) code.<br>
To achieve equivalent output to `expected-run-output.txt`, you must make adjustments to the translated program as described in the "Notes" section. Specifically, the following modifications are required:<br>

| Location       | Before Change       | After Change         |
|:--------------:|:-------------------:|:--------------------:|
| 2008_3_2 line 48 | Tokuten[i-1]        | str(Tokuten[i-1])    |
| 2008_3_3 line 52 | Tokuten[i-1]        | str(Tokuten[i-1])    |
| 2011_3_2 line 60 | Tenjun[num-1]       | str(Tenjun[num-1])   |
| 2011_3_2 line 60 | Tenban[num-1]       | str(Tenban[num-1])   |

<br>
*Note*: The programs `2014_3_2`, `2014_3_3`, and `2015_3_3` exhibit unexpected behavior and produce different execution results.<br>
- For the first two, this is due to the deference of the way to print an array.
- For the third, differences arise from out-of-bound array references.
</details>

<details><summary>日本人の方へ</summary>

## 注意点

### 文字列型と数値型の加算
DNCL2011において、文字列型と数値型の加算は未定義であるため、適宜翻訳後のファイルに変更を加える必要があります。<br>
numberが数値型、textが文字列型の変数であるとき、"number+text"のような演算を文字列可算として使用するコードを書きたい場合、翻訳後の"number+text"を「str(number)+text」のようにする必要があります。
### 表示関数
表示関数の挙動は標準状態(特に指示がない限り)において、<br>
　・引数間の空白などはなし<br>
　・引数出力後の改行アリ<br>
のように動作します。引数間の文字については、翻訳後のPythonファイル内print関数の引数のうち「sep=''」の部分を変更することにより 変えることができます。また、改行の有無はprint関数の引数のうち「end='\n'」の部分をへんこうすることにより、変えることができます。

# テストの実行について
`src/`ディレクトリ直下にて`make`または`make test`コマンドを実行することでDockerコンテナが立ち上がり、`src/test-data/inputs/*`の各ファイルに対して翻訳が実行され、以下のファイルが出力されます。
- `src/test-data/outputs/*` (翻訳結果)
- `src/test-data/translate-logs/*` (翻訳時の正常ログ)
- `src/test-data/translate-error-logs/*` (翻訳時の異常ログ)
- `src/test-data/run-outputs/*` (生成された各Pythonファイルの実行結果)
- `src/test-data/run-error-logs/*` (生成された各Pythonファイルの実行時エラー)
- `src/test-data/combined-run-output.txt` (生成された各Pythonファイルの実行結果を一つのテキストファイルにまとめたもの)
- `src/test-data/combined-run-error-log.txt` (生成された各Pythonファイルの実行時エラーを一つのテキストファイルにまとめたもの)

## サンプルコードについて
`src/test-data`内にはDNCL(2011)のサンプルコード(`inputs/*.txt`及び、その翻訳結果(Python)(`outputs/*.py`)が存在します。なお、DNCL(2011)のサンプルコードは[どんくり](https://dolittle.eplang.jp/dncl)
のサンプルプログラムをDNCL(2011)仕様に少し改変したものになります。

## サンプルコードにおける実行結果
`src/test-data/run-outputs`にはサンプルコードの実行結果が載っています。`src/test-data/combined-run-output.txt`が翻訳後Pythonコードの実行結果、`src/test-data/expected-run-output.txt`が翻訳前DNCL(2011)コードの実行結果です。<br>
なお、`expected-run-output.txt`と対応のとれた出力を得るためには、「注意点」の欄の通り適宜翻訳後のプログラムに変更を加える必要があります。具体的には以下の通りです。<br>

|該当箇所|変更前|変更後|
|:---:|:---:|:---:|
|2008_3_2 48行目|Tokuten[i-1]|str(Touten[i-1])|
|2008_3_3 52行目|Tokuten[i-1]|str(Touten[i-1])|
|2011_3_2 60行目|Tenjun[num-1]|str(Tenjun[num-1])|
|2011_3_2 60行目|Tenban[num-1]|str(Tenban[num-1])|

<br>
*注意* 2014_3_2,2014_3_3,2015_3_3は想定していない挙動を含むコードのため実行結果が異なります。<br>
前者2つは配列の出力方法の定義、3つ目は配列外参照による挙動差が原因です。<br>
=======
</details>
