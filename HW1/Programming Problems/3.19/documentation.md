# 3.19 Programming Problem

## 事前準備

1. 解壓縮下載的解壓檔
2. 打開終端並導航到項目目錄

## 編譯

請確保您的系統已安裝以下軟體：

- GCC 編譯器 (至少需要支援 C99 standard 的版本)
- Make 工具

若你使用的是 Ubuntu 系統，可以通過以下指令安裝所需的軟體：

```bash
apt update
apt install build-essential
```

這將安裝 GCC 編譯器和 Make 工具。

## 執行

在終端中執行以下指令來編譯程式：

```bash
make v1 # 編譯 Version 1
make v2 # 編譯 Version 2
```

編譯完成後，運行以下指令來執行程式：

```bash

./time <command> [<args>]
```

請將 `<command>` 替換為要計時的指令，將 `<args>` 替換為傳入的參數，此處可以為空值。

## 開源庫和API

此項目使用 [POSIX Library](https://pubs.opengroup.org/onlinepubs/9799919799/) 與 [C Standard Library](https://en.cppreference.com/w/c) 來進行操作
