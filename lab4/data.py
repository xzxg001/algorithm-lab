import random
import string

def generate_data_with_signs(n, filename):
    # 随机生成长度不超过 8 的字符串
    def random_string():
        length = random.randint(1, 8)  # 字符串长度在 1 到 8 之间
        return ''.join(random.choices(string.ascii_uppercase, k=length))

    # 生成数据
    data = [f"{n}"]  # 第一行是数据规模
    for _ in range(n):
        string_part = random_string()
        sign = random.choice(["+", "-"])
        data.append(f"{string_part} {sign}")

    # 保存到文件
    with open(filename, "w") as file:
        file.write("\n".join(data))
    
    print(f"数据已保存到 {filename}")

# 示例：生成 5 行数据并保存到 data.txt
generate_data_with_signs(10, "./data.txt")
