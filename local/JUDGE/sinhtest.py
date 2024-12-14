import random
import time
import os
import subprocess
from datetime import datetime
import sys

EXTENSION = ".exe"
NAME = "SOLVE"
CODE = "DIV369"
NTEST = 100
TIME_LIMIT = 1
writetest = False
wronglog = True
wrongexit = True
verdict = ""
total_points = 100.0
avg_points = total_points / NTEST
cur_pts = 0
cur_ac = 0
cur_time = 0
ac = 0
wa = 0
tle = 0

def rand(l, h):
    return random.randint(l, h)

def roundk(number, k):
    return f"{number:.{k}f}"

def pad(n):
    return f"{n:02d}"

def get_time():
    now = datetime.now()
    return f"{pad(now.hour)}:{pad(now.minute)}:{pad(now.second)} - {pad(now.day)}/{pad(now.month)}/{now.year}"

def random_str(size, mode="num"):
    if mode == "num":
        result = []
        for _ in range(size // 18):
            result.append(str(rand(10**17, 10**18 - 1)))
        result.append(''.join(str(rand(0, 9)) for _ in range(size % 18)))
        return ''.join(result)
    else:
        characters = "abcdefghijklmnopqrstuvwxyz"
        return ''.join(random.choice(characters) for _ in range(size))

def main():
    global cur_pts, cur_ac, cur_time, ac, wa, tle, verdict

    log_file = open(f"Judges\\[JUDGE] {CODE}.log", "w")
    log_file.write(f"Problem: {CODE}\nJudge Time: {get_time()}\n\n-------------------- JUDGE --------------------\n")

    def process():
        global cur_pts, cur_ac, cur_time, ac, wa, tle, verdict
        input_str = ""

        ############ INPUT ############
        n = rand(1, 10**999)
        input_str += f"{n}"
        ###############################

        with open(f"{NAME}.INP", "w") as inp_file:
            inp_file.write(input_str)

        start = time.time()
        sys.stdout.write(f"Running Test {iTest}/{NTEST}\n")
        subprocess.run(f"{NAME}{EXTENSION}", check=True, shell=True)
        duration = (time.time() - start) * 1000

        if duration > 1000.0 * TIME_LIMIT:
            log_file.write(f"[Score:0.00][Time:>{TIME_LIMIT}s] Test {iTest}: Time Limit Exceeded\n")
            tle += 1
            return

        subprocess.run(f"{NAME}_trau{EXTENSION}", check=True, shell=True)

        cur_time += duration / 1000.0
        is_wrong = False

        if subprocess.run(["fc", f"{NAME}.OUT", f"{NAME}.ans"], shell=True).returncode != 0:
            log_file.write(f"[Score:0.00][Time:{roundk(duration / 1000.0, 3)}s] Test {iTest}: Wrong Answer\n")
            wa += 1
            if wronglog:
                is_wrong = True
            if wrongexit:
                exit(1)
        else:
            cur_pts += avg_points
            cur_ac += 1
            log_file.write(f"[Score:{roundk(avg_points, 2)}][Time:{roundk(duration / 1000.0, 3)}s] Test {iTest}: Accepted\n")
            ac += 1

        if writetest or is_wrong:
            log_file.write(f"- Input:\n{input_str[:min(len(input_str), 100)]}{'...' if len(input_str) > 100 else ''}\n")
            with open(f"{NAME}.OUT", "r") as out_file:
                log_file.write("- Output:\n" + out_file.read() + "\n")
            with open(f"{NAME}.ans", "r") as ans_file:
                log_file.write("- Expected answer:\n" + ans_file.read() + "\n\n")

    start_judge_time = time.time()
    for iTest in range(1, NTEST + 1):
        process()

    if ac == NTEST:
        verdict = "Accepted"
    if wa > 0:
        verdict = "Wrong Answer"
    if tle > 0:
        verdict = "Time Limit Exceeded"
    if wa > 0 and tle > 0:
        verdict = "Wrong Answer + Time Limit Exceeded"

    log_file.write("\n-------------------- SCORE --------------------")
    log_file.write(f"\n* Total points: {roundk(cur_pts, 2)}/{total_points}.00 ({cur_ac}/{NTEST})")
    log_file.write(f"\n* Total runtime: {roundk(cur_time, 2)}s - Average: {roundk(cur_time / NTEST, 2)}s/case")
    log_file.write(f"\n* Result types:\n    - Accepted: {ac}\n    - Wrong Answer: {wa}\n    - Time Limited Exceeded: {tle}")
    log_file.write(f"\n(*) Overall result: {verdict}")
    log_file.write(f"\n\n[Finished in {roundk(time.time() - start_judge_time, 2)}s]\n")

    print(f"\nTotal points: {roundk(cur_pts, 2)}/{total_points}.00 ({cur_ac}/{NTEST})\n")
    log_file.close()

if __name__ == "__main__":
    main()
