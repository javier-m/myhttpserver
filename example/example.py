#!/usr/bin/env python3.6

import sys

request = sys.stdin.read()

body = ("<!doctype html>\n"
        "<html>\n"
        "<body>\n"
        "<div>YOUR REQUEST</div>\n"
        "<div>\n"
        + request +
        "</div>\n"
        "</body>\n"
        "</html>\n")

header = ("HTTP/1.1 200 OK\n"
          "Content-Length: " + str(len(body)) + "\n"
          "Content-Type: text/html\n"
          "\n")

response = header + body

print(response)
