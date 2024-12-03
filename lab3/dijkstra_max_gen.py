import random

def generate_fixed_graph_data(filename):
    """
    生成指定规模的图数据到文件中。
    数据规模分别为：1, 10, 100, 1000, 10000, 100000, 1000000
    """
    sizes = [1, 10, 100, 1000, 10000, 100000, 1000000]
    with open(filename, 'w') as f:
        for n in sizes:
            m = min(n * 10, n * (n - 1) // 2)  # 控制边的数量不过大
            st = random.randint(1, n)         # 随机起点
            f.write(f"{n} {m} {st}\n")
            edges = set()
            for _ in range(m):
                while True:
                    u, v = random.sample(range(1, n + 1), 2)
                    if u != v:
                        break
                w = random.randint(1, 1000)
                edges.add((u, v, w))
            for u, v, w in edges:
                f.write(f"{u} {v} {w}\n")

generate_fixed_graph_data('test_data_3.1.txt')
