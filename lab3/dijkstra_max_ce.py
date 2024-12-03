import matplotlib.pyplot as plt

# 从结果文件中读取数据
sizes, times = [], []
with open('result_3.1.txt', 'r') as f:
    for line in f:
        if "Dataset size" in line:
            size = int(line.split(': ')[1].split(' ')[0])
            time = int(line.split(': ')[2].split(' ')[0])
            sizes.append(size)
            times.append(time)

# 绘制图像
plt.figure(figsize=(10, 6))
plt.plot(sizes, times, marker='o', label='Dijkstra Performance')
plt.xscale('log')  # 数据规模跨度大，使用对数刻度
plt.yscale('log')
plt.xlabel('Dataset size (nodes)')
plt.ylabel('Running time (ms)')
plt.title('Dijkstra Algorithm Performance on Different Dataset Sizes')
plt.legend()
plt.grid(True)
plt.savefig('performance_plot.png')
plt.show()
