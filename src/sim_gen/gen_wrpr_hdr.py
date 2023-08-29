from typing import Dict

from gen_common import (
    HeaderFile,
    read_json_file,
    camel_case, FuncSpec
)

class WrapperHdrFile(HeaderFile):

    @classmethod
    def gen_func_from_spec(cls, func_name: str, func_spec: FuncSpec):
        instrn_defn: str = (
            "LongInstrn" if func_spec.is_long_instrn() else "ShortInstrn")
        print("\tvoid %s(Environment& env, ShortInstrn instrn);" % func_name)

    @classmethod
    def gen_struct(cls, module_name: str, spec_json: Dict[str,Dict]):
        print("class %s {" % camel_case(module_name))
        for (func_name, func_spec) in spec_json.items():
            cls.gen_func_from_spec(func_name, FuncSpec(func_spec))
            cls.gen_newline()
        print("};")

    @classmethod
    def gen_file_body(cls, module_name: str, spec_json: Dict[str,Dict]):
        cls.gen_file_header(module_name)
        cls.gen_newline()
        cls.gen_struct(module_name, spec_json)
        cls.gen_newline()
        cls.gen_file_trailer(module_name)

    @classmethod
    def gen_file(cls, module_name: str, module_file: str):
        spec_json: Dict[str,Dict[str,str]] = read_json_file(module_file)
        cls.gen_file_body(module_name, spec_json)

if __name__ == "__main__":
    WrapperHdrFile.gen_file("alu_ops", "info_alu_ops.json")
