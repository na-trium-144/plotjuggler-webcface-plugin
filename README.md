# plotjuggler-webcface-plugin

[PlotJuggler](https://github.com/facontidavide/PlotJuggler) plugin for [WebCFace](https://github.com/na-trium-144/webcface).

[plotjuggler-sample-plugins](https://github.com/PlotJuggler/plotjuggler-sample-plugins) をもとに作っています

## WebCFaceのインストール

WebCFaceのREADMEにしたがってインストールしてください

## PlotJugglerのインストール

PlotJugglerのREADMEにしたがってaptで入れるか、以下のようにソースからビルドしてください
```sh
sudo apt install qtbase5-dev libqt5svg5-dev libqt5websockets5-dev libqt5x11extras5-dev
git clone --recurse-submodules https://github.com/facontidavide/PlotJuggler.git
cd PlotJuggler
mkdir build; cd build
cmake ..
make -j
sudo make install
```

## プラグインのインストール

```sh
git clone https://github.com/na-trium-144/plotjuggler-webcface-plugin
cd plotjuggler-webcface-plugin
cmake -Bbuild
make -Cbuild
sudo make -Cbuild install
```

PlotJugglerがプラグインを読み込まない場合は、
ビルドしたプラグインを `plotjuggler` 実行ファイルと同じディレクトリに置くか、
App -> Preferences... からプラグインのディレクトリを指定してください。
