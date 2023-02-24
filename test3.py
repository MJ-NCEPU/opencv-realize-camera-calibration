import torch
import math
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.utils.checkpoint as checkpoint
from timm.models.layers import DropPath, to_2tuple, trunc_normal_

x = torch.randn(16,3,264,184)
x=x.flatten(2)
img_size = (126,134)
img_size = to_2tuple(img_size)
dpr = [x.item() for x in torch.linspace(0, 0.1, 24)]
print(dpr)
print(img_size)
print(x.size())