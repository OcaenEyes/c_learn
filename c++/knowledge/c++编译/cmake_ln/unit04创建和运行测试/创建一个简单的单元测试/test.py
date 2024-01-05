import subprocess
import argparse
# Python脚本调用可执行文件(使用--executable命令行参数传递)，并使用--short命令行参数执行：
parser = argparse.ArgumentParser()
parser.add_argument('--executable',help='要执行的文件-的完整路径')
parser.add_argument('--short',defauly=False,action='store_true',help="执行测试")

args = parser.parse_args()

def execute_cpp_code(integers):
    result = subprocess.check_output([args.executable] + integers)
    return int(result)
if args.short:
    # we collect [1, 2, ..., 100] as a list of strings
    result = execute_cpp_code([str(i) for i in range(1, 101)])
    assert result == 5050, 'summing up to 100 failed'
else:
    # we collect [1, 2, ..., 1000] as a list of strings
    result = execute_cpp_code([str(i) for i in range(1, 1001)])
    assert result == 500500, 'summing up to 1000 failed'