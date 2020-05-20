from bs4 import BeautifulSoup
import requests

# "abc168"
print("Contest ID?")
contest_id = input()
print(contest_id)
# "L64ySwL"
print("Username?")
username = input()
print(username)
# "hPzeX9BhRAQNRpAGGXjwQWp73YMcgvhC"
print("Password?")
password = input()
print(password)

tasks_url = "https://atcoder.jp/contests/" + contest_id + "/tasks_print"
login_url = "https://atcoder.jp/login"

session = requests.Session()

login_res = session.get(login_url)
login_html = BeautifulSoup(login_res.text, "html.parser")
csrf_token = login_html.find_all(attrs={"name": "csrf_token"})[0]["value"]
login_info = {
    "username": username,
    "password": password,
    "csrf_token": csrf_token
}
if not session.post(login_url, data=login_info).ok:
    print("Fail login")
    print(login_info)
    exit()

tasks_res = session.get(tasks_url)
tasks_html = BeautifulSoup(tasks_res.text, "html.parser")

problem = "a"
for task in tasks_html.find_all("div", class_="col-sm-12"):
    title = task.find("span", class_="h2")
    statement = task.find("span", class_="lang-en")
    if (not title) or (not statement):
        continue
    print(title.get_text())
    for section in statement.find_all("section"):
        h3s = section.find("h3")
        pre = section.find("pre")
        if h3s and pre and "Sample Input" in h3s.get_text():
            with open("./samples/" + problem + ".in", mode="a") as sample_in:
                sample_in.write("\n" + pre.get_text())
        if h3s and pre and "Sample Output" in h3s.get_text():
            with open("./samples/" + problem + ".ans", mode="a") as sample_out:
                sample_out.write(pre.get_text())

    problem = chr(ord(problem) + 1)
