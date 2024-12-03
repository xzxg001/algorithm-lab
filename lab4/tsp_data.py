import random

def generate_tsp_data_with_return_to_file(n, m, filename="tsp_data.txt"):
    edges = set()
    while len(edges) < m:
        a = random.randint(1, n)
        b = random.randint(1, n)
        if a != b:
            w = random.randint(1, 100)
            edge = (a, b, w) if a < b else (b, a, w)
            edges.add(edge)
    # 保存到文件
    with open(filename, "w") as file:
        file.write(f"{n} {m}\n")
        for edge in edges:
            file.write(f"{edge[0]} {edge[1]} {edge[2]}\n")

    print(f"TSP 数据已保存到 {filename}")

# 示例：生成 5 个城市，10 条边的 TSP 数据并保存到 tsp_data.txt
generate_tsp_data_with_return_to_file(20, 40, "./lab4/tsp_data.txt")