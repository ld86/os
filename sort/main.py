#!/usr/bin/python3

import os
import sys
import io
import re

def main():
  items = []
  for filename in sys.argv[1:]:
    if not os.path.exists(filename):
      print("Warning: %s not found, skip" % filename)
      continue
    try:
        items += re.findall(r'-?[0-9]+',io.open(filename).read())
    except Exception as e:
        print("Fatal exception %s, continue" % e)
  items.sort(key=int)
  [print(i) for i in items]

if __name__ == "__main__":
  try:
    main()
  except MemoryError as e:
    print("Error: Out of memory exception")
