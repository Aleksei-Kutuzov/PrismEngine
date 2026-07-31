#pragma once
enum class StageType {
    VERTEX,
    TESSELLATION_CONTROL,
    TESSELLATION_EVALUATION,
    GEOMETRY,
    FRAGMENT,
    COMPUTE
};

enum class PrimitiveTopology {
    POINT_LIST,
    LINE_LIST,
    LINE_STRIP,
    TRIANGLE_LIST,
    TRIANGLE_STRIP,
    TRIANGLE_FAN,
    LINE_LIST_WITH_ADJACENCY,
    LINE_STRIP_WITH_ADJACENCY,
    TRIANGLE_LIST_WITH_ADJACENCY,
    TRIANGLE_STRIP_WITH_ADJACENCY,
    PATCH_LIST,
};

enum class PolygonMode {
    FILL,
    LINE,
    POINT,
};

enum class CullMode {
    NONE,
    FRONT,
    BACK,
    FRONT_AND_BACK,
};

enum class FrontFace {
    COUNTER_CLOCKWISE,
    CLOCKWISE
};

enum class SampleCount {
    S1, S2, S4, S8, S16, S32, S64
};

enum class CompareOp {
    NEVER,
    LESS,
    EQUAL,
    LESS_OR_EQUAL,
    GREATER,
    NOT_EQUAL,
    GREATER_OR_EQUAL,
    ALWAYS
};

enum class StencilOp {
    KEEP,
    ZERO,
    REPLACE,
    INCREMENT_AND_CLAMP,
    DECREMENT_AND_CLAMP,
    INVERT,
    INCREMENT_AND_WRAP,
    DECREMENT_AND_WRAP
};

enum class LogicOp {
    CLEAR,
    AND,
    AND_REVERSE,
    COPY,
    AND_INVERTED,
    NO_OP,
    XOR,
    OR,
    NOR,
    EQUIVALENT,
    INVERT,
    OR_REVERSE,
    COPY_INVERTED,
    OR_INVERTED,
    NAND,
    SET,
};

enum class BlendFactor {
    ZERO,
    ONE,
    SRC_COLOR,
    ONE_MINUS_SRC_COLOR,
    DST_COLOR,
    ONE_MINUS_DST_COLOR,
    SRC_ALPHA,
    ONE_MINUS_SRC_ALPHA,
    DST_ALPHA,
    ONE_MINUS_DST_ALPHA,
    CONSTANT_COLOR,
    ONE_MINUS_CONSTANT_COLOR,
    CONSTANT_ALPHA,
    ONE_MINUS_CONSTANT_ALPHA,
    SRC_ALPHA_SATURATE,
    SRC1_COLOR,
    ONE_MINUS_SRC1_COLOR,
    SRC1_ALPHA,
    ONE_MINUS_SRC1_ALPHA
};

enum class BlendOp {
    ADD,
    SUBTRACT,
    REVERSE_SUBTRACT,
    MIN,
    MAX
};

enum class ColorComponent {
    R = 0b0001,
    G = 0b0010,
    B = 0b0100,
    A = 0b1000
};