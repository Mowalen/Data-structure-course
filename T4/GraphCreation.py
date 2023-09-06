
#2023.4.24


import matplotlib.pyplot as plt

# 折线图
result1 = open("1.txt", )
result2 = open("2.txt", )

x = []
time1 = []
time2 = []
room1 = []
room2 = []
for i in range(0, 100):
    lines1 = result1.readline()
    lines2 = result2.readline()
    lines1 = lines1.split()
    lines2 = lines2.split()
    time1.append(float(lines1[2]))
    x.append(float(lines1[1]))
    time2.append(float(lines2[2]))
    room1.append(float(lines1[5]))
    room2.append(float(lines2[5]))

plt.plot(x, time1, 's-', color='r', markersize=3, label="dfs")  # 方形
plt.plot(x, time2, 'o-', color='g', markersize=3, label="enumerate")  # 圆形
plt.xlabel("number")  # 横坐标名字
plt.ylabel("rum time(us)")  # 纵坐标名字
plt.legend(loc="best")  # 图例
plt.show()

plt.plot(x, room1, 's-', color='r', markersize=3, label="dfs")  # 方形
plt.plot(x, room2, 'o-', color='g', markersize=3, label="enumerate")  # 圆形
plt.xlabel("number")  # 横坐标名字
plt.ylabel("space use(bytes)")  # 纵坐标名字
plt.legend(loc="best")  # 图例
plt.show()

result1.close()
result2.close()
