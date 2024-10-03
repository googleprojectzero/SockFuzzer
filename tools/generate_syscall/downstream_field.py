# Copyright 2024 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

class Field:
    name: str | None
    cast: str | None
    max_value: int | None

    def __init__(self, name=None, cast=None, max_value=None):
        assert name is not None
        self.name = name
        self.cast = cast
        self.max_value = max_value

    @property
    def command_field(self):
        # Helper for codegen.
        if self.max_value is not None:
            return f"(args.{self.name}() % {self.max_value})"
        return f"args.{self.name}()"

    def has_dependency(self):
        # Whether this field depends on another field.
        return False

    def as_caller_setup(self, syscall):
        # Inserted before wrapper call.
        return ""

    def as_caller_arg(self, syscall):
        # Inserted as argument in wrapper call.
        return self.command_field

    def as_caller_cleanup(self, syscall):
        # Inserted after wrapper call.
        return ""

    def as_value(self, syscall):
        # When the value is needed, and the caller_arg
        # might need a dereference.
        return self.as_caller_arg(syscall)

    def as_size_of(self, syscall):
        # Size of this field, if defined.
        return self.as_value(syscall)

    def as_proto_message_type(self, syscall):
        # Inserted into the syscall protobuf message.
        # Only include the type, like 'required uint64'.
        # The name and number are added automatically.
        # Empty string means to leave out of the protobuf.
        return ""


class Value(Field):
    # syscall value
    # a value, given by or deduced from protobuf
    proto_type: str | None
    c_type: str | None

    def __init__(self, proto_type=None, c_type=None, **kwargs):
        super().__init__(**kwargs)
        self.proto_type = proto_type
        self.c_type = c_type

    def as_caller_setup(self, syscall):
        return f"{self.c_type} {self.name} = {self.command_field};\n"

    def as_caller_arg(self, syscall):
        return self.name

    def as_proto_message_type(self, syscall):
        return f"required {self.proto_type}"


class Bool(Value):
    def __init__(self, **kwargs):
        super().__init__("bool", "int", **kwargs)


class UInt32(Value):
    def __init__(self, **kwargs):
        super().__init__("uint32", "unsigned int", **kwargs)


class Int32(Value):
    def __init__(self, **kwargs):
        super().__init__("int32", "int", **kwargs)

    def __repr__(self):
        return f"Int32({self.name})"


class UInt64(Value):
    def __init__(self, **kwargs):
        super().__init__("uint64", "unsigned long", **kwargs)


class Int64(Value):
    def __init__(self, **kwargs):
        super().__init__("int64", "long", **kwargs)


class Declared(Field):
    # uninitialized stack variable
    c_type: str | None

    def __init__(self, c_type=None, **kwargs):
        super().__init__(**kwargs)
        assert isinstance(c_type, str)
        self.c_type = c_type

    def __repr__(self):
        return f"Declared({self.name})"

    def as_caller_setup(self, syscall):
        return f"{self.c_type} {self.name};\n"

    def as_caller_arg(self, syscall):
        return self.name


class Ptr(Field):
    # prepend & to caller_arg
    # TODO(nwach): these kinds of types are annoying to write...
    field: Field

    def __init__(self, field=None, **kwargs):
        super().__init__(**kwargs)
        assert field is not None
        self.field = field
        self.max_value = self.field.max_value

    def as_caller_setup(self, syscall):
        return self.field.as_caller_setup(syscall)

    def as_caller_arg(self, syscall):
        return f"&({self.field.as_caller_arg(syscall)})"

    def as_caller_cleanup(self, syscall):
        return self.field.as_caller_cleanup(syscall)

    def as_value(self, syscall):
        return self.field.as_value(syscall)

    def as_size_of(self, syscall):
        return self.field.as_size_of(syscall)

    def as_proto_message_type(self, syscall):
        return self.field.as_proto_message_type(syscall)


