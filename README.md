# HT-Keys Public Repository

本リポジトリでは、_HT-Keys_ のファームウェアと開発者向け情報を公開しています

# HT-Keys とは

私 [Harusame](https://twitter.com/HarusameTech) が設計・制作している自作キーボードシリーズです

site：<https://www.harusame.tech/product/keyboard/HT-Keys/>

# 製品シリーズ

## TKL

概要

- US 配列
- テンキーレス
- 87 キー
- USB Type-C インターフェース採用
- CherryMX プロファイル
- RP2040 搭載
- Raspberry Pi Pico 互換仕様
- ファームウェアレベルでカスタマイズ可能

## Releases について

本リポジトリでは、以下のような命名規則を使用しています

| Releases の名前 | 意味 |
| `Developer Release` | HT-Keys のデバッグや開発用。主に開発者向け |
| `User Release - beta` | HT-Keys の開発段階のファームウェア。主に開発者向け |
| `User Release - Stable` | HT-Keys のファームウェア。使用者向け |

※ファームウェア開発を行うにあたり、何かしらのバグの解消ができたものを `beta` とし、開発時点で見つかっているバグをおおよそ、あるいは全て解消できたものを `Stable` としています

## ご使用の際の注意事項

本キーボードは US 配列です。そのため、Windows のキーボード設定を以下のように変更する必要があります

[設定] -> [言語と時刻] -> [言語] -> [優先する言語] の「オプション」から、ハードウェアキーボードレイアウトを変更してください

<div align="center"><img src="https://user-images.githubusercontent.com/95992721/223290590-b2c7e64a-7791-4b0e-9e55-03f8c428e896.png"></div>
<div align="center">↓</div>
<div align="center"><img src="https://user-images.githubusercontent.com/95992721/223290757-b25cfca1-7e08-4824-9c6c-0a4f3b5d9bf7.png"></div>
<div align="center">↓</div>
<div align="center"><img src="https://user-images.githubusercontent.com/95992721/223290737-ae6536b0-0dc5-4523-9bb1-e338c6b78499.png"></div>
