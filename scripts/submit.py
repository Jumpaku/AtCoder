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
print("Password:", password)

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
# if "value" in opt and opt["value"].endswith("_"+probrem)][0]["value"]
select_task = submit_html.find("select", attrs={"id": "select-task"})
screen_task_name = [opt["value"] for opt in select_task.find_all("option")
                    if opt["value"].endswith("_"+probrem)][0]
submit_info = {
    "csrf_token": csrf_token,
    "data.TaskScreenName": screen_task_name,
    "data.LanguageId": language_id[language],
    "sourceCode": src_content
}
print("Submit:", submit_url)
"""
POST /contests/m-solutions2020/submit HTTP/2
Host: atcoder.jp
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:78.0) Gecko/20100101 Firefox/78.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate, br
Content-Type: application/x-www-form-urlencoded
Content-Length: 20439
Origin: https://atcoder.jp
Connection: keep-alive
Referer: https://atcoder.jp/contests/m-solutions2020/submit
Cookie: REVEL_SESSION=930ab5cbb68d10a3d2e7e63113fef37a7a0e58e1-%00csrf_token%3Aal26EQs%2BNMyqda0K2ZJ8%2BqSm8WNIZXAjKYnfAM4PFMg%3D%00%00a%3Afalse%00%00_TS%3A1611238439%00%00w%3Afalse%00%00Rating%3A0%00%00UserName%3AL64ySwL%00%00UserScreenName%3AL64ySwL%00%00SessionKey%3A00a3ab8ad671cdb19ddcf42647e0acf6a1c897b81a607638fa4c0bf85c710621fdefc74a4ebdfa-96b5740fbfa9c856026f19e934dcea98158fa7fd01f778f10f4c4ff9933e0e95%00; _ga=GA1.2.1344004464.1583114847; language=en; __pp_uid=IjuGL7O4fTdteSFRl1SIuHZafd0aGxvO; REVEL_FLASH=; timeDelta=-398; _gid=GA1.2.1053771269.1595685705
Upgrade-Insecure-Requests: 1
Pragma: no-cache
Cache-Control: no-cache
TE: Trailers
"""
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
