import json
from typing import List, Dict

from src.sim_gen2.pattern_utils import Pattern


def read_json_file(module_file:str):
    data: str
    with open(module_file, "r") as fp:
        data = fp.read()
    obj = json.loads(data)
    return obj

class FuncSpec(object):
    T: str
    P: str

    def __init__(self, func_spec: Dict[str, str]):
        self.T = func_spec["T"]
        self.P = func_spec["P"]

    def is_long_instrn(self)->bool:
        return self.instrn_size() > 16

    def instrn_size(self)->int:
        pattern: str = self.P
        compact: str = Pattern.remove_spaces(pattern)
        return len(compact)


class AnyFile(object):

    @classmethod
    def gen_newline(cls):
        print()

    pass

class HeaderFile(AnyFile):

    @classmethod
    def gen_file_header(cls, module_name: str):
        macro_name: str = "%s_H" % module_name.upper()
        print("#include %s" % macro_name)
        print("#define %s" % macro_name)

    @classmethod
    def gen_file_trailer(cls, module_name: str):
        macro_name: str = "%s_H" % module_name.upper()
        print("#endif // %s" % macro_name)

def camel_case(word: str)->str:
    def caps_first_letter(word:str)->str:
        return word[0].upper() + word[1:]
    words: List[str] = word.split("_")
    return "".join(map(caps_first_letter, words))

class WrapperCommon:

    ArgNames : Dict[str,str] = {
        "d" : "tgtRegNum",
        "r" : "srcRegNum",
        "k" : "memOffset",
        "K" : "immData",
        "A" : "portAddr",
        "q" : "displacement",
        "s" : "statusRegNum",
        "b" : "bitNum"
    }

    ArgTypes : Dict[int, str] = {
        1 : "OneBit",
        2 : "TwoBit",
        3 : "ThreeBit",
        4 : "FourBit",
        5 : "FiveBit",
        6 : "SixBit",
        7 : "SevenBit",
        8 : "EightBit",
        # 10 : "TenBits"
    }

    @classmethod
    def gen(cls, fld_type: str, fld_width: int):
        if fld_width == 10 and fld_type == "d":
            arg_type: str = "FiveBit"
        else:
            arg_type: str = WrapperCommon.ArgTypes[fld_width]
        arg_name: str = WrapperCommon.ArgNames[fld_type]
        return (arg_type, arg_name)
