#!/bin/python3
import json
import os
import re
import sys
import typing
import argparse
from bs4 import BeautifulSoup
import requests
# import requests_cache
import urllib.parse as urlparse
import sys
import os
import re
from cachecontrol import CacheControl


def get_user_password(cred_path) -> typing.Dict[str, str]:
    with open(cred_path, "r") as f:
        v = json.load(f)
        return {"username": v["username"], "password": v["password"]}


def get_cookie_text(cred_path) -> str:
    with open(cred_path, "r") as f:
        v = json.load(f)
        return v["cookie"]


def language_id(lang: str) -> str:
    return {
        "cpp": "5028",
        "py": "5055",
    }[lang]

def request_submit(contest_id: str, cookie_text: str, task_id: str, lang: str, source: str):
    submit_url = "https://atcoder.jp/contests/" + contest_id + "/submit"
    session = requests.Session()
    session.headers.update({"Cookie": cookie_text})
    csrf_token = [urlparse.unquote(s) for s in cookie_text.split("%00") if s.startswith("csrf_token")][0]
    csrf_token = csrf_token.split(":")[1]

    submit_info = {
        "csrf_token": csrf_token,
        "data.TaskScreenName": contest_id + "_" + task_id,
        "data.LanguageId": language_id(lang),
        "sourceCode": source
    }

    res = session.post(submit_url, data=submit_info)
    if not res.ok:
        print("Fail submit", file=sys.stderr)
        print(res, file=sys.stderr)
        exit(1)


def main(argv: typing.List[str]) -> int:
    parser = argparse.ArgumentParser(prog='submit')
    parser.add_argument("--contest", required=True)
    parser.add_argument("--task", required=True)
    parser.add_argument("--lang", required=True, choices=["cpp", "py"])
    parser.add_argument("--source", required=True)
    parser.add_argument("--credential-json", default=".credential.json")

    args = parser.parse_args(argv)
    cookie_text = get_cookie_text(args.credential_json)

    source = "(Blank)"
    with open(args.source, "r") as f:
        source = f.read()

    if input("Do you submit? [yes]") != "yes":
        print("Submit canceled")
        return 1

    request_submit(
        contest_id=args.contest,
        cookie_text=cookie_text,
        task_id=args.task,
        lang=args.lang,
        source=source
    )

    print("See result:", "https://atcoder.jp/contests/" + args.contest + "/submissions/me")

    return 0


if __name__ == '__main__':
    exit(main(sys.argv[1:]))
