# AtCoder

Competitive programming environment that supports C++ 14 and Python 3.

1. Open folder in container with VSCode Insiders.
2. Type `make help` to see help.


## GitHub Authentication

https://git-scm.com/docs/gitcredentials

```sh
USER=#GitHub username
PAT=#GitHub personal access token for username
CREDENTIAL=#Git credential file path
git config credential.helper "store --file=${CREDENTIAL}"
git config "credential.https://github.com/Jumpaku/AtCoder.git" "${USER}"
echo "https://${USER}:${PAT}@github.com" > "${CREDENTIAL}"
```