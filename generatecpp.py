#!/usr/bin/env python3
import re
import sys
def remove_default_args(param_string):
    # 去除首尾括号
    if param_string.startswith('(') and param_string.endswith(')'):
        param_string = param_string[1:-1]
    
    params = []
    current_param = []
    depth = 0  # 括号深度
    
    for char in param_string:
        if char == '(':
            depth += 1
        elif char == ')':
            depth -= 1
        elif char == ',' and depth == 0:
            # 遇到参数分隔符
            params.append(''.join(current_param).strip())
            current_param = []
            continue
        
        current_param.append(char)
    
    # 添加最后一个参数
    if current_param:
        params.append(''.join(current_param).strip())
    
    # 处理每个参数，移除默认值
    cleaned_params = []
    for param in params:
        # 查找等号（不在括号内的）
        depth = 0
        eq_index = -1
        for i, c in enumerate(param):
            if c == '(':
                depth += 1
            elif c == ')':
                depth -= 1
            elif c == '=' and depth == 0:
                eq_index = i
                break
        
        if eq_index != -1:
            # 移除等号及其后的内容
            cleaned_params.append(param[:eq_index].rstrip())
        else:
            cleaned_params.append(param)
    
    # 重新组合参数列表
    return '(' + ', '.join(cleaned_params) + ')'
def process_class(content):
    # class_match = re.search(r'class\s+(\w+)(?:\s*:\s*(?:virtual\s+)?(?:public\s+)?\w+(?:\s*,\s*(?:virtual\s+)?(?:public\s+)?\w+)*)?', content)
    # 匹配需要生成定义的类名
    class_match = re.search(r'(?<!friend)\s*class\s+(\w+)\s*(?:final)?\s*(?::\s*(?:(?:(?:virtual|public|protected|private)\s*)*\w+)(?:\s*,\s*(?:(?:virtual|public|protected|private)\s*)*\w+)*)?\s*({)', content)
    
    if not class_match:
        return None, content
    class_start = class_match.start()
    brace_start = class_match.start(2)
    class_name = class_match.group(1)

    brace_count = 1
    i = brace_start + 1
    while i < len(content) and brace_count > 0:
        if content[i] == '{':
            brace_count += 1
        elif content[i] == '}':
            brace_count -= 1
        i += 1
    if brace_count != 0:
        print(f"Error: Mismatched braces in class {class_name}")
        return None, content
    brace_end = i
    class_content = content[brace_start:brace_end]
    remaining_content = content[:class_start]+content[brace_end:]
    definitions = []
    # 删除所有的访问修饰符
    class_content = re.sub(r'public\s*:',' ',class_content)
    class_content = re.sub(r'private\s*:',' ',class_content)
    class_content = re.sub(r'protected\s*:',' ',class_content)
    # 处理构造函数
    while True:
        construct_match= re.search(rf'(?:explicit\s*)?(\~?{class_name})\s*(\(.*?\))([^{{]*?);',class_content)
        if not construct_match:
            break
        construct_pos = construct_match.span()
        class_content = class_content[:construct_pos[0]]+class_content[construct_pos[1]:]

        construct_name = construct_match.group(1)
        construct_parameter = construct_match.group(2)
        construct_suf = construct_match.group(3)
        if re.search('defaule\s+',construct_suf) or re.search('delete\s+',construct_suf):
            continue
        construct_parameter = remove_default_args(construct_parameter)
        construct = f"{class_name}::"+construct_name+construct_parameter+construct_suf
        construct = re.sub(r'\s+', ' ', construct).strip()
        definitions.append(construct+"{\n}\n")
    
    # 处理所有的运算符重载函数
    while True:
        operate_match = re.search('([\w*&: ]+\s*)(\s+operator\s*(?:[\w+\-*\/%^&|!~,=<>()[\]{} ]+)\s*)(\(.*?\))([^{]*?);',class_content)
        if not operate_match:
            break
        operate_pos = operate_match.span()
        class_content = class_content[:operate_pos[0]]+class_content[operate_pos[1]:]
        operate_return = operate_match.group(1)
        operate_name = operate_match.group(2).strip()
        operate_param = operate_match.group(3)
        operate_suf = operate_match.group(4)
        if not re.search(r'friend\s+',operate_return):
            operate_name = f" {class_name}::"+operate_name
        else:
            operate_return = re.sub(r'friend\s+','',operate_return)
        operate_param =remove_default_args(operate_param)
        operator = operate_return+operate_name+operate_param+operate_suf
        operator = re.sub(r'\s+', ' ', operator).strip()
        definitions.append(operator+"{\n}\n")
    
    # 处理所有普通函数
    while True:
        func_match = re.search(r'([\w*& :]+)(\s+\w+\s*)(\([^{]*?\))([^{]*?);',class_content)
        if not func_match:
            break
        func_pos = func_match.span()
        class_content = class_content[:func_pos[0]]+class_content[func_pos[1]:]
        func_return = func_match.group(1)
        func_name = func_match.group(2).strip()
        func_param = func_match.group(3)
        func_suf = func_match.group(4)
        if not re.search(r'friend\s+',func_return):
            func_name = f' {class_name}::'+func_name
        else:
            func_return = re.sub(r'friend\s+','',func_return)
        func_param = remove_default_args(func_param)
        func = func_return+func_name+func_param+func_suf
        func = re.sub(r'\s+',' ',func).strip()
        parts = func.split(' ')
        parts = [s for s in parts if s != 'virtual' and s!= 'override' and s!= 'static']
        func = ' '.join(parts)
        definitions.append(func+"{\n}\n")
    
    return definitions, remaining_content

def process_global_functions(content):
    definitions=[]
    while True:
        func_match = re.search(r'([\w*& :]+)(\s+\w+\s*)(\([^{]*?\))([^{]*?);',content)
        if not func_match:
            break;
        func_pos = func_match.span()
        content = content[:func_pos(0)]+content[func_pos(1):]
        func_return = func_match.group(1).strip()
        func_name = func_match.group(2).strip()
        func_param = func_match.group(3).strip()
        func_suf = func_match.group(4).strip()
        func_param = remove_default_args(func_param)
        func = func_return+' '+func_name+' '+func_param+' '+func_suf
        func = re.sub(r'\s+',' ',func).strip()
        definitions.append(func+"{\n}\n")
    return definitions

def process_header(input_file, output_file):
    try:
        with open(input_file, 'r', encoding='utf-8') as f:
            content = f.read()
    except Exception as e:
        print(f"Error: Could not read file {input_file}: {e}")
        sys.exit(1)
    function_definitions = []
    # 移除所有注释
    # 单行注释
    content = re.sub(r'\/\/.*?(?=\n)','',content) # 处理不了字符串中包含//的情况
    # 多行注释
    content = re.sub(r'\/\*.*?\*\/','',content,flags=re.DOTALL)
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