class Retval(Ptr):
    def __init__(self, **kwargs):
        super().__init__(Declared(name=kwargs.get('name'), c_type='int'), **kwargs)


class CappedSize(UInt64):
    # provides the size of an empty array
    # anything with a max_value can be a buffer size
    # this is just a utility class
    def __init__(self, **kwargs):
        super().__init__(max_value=4096, **kwargs)


class EmptyArray(Field):
    size_given_by: str | None
    fixed_size: str | None
    c_type: str | None

    def __init__(self, size_given_by=None, fixed_size=None, c_type=None, **kwargs):
        super().__init__(**kwargs)
        self.size_given_by = size_given_by
        self.fixed_size = fixed_size
        self.c_type = c_type

    def has_dependency(self):
        # Size given by another field
        return self.size_given_by is not None

    def as_caller_arg(self, syscall):
        return f"{self.name}.data()"

    def as_caller_setup(self, syscall):
        if self.size_given_by is not None:
            size_field = syscall.field_by_name(self.size_given_by)
            if size_field.max_value is None:
                raise ValueError(
                    f"Must define max_value for size field '{size_field.name}' used by '{self.name}' in '{syscall.name}'"
                )
            size = size_field.as_value(syscall)
        elif self.fixed_size is not None:
            size = self.fixed_size
        else:
            raise ValueError(f"No way to size '{self.name}' in '{syscall.name}'")

        return f"std::vector<{self.c_type}> {self.name}({size});\n"


class EmptyBuffer(EmptyArray):
    # arrays of char are common enough to warrant own type
    def __init__(self, **kwargs):
        super().__init__(c_type="char", **kwargs)


class Array(Field):
    # of_type must be a Value, specifying c_type and proto_type
    # TODO(nwach): this isn't even close to working for more complicated types
    of_type: Value | None

    def __init__(self, of_type=None, **kwargs):
        super().__init__(**kwargs)
        assert False
        # self.of_type = self.parse_arg_as_type(of_type)

    def as_caller_setup(self, syscall):
        # a bit hacky...
        assert self.of_type is not None
        out = f"std::vector<{self.of_type.c_type}> {self.name};\n"
        out += f"for(auto c : {self.command_field})" + "{\n"
        out += f"  {self.name}.push_back(c);\n"
        out += "}\n"
        return out

    def as_caller_arg(self, syscall):
        assert self.name is not None
        return self.name + ".data()"

    def as_size_of(self, syscall):
        assert self.name is not None
        return self.name + ".size()"

    def as_proto_message_type(self, syscall):
        assert self.of_type is not None
        assert self.of_type.proto_type is not None
        return "repeated" + self.of_type.proto_type


class Buffer(Field):
    # a buffer is like an array, but much simpler cause proto bytes scalar
    def as_caller_arg(self, syscall):
        return "(user_addr_t) " + self.command_field + ".data()"

    def as_proto_message_type(self, syscall):
        return f"required bytes"

    def as_size_of(self, syscall):
        return self.command_field + ".size()"


class SizeOf(Field):
    # resolves to the size of an container (usually array)
    container: str | None

    def __init__(self, container=None, **kwargs):
        super().__init__(**kwargs)
        self.container = container

    def as_caller_arg(self, syscall):
        container = syscall.field_by_name(self.container)
        return container.as_size_of(syscall)


class Literal(Field):
    value: str | None

    def __init__(self, value=None, **kwargs):
        super().__init__(**kwargs)
        self.value = value

    def as_caller_arg(self, syscall):
        return self.value


class Nullptr(Literal):
    def __init__(self, **kwargs):
        super().__init__("(user_addr_t) nullptr", **kwargs)


class Enum(Value):
    # enum with given name should be defined somewhere...
    def __init__(self, proto_type=None, **kwargs):
        if 'c_type' in kwargs:
            raise ValueError("The 'c_type' argument is not supported in the Enum class. "
                             "Did you mean to use 'proto_type' instead?")
        kwargs['c_type'] = "int"
        super().__init__(proto_type=proto_type, **kwargs)


