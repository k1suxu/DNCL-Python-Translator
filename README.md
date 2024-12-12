# DNCL-Python-Translator
This translates code written in DNCL(2011) into Python<br>
DNCL(2011)で書かれたコードをPythonコードに翻訳します。<br>


## DNCL(2011)
DNCL仕様書(2011年度版): https://web.archive.org/web/20220707074107/https://www.dnc.ac.jp/albums/abm00004841.pdf<br>
(元のURLが使えなくなっているためアーカイブサイトのURLを載せてあります。)

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
`src/`ディレクトリ直下にて`make test`コマンドを実行することでDockerコンテナが立ち上がり、`src/test-data/inputs/*`の各ファイルに対して翻訳が実行され、以下のファイルが出力されます。
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
|2018_3_2 54,56,59行目|end='\n'|end=''|
|2018_3_3 55,57,60行目|end='\n'|end=''|

<br>
*注意* 2014_3_2,2014_3_3,2015_3_3は想定していない挙動を含むコードのため実行結果が異なります。<br>
前者2つは配列に対するサイズ定義、3つ目は配列外参照による挙動差が原因です。<br>
=======
