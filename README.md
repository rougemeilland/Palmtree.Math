Palmtree 数値計算ライブラリ v1.4.0
=================================
.NET Framework で数値計算を行うためのライブラリです。
長精度の整数や有理数の演算に特化していますので、機能的にはあまり多くありません。  
なお、SFMTによる乱数生成もサポートしています。
 
動作環境
--------
.NET Framework 4.5以降が動作する x86/x64 CPUのコンピュータが必要です。

必要ディスク容量
----------------
インストールのために約6Mバイトのディスク空き容量が必要です。

主なデータ型/クラスについて
-------------------------
### `Palmtree.Math.UBigInt`型(符号なし長精度整数) ###
論理的には2の32乗-1ビットの長さまでの整数を扱うことができます(実際には扱える整数の長さはオペレーティングシステムその他の制限を受けます)。以下の演算が可能です。
* 加算/減算/乗算/除算/剰余/完全除算
* 累乗/累乗の剰余
* 等値/大小比較
* ビット単位の論理積/論理和/排他的論理和
* ビットシフト(右/左)
* `ToString`(対応書式: C, D, E, F, G, N, P, X, カスタム)
* `Parse`/`TryParse`
* 他のデータ型との相互型変換
  * `Int32`/`UInt32`/`Int64`/`UInt64`
  * `Double`/`Decimal`
  * `BigInt`/`Rational`
* 最大公約数の計算
* 拡張ユークリッド互除法

### `Palmtree.Math.BigInt`型(符号つき長精度整数) ###
負の数も扱えること以外は`UBigInt`型とほぼ同等です。
`UBigInt`型でできる演算に加えて、`BigInt`型では以下の演算が可能です。
* 絶対値/符号の反転
* 正剰余の計算
* 他のデータ型との相互型変換
  * `Int32`/`UInt32`/`Int64`/`UInt64`
  * `Double`/`Decimal`
  * `UBigInt`/`Rational`

### `Palmtree.Math.Rational`型(有理数) ###
論理的には、分子と分母がそれぞれ最大で2の32乗-1ビットの長さまでの有理数を扱うことができます(実際には扱える分子および分母の長さはオペレーティングシステムその他の制限を受けます)。
有理数の演算なので、`Double`などの浮動小数点型に比べて可能な演算は限られますが、計算誤差が発生しないことが特長です。
以下の演算が可能です。
* 加算/減算/乗算/除算
* 累乗
* 逆数
* 絶対値/符号反転
* 指定桁での丸め(`Floor`/`Ceiling`/切り捨て/切り上げ/四捨五入/五捨五超入/偶数への丸め)
* 等値/大小比較
* `ToString`(対応書式: C, E, F, G, N, P, カスタム)
* `Parse`/`TryParse`
* 他のデータ型との相互型変換
  * `Int32`/`UInt32`/`Int64`/`UInt64`
  * `Double`/`Decimal`
  * `UBigInt`/`BigInt`

### `Palmtree.Math.Random`クラス(乱数生成) ###
SFMTを使用して乱数を生成することができるクラスです。
以下のデータ型の乱数を生成することができます。
* `UInt32`型(0以上、2の32乗-1以下)
* `UInt64`型(0以上、2の64乗-1以下)
* `Double`型(0以上1未満)
* `UBigInt`型(0以上、2のn乗-1以下、nは指定可能)
* `Rational`型(0以上、1未満)
 
### `Palmtree.Security.Cryptography.CryptoRandom`クラス(暗号乱数生成) ###
`System.Security.Cryptography.RNGCryptoServiceProvider`のラッパークラスです。
以下のデータ型の乱数を生成することができます。
* `UInt32`型(0以上、2の32乗-1以下)
* `UInt64`型(0以上、2の64乗-1以下)
* `Double`型(0以上1未満)
* `UBigInt`型(0以上、2のn乗-1以下、nは指定可能)
* `Rational`型(0以上、1未満)
 
更新履歴
--------
### v1.4.0 ###
* 以下の機能の追加
  * 拡張ユークリッド互除法
  * 正剰余の計算機能
  * 完全除算機能
  * `Palmtree.Math.Random`クラスにデフォルトコンストラクタの追加 (この場合`seed`には現在時刻に基づく数値が採用されます)
  * Toom-Cook 法による乗算の実装。32bitアプリケーションの場合は約8万桁、64bitアプリケーションの場合は約32万桁以上の乗算を行う際に自動的にToom-Cook法が使用されます。
* 性能改善のための以下の変更
  * 基本演算ルーチンの整理
  * メモリの無駄なゼロクリアの削減
  * Karatsuba 法乗算ルーチンの見直し
### v1.3.4 ###
* パッケージミスの修正
### v1.3.3 ###
* `Palmtree.Math.Random`クラスで`Double`型の乱数を生成する際に、生成された数値が小さいと53bitの有効桁が確保できていない問題の改善
* 64bit版の`Palmtree.Math.Random`クラスで`UInt32`型の乱数と`UInt64`型の乱数を混在させて生成すると例外が発生する障害の修正
### v1.3.2 ###
* .NET framework 4.5～4.72に対応するようパッケージ方法を変更
### v1.3.1 ###
* 一時作業域の管理方法の変更によるKaratsuba法の実装の高速化。ある閾値の桁数の整数の乗算でKaratsuba法、それより小さい整数の乗算では従来の古典的算法が自動的に使用されます。
    * この閾値は32bitアプリケーションの場合10進数で約630,000桁、64bitアプリケーションの場合約1,260,000桁に設定されています。
    * この閾値は実機での性能検証によりチューニングされており将来予告なしに変更の可能性があります。
    * この閾値はハードコーディングされているため利用者が変更することはできません。
### v1.3.0 ###
* Karatsuba法によるUBigIntおよびBigInt型の乗算の高速化。この乗算の高速化はRational型の乗算および除算の性能にも反映されます。
* 性能改善のため、ヒープメモリの管理方法を変更
### v1.2.0 ###
* `Palmtree.Math.UBigIntComparer`クラス(`IEqualityComparer<UBigInt>`および`IComparer<UBigInt>`の実装)の追加
* `Palmtree.Math.BigIntComparer`クラス(`IEqualityComparer<BigInt>`および`IComparer<BigInt>`の実装)の追加
* `Palmtree.Math.RationalComparer`クラス(`IEqualityComparer<Rational>`および`IComparer<Rational>`の実装)の追加
### v1.1.0 ###
* `Palmtree.Security.Cryptography.CryptoRandom`クラスの追加
* `Palmtree.Math.Random`クラスにおいて、BigInt型の乱数を生成する機能を削除
### v1.0.1 ###
* nuget パッケージ中のライセンス表記の誤りの修正
### v1.0.0 ###
* 正式公開

プロジェクトURL
--------------
https://github.com/rougemeilland/Palmtree.Math

著作権
------
&copy; 2018-2019 Palmtree Software

##### SFMTのソースファイル(SFMT.c, SFMT-*.h): #####
Copyright (C) 2006, 2007 Mutsuo Saito, Makoto Matsumoto and Hiroshima  University.  
Copyright (c) 2012 Mutsuo Saito, Makoto Matsumoto, Hiroshima University  and The University of Tokyo.  
All rights reserved.

ライセンス
----------
Licensed under the [MIT License][mit].
 
[MIT]: http://www.opensource.org/licenses/mit-license.php
