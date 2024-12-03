import matplotlib.pyplot as plt

# 数据
scales = ["Small", "Medium", "Large"]
times = [0, 0, 0.081]  # 运行时间（单位：秒）
lis_lengths = [4, 61, 1958]  # LIS 长度

# 图 1: 运行时间 vs 数据规模
plt.figure(figsize=(12, 5))
plt.subplot(1, 2, 1)
plt.plot(scales, times, marker="o", color="blue", label="Execution Time (s)")
plt.title("Execution Time vs Dataset Scale")
plt.xlabel("Dataset Scale")
plt.ylabel("Time (s)")
plt.grid(True)
plt.legend()

# 图 2: LIS 长度 vs 数据规模
plt.subplot(1, 2, 2)
plt.plot(scales, lis_lengths, marker="o", color="green", label="LIS Length")
plt.title("Longest Increasing Subsequence vs Dataset Scale")
plt.xlabel("Dataset Scale")
plt.ylabel("LIS Length")
plt.grid(True)
plt.legend()

# 显示图表
plt.tight_layout()
plt.show()
