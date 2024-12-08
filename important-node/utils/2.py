# 定义一个集合用于存储不同的数字
unique_numbers = set()

# 变量用于计数行数
line_count = 0

# 打开文件并读取内容
with open('Anaheim.txt', 'r') as file:
    for line in file:
        line_count += 1  # 每读取一行，行数加1
        # 拆分行数据并添加到集合中
        columns = line.split()
        for value in columns:
            try:
                # 尝试将字符串转为数字并加入集合
                unique_numbers.add(float(value))
            except ValueError:
                # 如果不能转换为数字（如非数字字符），跳过
                continue

# 输出结果
print(f"文件共有 {line_count} 行。")
print(f"文件中一共包含 {len(unique_numbers)} 种不同的数字。")
