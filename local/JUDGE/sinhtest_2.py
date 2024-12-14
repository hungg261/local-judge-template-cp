import random
import time
import os
import subprocess
from datetime import datetime
import sys
from concurrent.futures import ThreadPoolExecutor, as_completed

EXTENSION = ".exe"
NAME = "SOLVE"
CODE = "TEST_MULTHREAD"
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

def process_test_case(iTest, input_str, test_dir):
    global cur_pts, cur_ac, cur_time, ac, wa, tle, verdict

    os.makedirs(test_dir, exist_ok=True)
    
    input_file_path = os.path.join(test_dir, f"{NAME}.INP")
    output_file_path = os.path.join(test_dir, f"{NAME}.OUT")
    ans_file_path = os.path.join(test_dir, f"{NAME}.ans")
    
    # Write input file
    with open(input_file_path, "w") as inp_file:
        inp_file.write(input_str)
    
    # Run the solve file
    start = time.time()
    sys.stdout.write(f"Running Test {iTest}/{NTEST}\n")
    try:
        subprocess.run(f"{NAME}{EXTENSION}", cwd=test_dir, check=True, shell=True)
    except: pass
    duration = (time.time() - start) * 1000
    
    if duration > 1000.0 * TIME_LIMIT:
        with open(f"Judges\\[JUDGE] {CODE}.log", "a") as log_file:
            log_file.write(f"[Score:0.00][Time:>{TIME_LIMIT}s] Test {iTest}: Time Limit Exceeded\n")
        tle += 1
        return

    try:
        subprocess.run(f"{NAME}_trau{EXTENSION}", cwd=test_dir, check=True, shell=True)
    except: pass
    
    if subprocess.run(["fc", output_file_path, ans_file_path], shell=True).returncode != 0:
        with open(f"Judges\\[JUDGE] {CODE}.log", "a") as log_file:
            log_file.write(f"[Score:0.00][Time:{roundk(duration / 1000.0, 3)}s] Test {iTest}: Wrong Answer\n")
        wa += 1
        if wronglog:
            with open(f"Judges\\[JUDGE] {CODE}.log", "a") as log_file:
                log_file.write(f"- Input:\n{input_str[:min(len(input_str), 100)]}{'...' if len(input_str) > 100 else ''}\n")
                with open(output_file_path, "r") as out_file:
                    log_file.write("- Output:\n" + out_file.read() + "\n")
                with open(ans_file_path, "r") as ans_file:
                    log_file.write("- Expected answer:\n" + ans_file.read() + "\n\n")
        if wrongexit:
            sys.exit(1)
    else:
        with open(f"Judges\\[JUDGE] {CODE}.log", "a") as log_file:
            log_file.write(f"[Score:{roundk(avg_points, 2)}][Time:{roundk(duration / 1000.0, 3)}s] Test {iTest}: Accepted\n")
        cur_pts += avg_points
        cur_ac += 1
        ac += 1

    cur_time += duration / 1000.0

def main():
    global cur_pts, cur_ac, cur_time, ac, wa, tle, verdict

    log_file_path = f"Judges\\[JUDGE] {CODE}.log"
    with open(log_file_path, "w") as log_file:
        log_file.write(f"Problem: {CODE}\nJudge Time: {get_time()}\n\n-------------------- JUDGE --------------------\n")
    
    start_judge_time = time.time()
    
    # Prepare test cases
    test_cases = []
    for iTest in range(1, NTEST + 1):
        n = rand(1, 1000)
        k = rand(1, 1000)
        sm = 0
        input_str = f"{n} {k}\n"
        
        for _ in range(n):
            s = rand(1, 10**6)
            input_str += f"{s} "
            sm += s
        input_str += "\n"
        for _ in range(k):
            input_str += f"{rand(1, sm)} "
        
        test_dir = f"test_case_{iTest}"
        test_cases.append((iTest, input_str, test_dir))
    
    # Create and start worker threads
    num_workers = min(NTEST, 4)  # Adjust based on your system
    with ThreadPoolExecutor(max_workers=num_workers) as executor:
        futures = [executor.submit(process_test_case, iTest, input_str, test_dir) for iTest, input_str, test_dir in test_cases]
        for future in as_completed(futures):
            try:
                future.result()
            except Exception as e:
                print(f"Test case failed: {e}")

    if ac == NTEST:
        verdict = "Accepted"
    if wa > 0:
        verdict = "Wrong Answer"
    if tle > 0:
        verdict = "Time Limit Exceeded"
    if wa > 0 and tle > 0:
        verdict = "Wrong Answer + Time Limit Exceeded"

    with open(log_file_path, "a") as log_file:
        log_file.write("\n-------------------- SCORE --------------------")
        log_file.write(f"\n* Total points: {roundk(cur_pts, 2)}/{total_points}.00 ({cur_ac}/{NTEST})")
        log_file.write(f"\n* Total runtime: {roundk(cur_time, 2)}s - Average: {roundk(cur_time / NTEST, 2)}s/case")
        log_file.write(f"\n* Result types:\n    - Accepted: {ac}\n    - Wrong Answer: {wa}\n    - Time Limited Exceeded: {tle}")
        log_file.write(f"\n(*) Overall result: {verdict}")
        log_file.write(f"\n\n[Finished in {roundk(time.time() - start_judge_time, 2)}s]\n")

    print(f"\nTotal points: {roundk(cur_pts, 2)}/{total_points}.00 ({cur_ac}/{NTEST})\n")

if __name__ == "__main__":
    main()
