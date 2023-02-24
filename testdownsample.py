import torch
import torch.nn as nn


def conv_layer(in_channels, out_channels, kernel_size, stride=1, dilation=1, groups=1, bias=True):
    padding = int((kernel_size - 1) / 2) * dilation
    return nn.Conv2d(in_channels, out_channels, kernel_size, stride, padding=padding, bias=bias, dilation=dilation,
                     groups=groups)


# For any upscale factors
class TESTIMDN_AS(nn.Module):
    def __init__(self, in_nc=3, nf=64):
        super(TESTIMDN_AS, self).__init__()

        self.fea_conv = nn.Sequential(conv_layer(in_nc, nf, kernel_size=3, stride=2),
        nn.LeakyReLU(0.05),
        conv_layer(nf, nf, kernel_size=3, stride=2))

    def forward(self, input):
        out_fea = self.fea_conv(input)
        return out_fea


input1 = torch.ones(20, 3, 200, 200)
modle = TESTIMDN_AS()
out = modle(input1)
print(input1.size())
print(out.size())