class Flags(Enum):
    c_type: str | None

    def __init__(self, proto_type=None, c_type='int', **kwargs):
        if proto_type is None:
            raise ValueError("The 'proto_type' argument is required in the Flags class.")
        if 'c_type' in kwargs:
            raise ValueError("The 'c_type' argument is not supported in the Flags class. "
                             "Did you mean to use 'proto_type' instead?")
        super().__init__(proto_type=proto_type, **kwargs)
        self.c_type = c_type

    def as_caller_setup(self, syscall):
        # enums are int32
        out = f"{self.c_type} {self.name} = 0;"
        out += f"for(auto f : {self.command_field}) " + "{\n"
        out += f"  {self.name} |= ({self.c_type}) f;\n"
        out += "}\n"
        return out

    def as_proto_message_type(self, syscall):
        assert self.proto_type is not None
        return "repeated " + self.proto_type

    def as_caller_arg(self, syscall):
        return self.name


class RandomStruct(Field):
    # A struct (or any c type), filled with up to sizeof(struct) fuzzed bytes
    struct: str | None

    def __init__(self, struct=None, **kwargs):
        super().__init__(**kwargs)
        self.struct = struct

    def as_proto_message_type(self, syscall):
        return "required bytes"

    def as_caller_setup(self, syscall):
        size = f"std::min({self.command_field}.size(), sizeof(struct {self.struct}))"
        out = f"struct {self.struct} {self.name};\n"
        out += f"memcpy(&{self.name}, {self.command_field}.data(), {size});\n"
        return out

    def as_caller_arg(self, syscall):
        assert self.name is not None
        return "&" + self.name


"""
CUSTOM TYPES
"""


class SockAddr(Field):
    # good example of custom type
    # uses already defined proto message
    # uses helper func get_sockaddr defined in bsd.h/cc
    def as_proto_message_type(self, syscall):
        return "required SockAddr "

    def as_caller_setup(self, syscall):
        return f"std::string {self.name} = get_sockaddr({self.command_field});\n"

    def as_caller_arg(self, syscall):
        return f"(caddr_t) {self.name}.data()"

    def as_size_of(self, syscall):
        return f"{self.name}.size()"


class RLimit(Field):
    # ok example of custom type
    # uses already defined proto message
    # manually sets up struct
    def as_proto_message_type(self, syscall):
        return "required RLimit "

    def as_caller_setup(self, syscall):
        out = f"struct rlimit {self.name} " + "{\n"
        out += f"  .rlim_cur = {self.command_field}.current(),\n"
        out += f"  .rlim_max = {self.command_field}.max(),\n"
        out += "};\n"
        return out

    def as_caller_arg(self, syscall):
        return f"&{self.name}"


class UUID(EmptyArray):
    def __init__(self, **kwargs):
        super().__init__(c_type="unsigned char", fixed_size=16, **kwargs)


class EmptySocketPair(EmptyArray):
    def __init__(self, **kwargs):
        super().__init__(c_type="int", fixed_size=2, **kwargs)


class EmptyPipeFds(EmptyArray):
    def __init__(self, **kwargs):
        super().__init__(c_type="int", fixed_size=2, **kwargs)


class Socklen(Value):
    def __init__(self, **kwargs):
        super().__init__(
            c_type="socklen_t", proto_type="uint32", max_value=4096, **kwargs
        )


class FileDescriptor(Enum):
    def __init__(self, **kwargs):
        super().__init__("FileDescriptor", **kwargs)


def all_subclasses(cls):
    return set(cls.__subclasses__()).union(
        [s for c in cls.__subclasses__() for s in all_subclasses(c)]
    )


FIELD_CLASSES = {cls.__name__: cls for cls in all_subclasses(Field)}
