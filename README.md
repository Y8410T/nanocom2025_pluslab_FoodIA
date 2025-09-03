# nanocom2025_pluslab_FoodIA
## 概要

冷蔵庫を開いた時に冷蔵庫内を撮影し，レシピ提案と足りない食材をリストアップするシステムである．

類似の製品として関西電力から発売された[冷蔵庫カメラアプリ](https://media.kepco.co.jp/project/17659806)が存在する．

## 使用リーフ

### カメラ撮影関係

Type|Name
-|-
AZ02 | RTC&microSD
AX04 | Spacer
AX06 | Grove&5V
AP01 | AVR MCU
AZ01 | USB
AV01 | CR2032

### BLE関係
Type|Name
-|-
AC02 | BLE Sugar

## AVR MCU 開発環境構築

### 1.Arduino IDEのインストール 

Arduino IDEのインストールは[こちら](https://www.arduino.cc/en/software/#ide)

### 2.マイコンボードの設定を行う

1. ツール → ボードから，Arduino Pro or Pro Miniを選択，プロセッサでATmega328P (3.3V,8MHz)を選択する．

2. ツール → シリアルポートから，Leafonyが接続されているシリアルポートを選択する．

### 参考サイト

- https://docs.leafony.com/docs/environment/avr/arduino/
