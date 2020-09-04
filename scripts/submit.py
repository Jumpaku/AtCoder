from bs4 import BeautifulSoup
import requests
# import requests_cache
import urllib.parse as urlparse
import sys
import os
import re
from cachecontrol import CacheControl

"""
python3 /home/scripts/submit.py probrem language src_file_name
"""

# requests_cache.install_cache('demo_cache')


# "abc168"
print("Contest ID?")
contest_id = input()
print("Contest ID:", contest_id)
# "L64ySwL"
print("Username?")
username = input()
print("Username:", username)
# "hPzeX9BhRAQNRpAGGXjwQWp73YMcgvhC"
print("Password?")
password = input()
print("Password:****")

print(sys.argv)
probrem = sys.argv[1]
print("Probrem:", probrem)
language_id = {
    "cplusplus": 4003,
    "python3": 4006,
    "pypy3": 4047
}
language_extension = {
    "cplusplus": "cpp",
    "python3": "py",
    "pypy3": "py"
}
language = sys.argv[2]
if language not in language_id:
    print("Language ({}) not found in {}".format(language, language_id))
    exit()
print("Language:", language)
src_file = sys.argv[3]
if not os.path.exists(src_file):
    print("File ({}) not found".format(src_file))
    exit()
if not src_file.endswith(language_extension[language]):
    print("Wrong extension ({}) for {}".format(src_file, language))
    exit()
print("File:", src_file)
with open(src_file, 'r') as f:
    src_content = f.read()
submit_url = "https://atcoder.jp/contests/" + contest_id + "/submit?lang=en"
login_url = "https://atcoder.jp/login?continue=" + \
    urlparse.quote(submit_url, "")

session = CacheControl(requests.Session())

print("Login:", login_url)
login_res = session.get(login_url)
login_html = BeautifulSoup(login_res.text, "html.parser")
csrf_token = login_html.find_all(attrs={"name": "csrf_token"})[0]["value"]
login_info = {
    "username": username,
    "password": password,
    "csrf_token": csrf_token
}
login_res = session.post(login_url, data=login_info)
if not login_res.ok:
    print("Fail login")
    print(login_res.headers)
    print(login_res.status_code)
    exit()
html_text = re.sub(r"\r\n|\r|\n", "\n", login_res.text)
submit_html = BeautifulSoup(html_text, "lxml")
csrf_token = submit_html.find_all(attrs={"name": "csrf_token"})[0]["value"]
select_task = submit_html.find("select", attrs={"id": "select-task"})

screen_task_name_candidates = list(select_task.find_all("option"))
print("screen_task_names: ")
for candidate in screen_task_name_candidates:
    print("\t", candidate)

screen_task_name = [opt["value"]
                    for opt in screen_task_name_candidates
                    if opt.get_text(strip=True).lower().startswith(probrem)][0]
submit_info = {
    "csrf_token": csrf_token,
    "data.TaskScreenName": screen_task_name,
    "data.LanguageId": language_id[language],
    "sourceCode": src_content
}
print("Submit:", submit_url)


session.headers["Host"] = "atcoder.jp"
session.headers["User-Agent"] = "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:78.0) Gecko/20100101 Firefox/78.0"
session.headers["Accept"] = "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"
session.headers["Accept-Language"] = "en-US,en;q=0.5"
session.headers["Accept-Encoding"] = "gzip, deflate, br"
session.headers["Content-Type"] = "application/x-www-form-urlencoded"
session.headers["Origin"] = "https://atcoder.jp"
session.headers["Connection"] = "keep-alive"
session.headers["Upgrade-Insecure-Requests"] = "1"
session.headers["Pragma"] = "no-cache"
session.headers["Cache-Control"] = "no-cache"
session.headers["TE"] = "Trailers"

submit_res = session.post(submit_url, data=submit_info)
"""

"""
if not submit_res.ok:
    print("Fail submit")
    print(submit_res)
    exit()
print("See result:", "https://atcoder.jp/contests/" +
      contest_id + "/submissions/me")
