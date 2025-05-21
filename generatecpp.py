#!/usr/bin/env python3
import re
import sys

def process_class(content):
    # class_match = re.search(r'class\s+(\w+)(?:\s*:\s*(?:virtual\s+)?(?:public\s+)?\w+(?:\s*,\s*(?:virtual\s+)?(?:public\s+)?\w+)*)?', content)
    # 匹配需要生成定义的类名
    class_match = re.search(r'(?<!\w)(?<!friend\s)class\s+(\w+)\s*(?:final)?\s*(?::\s*(?:(?:(?:virtual|public|protected|private)\s*)*\w+)(?:\s*,\s*(?:(?:virtual|public|protected|private)\s*)*\w+)*)?\s*{', content)
    if not class_match:
        return None, content
    class_name = class_match.group(1)
    class_start = re.search(rf'class\s+{class_name}\s*(?::\s*(?:virtual\s+)?(?:public\s+)?\w+(?:\s*,\s*(?:virtual\s+)?(?:public\s+)?\w+)*)?\s*{{', content)
    if not class_start:
        print(f"Error: Could not find class definition start for {class_name}")
        return None, content
    start_pos = class_start.end() - 1
    brace_count = 1
    i = start_pos + 1
    while i < len(content) and brace_count > 0:
        if content[i] == '{':
            brace_count += 1
        elif content[i] == '}':
            brace_count -= 1
        i += 1
    if brace_count != 0:
        print(f"Error: Mismatched braces in class {class_name}")
        return None, content
    class_content = content[start_pos:i]
    remaining_content = content[i:]
    class_content = re.sub(r'^\s*(public|private|protected):\s*', '', class_content, flags=re.MULTILINE)
    func_pattern = r'(virtual\s+)?([\w:&<>]+\s*[\*&]?\s*)?(operator[\w<>=!+\-*]+)?\s*(\w+)?\s*\(\s*([^)]*)\s*\)\s*(const)?\s*(?:override)?\s*(?:=\s*0)?\s*;'
    functions = re.findall(func_pattern, class_content, re.MULTILINE)
    definitions = []
    for func in functions:
        virtual, return_type, op_name, func_name, params, const = func
        # 确保匹配到有效的函数名
        if not func_name and not op_name:
            continue
        # 跳过构造函数和析构函数
        if func_name == class_name or (func_name and func_name.startswith('~')):
            continue
        # 清理参数列表，去除默认值
        cleaned_params = []
        for p in params.split(','):
            p = p.strip()
            if p:
                p = re.sub(r'\s*=\s*[^,)]+', '', p)
                cleaned_params.append(p)
        params = ', '.join(cleaned_params)
        # 处理返回类型
        return_type = return_type.strip() if return_type else ''
        if return_type.startswith('virtual '):
            return_type = return_type[len('virtual '):].strip()
        const = ' const' if const else ''
        # 处理操作符重载
        if op_name:
            func_name = f'operator{op_name[len("operator"):]}'
        # 生成函数定义
        func_def = f"{return_type} {class_name}::{func_name}({params}){const} {{\n    // TODO: Implement\n}}\n"
        definitions.append(func_def)
    return definitions, remaining_content

def process_global_functions(content):
    global_func_pattern = r'^\s*(?!class|struct)(\w+\s+)+(\w+)(\s*\(\s*[^;]*\s*\))\s*;'
    matches = re.finditer(global_func_pattern, content, re.MULTILINE)
    definitions = []
    for match in matches:
        return_type = match.group(1).strip()
        func_name = match.group(2).strip()
        params = match.group(3).strip()
        cleaned_params = []
        for p in params[1:-1].split(','):
            p = p.strip()
            if p:
                p = re.sub(r'\s*=\s*[^,)]+', '', p)
                cleaned_params.append(p)
        params = ', '.join(cleaned_params)
        func_def = f"{return_type} {func_name}({params}) {{\n    // TODO: Implement\n}}\n"
        definitions.append(func_def)
    return definitions

def process_header(input_file, output_file):
    try:
        with open(input_file, 'r', encoding='utf-8') as f:
            content = f.read()
    except Exception as e:
        print(f"Error: Could not read file {input_file}: {e}")
        sys.exit(1)
    function_definitions = []
    while True:
        defs, content = process_class(content)
        if defs is None:
            break
        function_definitions.extend(defs)
    # 需要修改全局匹配
    global_defs = process_global_functions(content)
    function_definitions.extend(global_defs)
    try:
        output = [f'#include "{input_file}"\n\n'] + function_definitions
        with open(output_file, 'w', encoding='utf-8') as f:
            f.writelines(output)
        print(f"Successfully generated {output_file}!")
    except Exception as e:
        print(f"Error: Could not write to file {output_file}: {e}")
        sys.exit(1)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: python3 script.py input.h [output.cpp]")
        sys.exit(1)
    input_path = sys.argv[1]
    output_path = sys.argv[2] if len(sys.argv) >= 3 else input_path.replace('.h', '.cpp')
    process_header(input_path, output_path)