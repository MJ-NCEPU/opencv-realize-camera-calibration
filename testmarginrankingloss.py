import torch.nn as nn
import torch

loss = nn.MarginRankingLoss()
input1 = torch.randint(1, 20, (3,))
print(input1)
input2 = torch.randint(1, 20, (3,))
print(input2)
target = torch.randn(3).sign()
print(target)
output = loss(input1, input2, target)
print(output)
