import logging
from collections import OrderedDict
from dataclasses import dataclass
from pprint import pformat
from typing import Dict, List, Tuple, Optional

INSTRN_SIZE = 16

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

    def __repr__(self):
        pos_str: str = ",".join(["%d..%d" %(pos[0],pos[1]) for pos in self.pos])
        return "%s%d(%s)" % (self.char, self.count, pos_str)

class ArgBitsInfo(object):
    d:ArgBitInfo
    r:ArgBitInfo
    k:ArgBitInfo
    K:ArgBitInfo
    A:ArgBitInfo
    q:ArgBitInfo
    s:ArgBitInfo

    CHARS = ["d", "r", "k", "K", "A", "q", "s", "b", "m", "f"]

    def __init__(self, pattern: str):
        self.__dict__ = OrderedDict()
        self.init(pattern)

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

    def get_items(self)->List[Tuple[str,ArgBitInfo]]:
        return [
            (x, self.__dict__[x]) for x in self.CHARS
            if x in self.__dict__.keys()]

    def init(self, pattern: str):
        prev : Optional[str] = None
        for i,ch in enumerate(pattern):
            if ch != prev:
                self.start(ch,i)
            else:
                self.cont(ch,i)
            prev = ch

    def __repr__(self):
        return ", ".join(["%s" % repr(arg_bit_info)
                for arg_bit_info in self.__dict__.values()])

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

    def gen_insertion_expr(self, var: str)->str:
        shift: int = self.curr - self.start - self.width
        wstr: str = self.get_mask()
        expr:str = var
        expr = "( %s & %s )" % (expr, wstr) if self.width > 0 else expr
        expr = "( %s << %d )" % (expr, shift) if shift > 0 else expr
        return expr

class ArgBitRangesExpr(object):

    @classmethod
    def gen_extraction(cls, var: str, size: int, ranges: List[Tuple[int,int]]):
        ret : str = ""
        exprs: List[str] = []
        curr: int = size
        for start, end in ranges[::-1]:
            width: int = end - start + 1
            expr: str = ArgBitRangeExpr(curr, size, start, width).gen_extraction_expr(var)
            exprs.append(expr)
            curr -= width
        return "( %s )" % " | ".join(exprs)

    @classmethod
    def gen_insertion(cls, var: str, size: int, ranges: List[Tuple[int,int]]):
        ret : str = ""
        exprs: List[str] = []
        curr: int = size
        for start, end in ranges[::-1]:
            width: int = end - start + 1
            expr: str = ArgBitRangeExpr(curr, size, start, width).gen_insertion_expr(var)
            exprs.append(expr)
            curr -= width
        return "( %s )" % " | ".join(exprs)

@dataclass
class BitRange:
    hex: str
    mask: str
    len_: int
    off: int   # Offset from conventional start pos - left for prefix, right for suffix

class Pattern(object):

    readable: str
    compact: str

    prefix: str
    pfx_info: BitRange

    suffix: str
    sfx_info: BitRange

    instrn_info: BitRange

    arg_bits_info: ArgBitsInfo

    def __init__(self, pattern:str):
        self.readable = pattern
        self.compact = self.readable.replace("-", "")

        self.prefix = self.extract_prefix()
        self.set_prefix_flags()
        self.suffix, off = self.extract_suffix(INSTRN_SIZE)
        self.set_suffix_flags(off)

        self.set_instrn_flags()
        self.set_arg_bits_info()

    def set_instrn_flags(self):
        instrn_str: str = "".join([ch if ch in ["0", "1"] else "0"
                              for ch in self.compact])
        instrn_hex: str = hex(int(instrn_str, 2))
        instrn_mask: str = "".join(["1" if ch in ["0","1"] else "0"
                                    for ch in self.compact])
        instrn_mask_hex = hex(int(instrn_mask, 2))
        self.instrn_info = BitRange(instrn_hex, instrn_mask_hex, INSTRN_SIZE, 0)

    def extract_prefix(self)->str:
        prefix: str = ""
        for ch in self.compact:
            if ch not in ['0','1']: break
            prefix = prefix + ch
        return prefix

    def set_prefix_flags(self):

        pfx_len: int = len(self.prefix)
        pfx_bin: str = self.prefix + "0"*(INSTRN_SIZE-pfx_len)
        pfx_hex: str = hex(int(pfx_bin,2))
        msk_bin: str = "1"*pfx_len + "0"*(INSTRN_SIZE-pfx_len)
        msk_hex: str = hex(int(msk_bin,2))
        self.pfx_info = BitRange(pfx_hex, msk_hex, pfx_len, 0)

    def extract_suffix(self, upto:int)->Tuple[str,int]:
        suffix: str = ""
        rev_str = self.compact[upto:0:-1]

        off: int = 0
        while rev_str[off] not in ['0','1']:
            off = off + 1

        i: int = off
        while i < len(rev_str):
            ch = rev_str[i]
            if ch not in ['0','1']: break
            suffix = suffix + ch
            i = i + 1
        return suffix[::-1], off

    def set_suffix_flags(self, off):

        sfx_len: int = len(self.suffix)
        sfx_bin: str = "0"*(INSTRN_SIZE-sfx_len) + self.suffix + "0"*off
        sfx_hex: str = hex(int(sfx_bin,2))
        msk_bin: str = "0"*(INSTRN_SIZE-sfx_len) + "1"*sfx_len + "0"*off
        msk_hex: str = hex(int(msk_bin,2))
        self.sfx_info = BitRange(sfx_hex, msk_hex, sfx_len, off)

    def set_arg_bits_info(self):
        self.arg_bits_info = ArgBitsInfo(self.compact)

    def get_arg_bits_info(self)->ArgBitsInfo:
        return self.arg_bits_info

    def is_long_instrn(self)->bool:
        return self.instrn_size() > 16

    def instrn_size(self)->int:
        return len(self.compact)


class Prefixes(object):

    len: int
    mask: str
    instrns: Dict[Hex, Dict[str, BitRange]]

    def __init__(self, len:int, mask:str):
        self.len = len
        self.mask = mask
        self.instrns = {}

    def set(self, hex:Hex, instrn:str, sfx_info: BitRange):
        if not self.instrns.get(hex):
            self.instrns[hex] = {}
        else:
            logging.error("Conflict PM(%s) PH(%s) %s %s"
                          % (self.mask, hex, instrn, self.instrns.get(hex)))
        self.instrns[hex][instrn] = sfx_info

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
        len: int = pattern.pfx_info.len_
        prefixes: Prefixes = self.by_len.get(len, Prefixes(len, pattern.pfx_info.mask))
        prefixes.set(pattern.pfx_info.hex, instrn, pattern.sfx_info)
        self.by_len[len] = prefixes

    def __repr__(self):
        return pformat(self.by_len)

if __name__ == "__main__":
    pat_str: str = "1000-000d-dddd-ffmm"
    pat_obj: Pattern = Pattern(pat_str)
    print(f"{pat_obj.instrn_info.mask} {pat_obj.instrn_info.hex}")

