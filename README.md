# WSrch 

CWSEngine (Windows Search C++ Wrapper)

Visual C++ 6.0 (VC6 / C++98) などのレガシー環境から最新環境まで幅広く対応する、.NET 非依存の Windows Search API 汎用検索エンジン (`CWSEngine`) およびサンプルプロジェクト一式です。

.NET Framework や C++/CLI を一切使用せず、純粋な Win32 API および COM (ADO / `msado15.dll`) 経由で OLE DB プロバイダ `Search.CollatorDSO` へ SQL クエリを発行します。

---

## 特徴

- **.NET 非依存**: 完全な Win32 ネイティブ C++ 実装。外部ランタイム（.NET 等）に依存しません。
- **レガシー開発環境対応**: C++98 規格に準拠し、Visual C++ 6.0 でそのままビルド可能。
- **最新 OS 対応**: Windows 11 の Windows Search 仕様（`Search.CollatorDSO` 接続）に完全対応。
- **柔軟な SQL 検索機能**:
  - セミコロン区切りによる複数拡張子の同時指定 (`*.txt;*.doc` など)
  - ワイルドカード (`*`) および `CONTAINS` 句による高速なインデックスキーワード検索
  - 各種プロパティ（更新日時、ファイル名、フルパスなど）による昇順・降順ソート
- **即座にビルド可能な構成**: VC6 用のワークスペースファイル (`.dsw`) やプロジェクトファイル (`.dsp`) を同梱。

---


## 動作環境・必要要件

- **開発環境**:
  - Microsoft Visual C++ 6.0 (VC6)
  - ※ Visual Studio 2005 以降のモダンな Visual Studio でのプロジェクト移行・ビルドにも対応
- **対応 OS**:
  - Windows XP / Vista / 7 / 8 / 10 / 11 (Windows Search サービスが有効であること)
- **依存コンポーネント**:
  - ADO (`msado15.dll`) ※ Windows 標準搭載

---

## ビルド手順 (VC6 の場合)

1. リポジトリをクローンします。
2. `WSrch.dsw` をダブルクリックして Visual C++ 6.0 で開きます。
3. メニューの **[Build]** -> **[Set Active Configuration]** で `WSrch - Win32 Release` または `Win32 Debug` を選択します。
4. **[Build]** (F7) を実行すると、ビルドが完了し実行可能ファイルが生成されます。

---

## 使い方・コード例

### 1. ヘッダのインクルード

```cpp
#include "v_tstrng.hxx"
#include "Path_Fnc.hxx"
#include "tstring.hxx"
#include "iVariant.hxx"
#include "WSEngine.inc"
```

### 2. 検索の実行

`CWSEngine` クラスインスタンスを生成し、拡張子・キーワード・ソート条件を指定して検索します。

```cpp
CWSEngine engine;

// 1. 検索拡張子 (マルチ指定可能)
tstring tsExt = _T("txt;doc");

// 2. 検索キーワード配列
v_tstring vKeys;
vKeys.push_back(_T("2026")); // キーワード

// 3. 検索実行 (更新日時の新しい順)
vv_tstring vvResults = engine.Search(tsExt, vKeys, CWSEngine::SORT_DATE_DESC);

// 4. 結果の取得
for (size_t i = 0; i < vvResults.size(); ++i) {
    tstring tsPath = vvResults[i][0]; // ファイルのフルパス
    tstring tsDate = vvResults[i][1]; // 更新日時
    
    // 取得したパスや日時への処理
}
```

### 3. ソートオプション (`SORT_TYPE`)

| 定数 | 内容 |
| :--- | :--- |
| `SORT_NONE` | ソートなし |
| `SORT_DATE_DESC` / `SORT_DATE_ASC` | 更新日時 (新しい順 / 古い順) |
| `SORT_NAME_DESC` / `SORT_NAME_ASC` | ファイル名 (Z-A / A-Z) |
| `SORT_PATH_DESC` / `SORT_PATH_ASC` | フルパス名 (Z-A / A-Z) |




---

## 免責事項

本ツールおよび公開しているソースコードの使用により生じたいかなる損害についても、著作者は一切の責任を負いません。ご自身の責任において利用してください。
引用・改変時は上記 URL ( https://mish.work/ ) を明記してください。


---

* **作者:** Iwao ( https://mish.work/ )
* **Copyright:** (C) 2026 Iwao. All Rights Reserved.

