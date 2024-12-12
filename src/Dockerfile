# ベースイメージ
FROM ubuntu:22.04

# 必要なパッケージをインストール
RUN apt-get update && apt-get install -y \
    g++ \
    locales \
    dos2unix \
    python3 \
    python3-pip \
    python-is-python3 \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# ロケールを生成
RUN locale-gen ja_JP.UTF-8 \
    && update-locale LANG=ja_JP.UTF-8

# 作業ディレクトリ
WORKDIR /app

# 必要なファイルをコンテナにコピー
COPY . /app

# 実行可能権限を付与
RUN chmod +x run_translate.sh \
    && chmod +x run_py.sh
