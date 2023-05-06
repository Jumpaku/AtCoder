#!/bin/python3
import json
import os
import re
import sys
import typing
import argparse
import urllib.parse as urlparse

import requests
from bs4 import BeautifulSoup


def get_user_password(cred_path) -> typing.Dict[str, str]:
    with open(cred_path, "r") as f:
        v = json.load(f)
        return {"username": v["username"], "password": v["password"]}


def request_tasks(contest_id: str, username: str, password: str):
    tasks_url = "https://atcoder.jp/contests/" + contest_id + "/tasks_print?lang=en"
    login_url = "https://atcoder.jp/login?continue=" + urlparse.quote(tasks_url, "")
    session = requests.Session()
    login_res = session.get(login_url)
    login_html = BeautifulSoup(login_res.text, "html.parser")
    csrf_token = login_html.find_all(attrs={"name": "csrf_token"})[0]["value"]
    login_info = {
        "username": username,
        "password": password,
        "csrf_token": csrf_token
    }
    res = session.post(login_url, data=login_info)
    if not res.ok:
        print("Fail login", file=sys.stderr)
        print(login_info, file=sys.stderr)
        print(res, file=sys.stderr)
        exit()
    return res


def scrape_tasks(tasks_html):
    os.makedirs("/work/tasks/", exist_ok=True)

    tasks = []
    for task_div in tasks_html.find_all("div", class_="col-sm-12"):
        title_span = task_div.find("span", class_="h2")
        statement_span = task_div.find("span", class_="lang-en")
        if (not title_span) or (not statement_span):
            continue
        task = dict()

        limits = task_div.p.get_text()
        if limits:
            task["task"] = chr(ord("a") + len(tasks))
            task["limit"] = limits

        for section in statement_span.find_all("section"):
            h3s = section.find("h3")
            pre = section.find("pre")
            if h3s and pre and "Sample Input" in h3s.get_text():
                if "input" not in task:
                    task["input"] = []
                task["input"].append(pre.get_text())
            if h3s and pre and "Sample Output" in h3s.get_text():
                if "answer" not in task:
                    task["answer"] = []
                task["answer"].append(pre.get_text())

        tasks.append(task)
    return tasks


def main(argv: typing.List[str]) -> int:
    parser = argparse.ArgumentParser(prog='submit')
    parser.add_argument("--contest", required=True)
    parser.add_argument("--credential-json", default=".credential.json")

    args = parser.parse_args(argv)
    cred = get_user_password(args.credential_json)
    contest_id = args.contest

    response = request_tasks(
        contest_id=contest_id,
        username=cred["username"],
        password=cred["password"]
    )

    html_text = re.sub(r"\r\n|\r|\n", "\n", response.text)
    tasks_html = BeautifulSoup(html_text, "lxml")
    tasks = scrape_tasks(tasks_html)

    print(json.dumps({
        "contest": contest_id,
        "title": tasks_html.find_all("title")[0].get_text(),
        "tasks": tasks
    }))

    return 0


if __name__ == '__main__':
    exit(main(sys.argv[1:]))
