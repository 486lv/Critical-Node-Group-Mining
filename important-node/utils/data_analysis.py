import matplotlib.pyplot as plt

# 读取数据
x = []
y1 = []
y2 = []

with open('data5.txt', 'r') as file:
    for line in file:
        data = line.split()
        x.append(float(data[0]))  # 第一列是x轴
        y1.append(float(data[1]))  # 第二列是第一条曲线的y值
        y2.append(float(data[2]))  # 第三列是第二条曲线的y值

# 创建子图
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8))

# 绘制折线图
ax1.plot(x, y1, label="D", color='b', marker='o')
ax1.plot(x, y2, label="VOTE", color='r', marker='x')
ax1.set_xlabel('Alpha')
ax1.set_ylabel('Infection Rate')
ax1.set_title('Alpha vs Infection Rate (Line Plot)')
ax1.legend()
ax1.grid(True)

# 设置柱状图的宽度
bar_width = 0.35

# 设置x轴的位置
r1 = range(len(x))
r2 = [i + bar_width for i in r1]

# 绘制柱状图
ax2.bar(r1, y1, color='b', width=bar_width, edgecolor='grey', label='D')
ax2.bar(r2, y2, color='r', width=bar_width, edgecolor='grey', label='VOTE')
ax2.set_xlabel('Alpha')
ax2.set_ylabel('Infection Rate')
ax2.set_title('Alpha vs Infection Rate (Bar Chart)')
ax2.legend()
ax2.set_xticks([r + bar_width/2 for r in range(len(x))])
ax2.set_xticklabels(x)
ax2.grid(True)

# 调整布局并显示图形
plt.tight_layout()
plt.show()