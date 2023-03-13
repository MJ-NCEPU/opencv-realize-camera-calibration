a = [1, 2, 3, 4]
b = [5, 6, 7]
c = {"a": 3, "b": 4}
d = {"ab": 3, "bc": 4}
print(dict(list(c.items()) +list(d.items())))
print((c, d))
