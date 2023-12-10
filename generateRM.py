#!/usr/bin/python3

import os
import subprocess
import timeit

content = [
  '# 🎄 Advent of Code 2023 🎄',
  'Solutions for [Advent of Code 2023](https://adventofcode.com/2023). This years objective is to write somewhat performant C code.',
  '## Usage',
  '```make && ./aoc [day_number] [performance_amount]```',
  '## Solution info for days'
]
dirs = [f for f in os.listdir('.') if os.path.isdir(f) and f[0:3] == 'AoC']
emojis = ['👼','🎅','🤶','🧑‍🎄','🧝','🧝‍♂️','🧝‍♀️','👪','🦌','🍪','🥛','🍷','🍴','⛪','🌟','❄️','☃️','⛄','🔥','🎄','🎁','🧦','🔔','🎶','🕯️','🛐','✝️']
dirs.sort(key=lambda s: int(s[3:]))
content.append('| 🎄 | Day | Time | #1 | #2 |')
content.append('| --- | --- | --- | --- | --- |')
for i,dir in enumerate(dirs):
    fileName = dir + '/' + dir.lower() + '.c'
    time = subprocess.check_output([f'./aoc', f'{i+1}', '100'])
    time = '{:g}'.format(float('{:.{p}g}'.format(float(time)*1000_000, p=2)))
    content.append(f'| [{emojis[i]}](https://adventofcode.com/2023/day/{dir.replace("AoC","")}) | [{dir.  replace("aoc", "Day ").capitalize()}]({fileName}) | {time} μs | ✅ | ✅ |')

with open('README.md', 'w') as file:
    file.write('\n'.join(content))
