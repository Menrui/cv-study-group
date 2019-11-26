# 課題１「Affine変換」

## 課題内容
* Affine変換、補完の関数を作成して以下の操作を行う
* Lenna画像を拡大(2倍以上)しnearestとbilinearで補完
* アフィン変換を行う(3つ以上、一回の計算で)
* Mark downを書いてgit上に提出


## ファイル構成
- Header
  - **affine.h**
        - enum ComplementMode
  - **bilinier.h**
  - **main.h**
  - **nearest.h**
- Source
  - **affine.cpp**
        - Mat imageAddine(Matx33d A, Mat image, ComplementMode mode)
        - tuple<double, double> pixelAffine(Mat A, int x, int y)
        - tuple<double, double> pixelAffine2(Mat A, int x, int y)
  - **bilinier.cpp**
        - Vec3b bilinier(Mat image, double x, double y)
  - **main.cpp**
        - int main()
  - **nearest.cpp**
        - Vec3b nearest(Mat image, double x, double y)


## 関数の説明
**Vec3b bilinier(Mat image, double x, double y)**  
バイリニア補完を掛ける際の、座標ごとの補完値を計算する。  
入力 ： 補完対象画像, x座標, y座標  
出力 ： 与えられた座標のバイリニア補完値  
  
**Vec3b nearest(Mat image, double x, double y)**
ニアレスト補完を掛ける際の、座標ごとの補完値を計算する。入力、出力ともにbilinierと同じ。

**pixelAffine(affine.cpp)**
アフィン変換を行う際の、座標ごとの変換値を計算する。アフィン変換後の座標からアフィン変換前の座標を計算する。
入力 ： 変換行列 A,  x座標,  y座標
出力 ： アフィン変換前の座標(x, y)を要素とするタプル

**pixelAffine2(affine.cpp)**
アフィン変換前の座標からアフィン変換後の座標を計算する。  
入出力はpixelAffineと同様。

**Mat imageAddine(Matx33d A, Mat image, ComplementMode mode)**  
与えられた画像に対してアフィン変換を行う。  
入力 ： 変換行列A, 変換対象画像, 補完モード  
出力 ： 変換後画像

**int main()**
各関数を用いて課題内容を実行する。

