import os
from bs4 import BeautifulSoup
import requests
import urllib.parse as urlparse
from sys import stdin
import sys
from functools import reduce
import re

contest_data = sys.argv[1]
with open(contest_data, "r") as f:
    (contest_id, username, password) = f.read().split()[:3]
""""""

print("Contest ID:", contest_id)
print("Username:", username)
print("Password:****")

tasks_url = "https://atcoder.jp/contests/" + contest_id + "/tasks_print?lang=en"
login_url = "https://atcoder.jp/login?continue=" + \
    urlparse.quote(tasks_url, "")

session = requests.Session()

print(login_url)
login_res = session.get(login_url)
login_html = BeautifulSoup(login_res.text, "html.parser")
csrf_token = login_html.find_all(attrs={"name": "csrf_token"})[0]["value"]
login_info = {
    "username": username,
    "password": password,
    "csrf_token": csrf_token
}
tasks_res = session.post(login_url, data=login_info)
if not tasks_res.ok:
    print("Fail login")
    print(login_info)
    print(tasks_res)
    exit()
html_text = tasks_res.text

"""
html_text = reduce(lambda t0, t1: t0+t1, stdin)
"""

html_text = re.sub(r"\r\n|\r|\n", "\n", html_text)
tasks_html = BeautifulSoup(html_text, "lxml")

problem = "a"
os.makedirs("/home/limits/", exist_ok=True)
for task in tasks_html.find_all("div", class_="col-sm-12"):
    title = task.find("span", class_="h2")
    statement = task.find("span", class_="lang-en")
    if (not title) or (not statement):
        continue
    limits = task.p.get_text()
    print(title.get_text(), "--", limits)
    if limits:
        with open("/home/limits/" + problem + ".limit", "w") as f:
            f.write(limits)
    for section in statement.find_all("section"):
        h3s = section.find("h3")
        pre = section.find("pre")
        if h3s and pre and "Sample Input" in h3s.get_text():
            with open("./samples/" + problem + ".in", mode="a") as sample_in:
                sample_in.write("\n" + pre.get_text())
        if h3s and pre and "Sample Output" in h3s.get_text():
            with open("./samples/" + problem + ".ans", mode="a") as sample_out:
                sample_out.write("\n" + pre.get_text())

    problem = chr(ord(problem) + 1)
