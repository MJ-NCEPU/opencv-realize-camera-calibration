import torch


torch.manual_seed(1)
a = torch.randint(1, 6, (10,), dtype=torch.long)
print(a)
