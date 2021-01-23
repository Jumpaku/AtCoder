from bs4 import BeautifulSoup
import requests
# import requests_cache
import urllib.parse as urlparse
import sys
import os
import re
from cachecontrol import CacheControl

"""
python3 /home/scripts/submit.py contest_data_file probrem language src_file_name
"""

contest_data = sys.argv[1]
with open(contest_data, "r") as f:
    (contest_id, username, password) = f.read().split()[:3]
""""""

print("Contest ID:", contest_id)
print("Username:", username)
print("Password:****")

probrem = sys.argv[2]
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
language = sys.argv[3]
if language not in language_id:
    print("Language ({}) not found in {}".format(language, language_id))
    exit()
print("Language:", language)
src_file = sys.argv[4]
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
with open("/home/tasks/" + probrem + "/limit.txt", "r") as f:
    limits = [it.strip() for it in f.read().split("/")]
    print("")
    if limits[0] != "Time Limit: 2 sec":
        print("  "+limits[0]+" !!")
    if limits[1] != "Memory Limit: 1024 MB":
        print("  "+limits[1]+" !!")
    print("")
submitYes = ("Yes" == input("Do you submit? [Yes]"))
if not submitYes:
    print("Submit canceled")
    exit()

submit_res = session.post(submit_url, data=submit_info)
"""

"""
if not submit_res.ok:
    print("Fail submit")
    print(submit_res)
    exit()
print("See result:", "https://atcoder.jp/contests/" +
      contest_id + "/submissions/me")
