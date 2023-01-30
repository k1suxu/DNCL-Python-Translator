# DNCL-Python-Translator
This translates code written in DNCL(2011) into Python.

## 使用方法
このプログラムはDNCL(2011)をPythonに翻訳します。mainファイルmain関数内"input_filename"に入力データファイル(DNCL(2011)で書かれたコード)へのパスを、"output_filename"に出力データを入力するためのファイルへのパスを記入したのち、お好きなエディタで実行することができます。
### 文字列型と数値型の加算
文字列型と数値型の加算は未定義であるため、適宜翻訳後のファイルに変更を加える必要があります。<br>
numberが数値型、textが文字列型の変数であるとき、"number+text"のような演算を使用するコードを使用したい場合、翻訳後の"number+text"を「str(number)+text」のようにする必要があります。
### 表示関数
表示関数の挙動は標準状態(特に指示がない限り)において、<br>
　・引数間の空白などはなし<br>
　・引数出力後の改行アリ<br>
のように動作します。引数間の文字については、翻訳後のPythonファイル内print関数の引数のうち「sep=''」の部分を変更することにより 変えることができます。また、改行の有無はprint関数の引数のうち「end='\n'」の部分をへんこうすることにより、変えることができます。

## サンプルコードについて
Separated_Input_Files, Separated_Output_FilesにはDNCL(2011)のサンプルコード及び、その翻訳結果(Python)が存在します。なお、DNCL(2011)のサンプルコードは[どんくり](https://dolittle.eplang.jp/dncl)
のサンプルをDNCL(2011)年仕様に少し改変したものになります。

## サンプルコードにおける実行結果
Output_Datasにはサンプルコードの実行結果が載っています。Mine.txtが翻訳後Pythonコードの実行結果、どんくり.txtが翻訳前DNCL(2011)コードの実行結果です。なお、Mine.txtについては、使用方法の欄の通り適宜翻訳後のプログラムに変更を加えたものを実行しています。具体的には以下の通りです。<br>

|該当箇所|変更前|変更後|
|:---:|:---:|:---:|
|2008_3_2 48行目|Tokuten[i-1]|str(Touten[i-1])|
|2008_3_3 52行目|Tokuten[i-1]|str(Touten[i-1])|
|2011_3_2 60行目|Tenjun[num-1]|str(Tenjun[num-1])|
|2011_3_2 60行目|Tenban[num-1]|str(Tenban[num-1])|
|2018_3_2 54,56,59行目|end='\n'|end=''|
|2018_3_3 55,57,60行目|end='\n'|end=''|

<br>
*注意* 2014_3_2,2014_3_3,2015_3_3は想定していない挙動を含むコードのため実行結果が異なります。前者2つは配列に対するサイズ定義、3つ目は配列外参照が原因です。
=======
# DNCL-Python-Translator
DNCL(2011年度版)をPythonに翻訳するプログラム及び正当性確保のためのテストデータと実行結果一覧です。<br>
<br>
DNCL仕様書(2011年度版): https://web.archive.org/web/20220707074107/https://www.dnc.ac.jp/albums/abm00004841.pdf<br>
(元URLが使えなくなっているためアーカイブサイトのURLを載せてあります。)
