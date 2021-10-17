import argparse


def main():
    parser = argparse.ArgumentParser(
        description='このプログラムの説明（なくてもよい）')    # 2. パーサを作る
    parser.add_argument("--arg", type=str, default="", help="")
    pass


if __name__ == 'main':
    main()
