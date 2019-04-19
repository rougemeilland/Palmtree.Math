Palmtree 数値計算ライブラリ
======================
.NET Framework で数値計算を行うためのライブラリです。
長精度の整数や有理数の演算に特化していますので、機能的にはあまり多くありません。  
なお、SFMTによる乱数生成もサポートしています。
 
データ型/クラスについて
------
### UBigInt型(符号なし長精度整数) ###
論理的には2の32乗-1ビットの長さまでの整数を扱うことができます。以下の演算が可能です。
* 加算/減算/乗算/除算/剰余
* 累乗/累乗の剰余
* 等値/大小比較
* ビット単位の論理積/論理和/排他的論理和
* 論理シフト(右/左)
* ToString/Parse/TryParse
* 他のデータ型との相互型変換
  * Int32/UInt32/Int64/UInt64
  * Double/Decimal
* 最大公約数の計算

### BigInt型(符号つき長精度整数) ###
負の数も扱えること以外はUBigInt型とほぼ同等です。
UBigInt型でできる演算に加えて、BigInt型では以下の演算が可能です。
* 絶対値の取得/符号の反転

### Rational型(有理数) ###
論理的には、分子と分母がそれぞれ最大で2の32乗-1ビットの長さまでの有理数を扱うことができます。
以下の演算が可能です。
* 

負の数も扱えること以外はUBigInt型とほぼ同等です。
UBigInt型でできる演算に加えて、BigInt型では以下の演算が可能です。
* 絶対値の取得/符号の反転

### ブロックレベル ###
    function f () {
        alert(0);  /* 先頭に4文字のスペース、
                      もしくはタブを挿入します */
    }
 
パラメータの解説
----------------
リストの間に空行を挟むと、それぞれのリストに `<p>` タグが挿入され、行間が
広くなります。
 
    def MyFunction(param1, param2, ...)
 
+   `param1` :
    _パラメータ1_ の説明
 
+   `param2` :
    _パラメータ2_ の説明
 
関連情報
--------
### リンク、ネストしたリスト
1. [リンク1](http://example.com/ "リンクのタイトル")
    * ![画像1](http://github.com/unicorn.png "画像のタイトル")
2. [リンク2][link]
    - [![画像2][image]](https://github.com/)
 
  [link]: http://example.com/ "インデックス型のリンク"
  [image]: http://github.com/github.png "インデックス型の画像"
 
### 引用、ネストした引用
> これは引用です。
>
> > スペースを挟んで `>` を重ねると、引用の中で引用ができますが、
> > GitHubの場合、1行前に空の引用が無いと、正しくマークアップされません。
 
ライセンス
----------
Copyright &copy; 2011 xxxxxx
Licensed under the [Apache License, Version 2.0][Apache]
Distributed under the [MIT License][mit].
Dual licensed under the [MIT license][MIT] and [GPL license][GPL].
 
[Apache]: http://www.apache.org/licenses/LICENSE-2.0
[MIT]: http://www.opensource.org/licenses/mit-license.php
[GPL]: http://www.gnu.org/licenses/gpl.html
