# 打开输入文件并读取内容
with open('Anaheim.txt', 'r') as file:
    # 打开输出文件以写入结果
    with open('output.txt', 'w') as output_file:
        for line in file:
            # 分割每行数据
            columns = line.split()  # 默认按空格或制表符分割
            col1 = columns[0]
            col2 = columns[1]

            # 写入前两列到输出文件，每列之间用空格分隔

print("提取的前两列已保存到 'output.txt' 文件中。")
