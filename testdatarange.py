# data_range = [r.split('-') for r in '1-3450/801-810'.split('/')]
# print(data_range)
from torchsummary import summary
import torch

a = torch.randn((2,1))
print(a)
softmax1 = torch.nn.Softmax(dim=1)
softmax2 = torch.nn.Softmax(dim=0)
b1 = softmax1(a)
b2 = softmax2(a)
print(b1)
print(b2)