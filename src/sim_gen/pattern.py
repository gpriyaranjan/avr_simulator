from collections import OrderedDict
from pprint import pformat
from typing import Dict, List, Tuple, Optional

INSTRN_SIZE = 16

def extract_prefix(pattern:str)->str:
    prefix: str = ""
    for ch in pattern:
        if ch not in ['0','1']: break
        prefix = prefix + ch
    return prefix

Hex = str

class ArgBitInfo(object):

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


class ArgBitsInfo(object):
    d:ArgBitInfo
    r:ArgBitInfo
    k:ArgBitInfo
    K:ArgBitInfo
    A:ArgBitInfo
    q:ArgBitInfo
    s:ArgBitInfo

    CHARS = ["d", "r", "k", "K", "A", "q", "s", "b", "m", "f"]

    def __init__(self):
        self.__dict__ = OrderedDict()

    def start(self, ch, pos):
        if ch in self.CHARS:
            self.__dict__[ch] = self.__dict__.get(ch, ArgBitInfo(ch))
            self.__dict__[ch].start(pos)

    def cont(self, ch, pos):
        if ch in self.CHARS:
            self.__dict__[ch] = self.__dict__.get(ch, ArgBitInfo(ch))
            self.__dict__[ch].cont(pos)

    def get(self, ch):
        return self.__dict__.get(ch, ArgBitInfo(ch))

    def get_items(self)->Tuple[str,ArgBitInfo]:
        return [
            (x, self.__dict__[x]) for x in self.CHARS
            if x in self.__dict__.keys()]


class ArgBitRangeExpr(object):

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

    def get_mask(self)->str:
        bstr: str = "1"*(self.width) + "0"*(self.size - self.curr)
        hstr: str = hex(int(bstr, 2))
        return hstr

    def gen_extraction_expr(self, var: str)->str:
        shift: int = self.curr - self.start - self.width
        wstr: str = self.get_mask()
        expr:str = var
        expr = "(%s >> %d)" % (expr, shift) if shift > 0 else expr
        expr = "( %s & %s )" % (expr, wstr) if self.width > 0 else expr
        return expr


class ArgBitRangesExpr(object):

    @classmethod
    def gen(cls, var: str, size: int, ranges: List[Tuple[int,int]]):
        ret : str = ""
        exprs: List[str] = []
        curr: int = size
        for start, end in ranges[::-1]:
            width: int = end - start + 1
            expr: str = ArgBitRangeExpr(curr, size, start, width).gen_extraction_expr(var)
            exprs.append(expr)
            curr -= width
        return "( %s )" % " | ".join(exprs)


class Pattern(object):

    readable: str
    pattern: str

    prefix: str
    pfx_hex: str
    pfx_msk: str
    pfx_len: int

    def __init__(self, pattern:str):
        self.readable = pattern
        self.pattern = self.readable.replace("-", "")

        self.prefix = extract_prefix(self.pattern)
        self.set_prefix_flags()

    def set_prefix_flags(self):

        self.pfx_len = len(self.prefix)

        pfx_len: int = len(self.prefix)
        pfx_bin: str = self.prefix + "0"*(INSTRN_SIZE-pfx_len)
        self.pfx_hex = hex(int(pfx_bin,2))
        msk_bin: str = "1"*pfx_len + "0"*(INSTRN_SIZE-pfx_len)
        self.pfx_msk = hex(int(msk_bin,2))

    def get_bit_counts(self)->ArgBitsInfo:

        bitInfo : ArgBitsInfo = ArgBitsInfo()
        prev : Optional[str] = None
        for i,ch in enumerate(self.pattern):
            if ch != prev:
                bitInfo.start(ch,i)
            else:
                bitInfo.cont(ch,i)
            prev = ch
        return bitInfo

    def __repr__(self):
        return ("PL(%s),P(%s),PH(%s),PM(%s)" %
                (self.pfx_len, self.prefix, self.pfx_hex, self.pfx_msk))


class Prefixes(object):
    len: int
    mask: str
    instrns: Dict[Hex,str]

    def __init__(self, len:int, mask:str):
        self.len = len
        self.mask = mask
        self.instrns = {}

    def set(self, hex:Hex, instrn:str):
        self.instrns[hex] = instrn

    def __repr__(self):
        instrns = ["<%s,%s>" % (mask, instrn)
                   for (mask, instrn) in self.instrns.items()]
        instrns = sorted(instrns)
        return "(%s)" % (",".join(instrns))


class PrefixTable(object):
    by_len: Dict[int, Prefixes]

    def __init__(self):
        self.by_len = {}

    def add_prefix(self, instrn:str, pattern: Pattern):
        len: int = pattern.pfx_len
        prefixes: Prefixes = self.by_len.get(len, Prefixes(len, pattern.pfx_msk))
        prefixes.set(pattern.pfx_hex, instrn)
        self.by_len[len] = prefixes

    def __repr__(self):
        return pformat(self.by_len)
