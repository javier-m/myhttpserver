#!/usr/bin/env python3.6

# Example
# Should accept an http request on stdin
# and output an http response on stdout

import sys
import time
import random

wait_time_s = random.uniform(0, 10)

request = sys.stdin.read()

body = ("<!doctype html>\n"
        "<html>\n"
        "<body>\n"
        "<div>WAIT TIME: " + str(wait_time_s) + "s</div>\n"
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

time.sleep(wait_time_s)

print(response)
