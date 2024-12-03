import random

def generate_knapsack_data_to_file(n, m, filename):
    """
    生成 0-1 背包问题的数据并保存到文件。

    :param n: 背包容量
    :param m: 物品数量
    :param filename: 保存数据的文件名
    """
    # 随机生成物品的重量和价值
    items = []
    for _ in range(m):
        w = random.randint(1, n)  # 重量在 1 到 n 之间
        v = random.randint(1, 100)  # 价值在 1 到 100 之间
        items.append((w, v))
    
    # 写入文件
    with open(filename, "w") as file:
        file.write(f"{n} {m}\n")
        for w, v in items:
            file.write(f"{w} {v}\n")
    
    print(f"数据已保存到文件：{filename}")

# 示例用法
n = 70  # 背包容量
m = 3   # 物品数量
filename = "knapsack_data.txt"  # 保存文件名

generate_knapsack_data_to_file(n, m, filename)
