import json
import os.path
from typing import List, Dict, IO, Tuple, Optional

from pattern import Pattern, ArgBitInfo

class SpecCommon(object):

    @classmethod
    def read_json_file(cls, module_file:str):
        data: str
        with open(module_file, "r") as fp:
            data = fp.read()
        obj = json.loads(data)
        return obj

    @classmethod
    def mod_name(cls, spec_file: str):
        return os.path.splitext(os.path.basename(spec_file))[0]


class FuncSpec(object):
    T: str
    P: str
    man_dcd: bool # manual decode
    mod_name: str
    pattern: Pattern

    def __init__(self, func_spec: Dict[str, str], mod_name: str=None):
        self.T = func_spec["T"]
        self.P = func_spec["P"]
        self.man_dcd = (func_spec.get("D", "auto") == "manual")
        self.pattern = Pattern(self.P)
        self.mod_name = mod_name

    def is_long_instrn(self)->bool:
        return self.pattern.instrn_size() > 16



class AnyFile(object):

    out_fp: IO

    def fprintln(self, str_=""):
        print(str_, file=self.out_fp)

    def fprint(self, str_=""):
        print(str_, file=self.out_fp, end='')

    def blankline(self):
        self.fprintln("")

    def open_writer(self, out_file:str):
        self.out_fp = open(out_file, "w")

    def close_writer(self):
        self.out_fp.close()



class CLangFile(AnyFile):

    def write_include_files(self, includes: List[str]):
        include: str
        for include in includes:
            self.fprintln('#include "%s"' % include)
        self.blankline()


class HeaderFile(CLangFile):

    def write_file_header(self, module_name: str):
        macro_name: str = "%s_H" % module_name.upper()
        self.fprintln("#ifndef %s" % macro_name)
        self.fprintln("#define %s" % macro_name)

    def write_file_trailer(self, module_name: str):
        macro_name: str = "%s_H" % module_name.upper()
        line:str = "#endif // %s" % (macro_name)
        self.fprintln(line)

    def write_class_prefix(self, class_name: str):
        self.fprintln("class %s {" % class_name)
        self.fprintln("public:")
        self.blankline()

    def write_enum_prefix(self, enum_name: str):
        self.fprintln("enum %s {" % enum_name)
        self.blankline()

    def write_class_suffix(self):
        self.fprintln("};")

    def write_enum_suffix(self):
        self.fprintln("};")

    def write_func_header(
            self, ret_type: str, func_name: str,
            args: List[Tuple[str,str]],
            indent:int=0, static:bool=False
    ):
        args_str: str = ", ".join([f"{type_} {name}" for (type_, name) in args])
        static_pfx: str = "static" if static else ""
        self.fprintln(" ".join(
            ["\t"*(indent), static_pfx, f"{ret_type} {func_name}({args_str});"]))


class CppFile(CLangFile):

    def write_func_body_hdr(self,
                            ret_type: str, class_name: str, func_name: str, args: List[Tuple[str,str]]):

        args_str: str = ", ".join(["%s %s" % (type_, name) for (type_, name) in args])
        func_desc = "%s::%s"%(class_name, func_name) if len(class_name) else func_name
        func_header: str = "%s %s(%s) {" % (ret_type, func_desc, args_str)
        self.fprintln(func_header)

    def write_switch_func(self, switch_expr: str, cases: List[Tuple[str, str]],
                          ret_flag: bool, def_ret_flag: bool, def_val: Optional[str]):

        self.fprintln("\tswitch(%s) {" % switch_expr)
        for check_val, ret_val in cases:
            if ret_flag:
                self.fprintln("\t\tcase %s: return %s;" % (check_val, ret_val))
            else:
                self.fprintln("\t\tcase %s: %s; break;" % (check_val, ret_val))

        if def_ret_flag:
            self.fprintln("\t\tdefault: break;")
        else:
            self.fprintln("\t\tdefault: return %s;" % def_val)

        self.fprintln("\t};")


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
    def gen_func_arg(cls, fld_type: str, fld_width: int):
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

    @classmethod
    def gen_func_args(cls, pattern: Pattern):
        args: List[Tuple[str,str]] = []
        arg_bit_info: ArgBitInfo

        for ch, arg_bit_info in pattern.get_arg_bits_info().get_items():
            fld_type, fld_name = WrapperCommon.gen_func_arg(ch, arg_bit_info.count)
            args.append((fld_type, fld_name),)
        return args
