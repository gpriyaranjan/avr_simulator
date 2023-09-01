import json
from typing import List, Dict, IO

from pattern_utils import Pattern


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

    out_fp: IO

    def fprint(self, str_):
        print(str_, file=self.out_fp)

    def gen_newline(self):
        self.fprint("")

    def open_writer(self, out_file:str):
        self.out_fp = open(out_file, "w")

    def close_writer(self):
        self.out_fp.close()

    pass

class HeaderFile(AnyFile):

    def gen_file_header(self, module_name: str):
        macro_name: str = "%s_H" % module_name.upper()
        self.fprint("#ifndef %s" % macro_name)
        self.fprint("#define %s" % macro_name)

    def gen_file_trailer(self, module_name: str):
        macro_name: str = "%s_H" % module_name.upper()
        line:str = "#endif // %s" % (macro_name)
        self.fprint(line)

    def gen_class_prefix(self, class_name: str):
        self.fprint("class %s {" % class_name)
        self.fprint("public:")
        self.gen_newline()

    def gen_enum_prefix(self, enum_name: str):
        self.fprint("enum %s {" % enum_name)
        self.gen_newline()

    def gen_class_suffix(self):
        self.fprint("};")

    def gen_enum_suffix(self):
        self.fprint("};")

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
        "b" : "bitNum",
        "f" : "flag",
        "m" : "mode"
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
        # 10 : "TenBits",
        12 : "TwelveBit",
        16 : "SixteenBit",
        22 : "TwentyTwoBit"
    }

    @classmethod
    def gen(cls, fld_type: str, fld_width: int):
        if fld_width == 10 and fld_type == "d":
            arg_type: str = "FiveBit"
        else:
            try:
                arg_type: str = WrapperCommon.ArgTypes[fld_width]
            except Exception as ex:
                print("Fld width is %d" % fld_width)
                raise ex
        arg_name: str = WrapperCommon.ArgNames[fld_type]
        return (arg_type, arg_name)
