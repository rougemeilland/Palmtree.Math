Palmtree 数値計算ライブラリ
==========================
.NET Framework で数値計算を行うためのライブラリです。
長精度の整数や有理数の演算に特化していますので、機能的にはあまり多くありません。  
なお、SFMTによる乱数生成もサポートしています。
 
動作環境
-------
.NET Frameworkが動作する x86/x64 CPUのコンピュータが必要です。

必要ディスク容量
---------------
インストールのために約6Mバイトのディスクが必要です。

データ型/クラスについて
---------------------
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
* 絶対値/符号の反転

### Rational型(有理数) ###
論理的には、分子と分母がそれぞれ最大で2の32乗-1ビットの長さまでの有理数を扱うことができます。
有理数の演算なので、Doubleなどの浮動小数点型に比べて可能な演算は限られますが、計算誤差が発生しないことが特長です。
以下の演算が可能です。
* 加算/減算/乗算/除算
* 累乗
* 逆数
* 絶対値/符号反転
* 指定桁での丸め(Floor/Ceiling/切り捨て/切り上げ/四捨五入/五捨五超入/偶数への丸め)
* 等値/大小比較
* ToString/Parse/TryParse
* 他のデータ型との相互型変換
  * Int32/UInt32/Int64/UInt64
  * Double/Decimal

### Randomクラス(乱数生成) ###
SFMTを使用して乱数を生成することができるクラスです。
以下のデータ型の乱数を生成することができます。
* UInt32型(0以上、2の32乗-1以下)
* UInt64型(0以上、2の64乗-1以下)
* Double型(0以上1未満)
* UBigInt型(0以上、2のn乗-1以下、nは指定可能)
* BigInt型(0以上、2のn乗-1以下、nは指定可能)
* Rational型(0以上、1未満)
 
著作権
------
&copy; 2018-2019 Palmtree Software

##### SFMT.c, SFMT-*.h: #####
Copyright (C) 2006, 2007 Mutsuo Saito, Makoto Matsumoto and Hiroshima  University.  
Copyright (c) 2012 Mutsuo Saito, Makoto Matsumoto, Hiroshima University  and The University of Tokyo.  
All rights reserved.

ライセンス
----------
Licensed under the [MIT License][mit].
 
[MIT]: http://www.opensource.org/licenses/mit-license.php
