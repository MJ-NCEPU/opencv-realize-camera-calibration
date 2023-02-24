import torch
def look():
    return 3

print(torch.eye(3).view(3, 3, 1, 1))