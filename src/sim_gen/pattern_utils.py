from collections import OrderedDict
from typing import List, Tuple, Optional

class BitInfo(object):

    char: str
    count: int
    pos: List[Tuple[int,int]]

    def __init__(self, char):
        self.char = char
        self.count = 0
        self.pos = []

    def start(self, pos:int):
        self.count += 1
        self.pos.append((pos, pos),)

    def cont(self, pos):
        self.count += 1
        x,y = self.pos[-1]
        self.pos[-1] = (x,y+1)

class BitsInfo(object):
    d:BitInfo
    r:BitInfo
    k:BitInfo
    K:BitInfo
    A:BitInfo
    q:BitInfo
    s:BitInfo

    CHARS = ["d", "r", "k", "K", "A", "q", "s", "b", "m", "f"]

    def __init__(self):
        self.__dict__ = OrderedDict()

    def start(self, ch, pos):
        if ch in self.CHARS:
            self.__dict__[ch] = self.__dict__.get(ch, BitInfo(ch))
            self.__dict__[ch].start(pos)

    def cont(self, ch, pos):
        if ch in self.CHARS:
            self.__dict__[ch] = self.__dict__.get(ch, BitInfo(ch))
            self.__dict__[ch].cont(pos)

    def get(self, ch):
        return self.__dict__.get(ch, BitInfo(ch))

    def get_items(self)->Tuple[str,BitInfo]:
        return [
            (x, self.__dict__[x]) for x in self.CHARS
            if x in self.__dict__.keys()]

class BitRangeExpr(object):

    HEX = {
        0 : "0",
        1 : "1",
        2 : "3",
        3 : "7",
        4 : "F"
    }

    def __init__(self, curr: int, size:int, start:int, width:int):
        self.curr = curr
        self.size = size
        self.start = start
        self.width = width

    def get_mask(self, width:int, curr:int, size:int)->str:
        bstr: str = "1"*(width) + "0"*(size-curr)
        hstr: str = hex(int(bstr, 2))
        return hstr

    def gen(self, var: str)->str:
        shift: int = self.curr - self.start - self.width
        wstr: str = self.get_mask(
            self.width, self.curr, self.size)
        mask = var
        mask = "(%s >> %d)" % (mask, shift) if shift > 0 else mask
        mask = "( %s & %s )" % (mask, wstr) if self.width > 0 else mask
        return mask


class BitRangesExpr(object):

    @classmethod
    def gen(cls, var: str, size: int, ranges: List[Tuple[int,int]]):
        ret : str = ""
        exprs: List[str] = []
        curr: int = size
        for start, end in ranges[::-1]:
            width: int = end - start + 1
            expr: str = BitRangeExpr(curr, size, start, width).gen(var)
            exprs.append(expr)
            curr -= width
        return "( %s )" % " | ".join(exprs)


class Pattern:

    @classmethod
    def remove_spaces(cls, pattern: str):
        return pattern.replace("-", "")

    @classmethod
    def get_bit_counts(cls, pattern: str)->BitsInfo:
        pattern = pattern.replace("-", "")

        bitInfo : BitsInfo = BitsInfo()
        prev : Optional[str] = None
        for i,ch in enumerate(pattern):
            if ch != prev:
                bitInfo.start(ch,i)
            else:
                bitInfo.cont(ch,i)
            prev = ch
        return bitInfo
