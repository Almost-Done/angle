//
// Copyright (c) 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Pack_Unpack_test.cpp:
//   Tests for the emulating pack_unpack functions for GLSL.
//

#include "angle_gl.h"
#include "gtest/gtest.h"
#include "GLSLANG/ShaderLang.h"
#include "tests/test_utils/compiler_test.h"

using namespace sh;

namespace
{

class PackUnpackTest : public MatchOutputCodeTest
{
  public:
    PackUnpackTest() : MatchOutputCodeTest(GL_FRAGMENT_SHADER, 0, SH_GLSL_400_CORE_OUTPUT) {}
};

// Check if PackSnorm2x16 Emulation for GLSL < 4.2 compile correctly.
TEST_F(PackUnpackTest, PackSnorm2x16Emulation)
{
    const std::string &shaderString =
        "#version 300 es\n"
        "precision mediump float;\n"
        "layout(location = 0) out mediump vec4 fragColor;"
        "void main() {\n"
        "   vec2 v;\n"
        "   uint u = packSnorm2x16(v);\n"
        "   fragColor = vec4(0.0);\n"
        "}\n";
    compile(shaderString);
    ASSERT_TRUE(foundInCode("uint packSnorm2x16_emu(vec2 v)"));
}

// Check if UnpackSnorm2x16 Emulation for GLSL < 4.2 compile correctly.
TEST_F(PackUnpackTest, UnpackSnorm2x16Emulation)
{
    const std::string &shaderString =
        "#version 300 es\n"
        "precision mediump float;\n"
        "layout(location = 0) out mediump vec4 fragColor;"
        "void main() {\n"
        "   uint u;\n"
        "   vec2 v=unpackSnorm2x16(u);\n"
        "   fragColor = vec4(0.0);\n"
        "}\n";
    compile(shaderString);
    ASSERT_TRUE(foundInCode("vec2 unpackSnorm2x16_emu(uint u)"));
}

// Check if PackUnorm2x16 Emulation for GLSL < 4.1 compiles correctly.
TEST_F(PackUnpackTest, PackUnorm2x16Emulation)
{
    const std::string &shaderString =
        "#version 300 es\n"
        "precision mediump float;\n"
        "layout(location = 0) out mediump vec4 fragColor;"
        "void main() {\n"
        "   vec2 v;\n"
        "   uint u = packUnorm2x16(v);\n"
        "   fragColor = vec4(0.0);\n"
        "}\n";
    compile(shaderString);
    ASSERT_TRUE(foundInCode("uint packUnorm2x16_emu(vec2 v)"));
}

// Check if UnpackSnorm2x16 Emulation for GLSL < 4.1 compiles correctly.
TEST_F(PackUnpackTest, UnpackUnorm2x16Emulation)
{
    const std::string &shaderString =
        "#version 300 es\n"
        "precision mediump float;\n"
        "layout(location = 0) out mediump vec4 fragColor;"
        "void main() {\n"
        "   uint u;\n"
        "   vec2 v=unpackUnorm2x16(u);\n"
        "   fragColor = vec4(0.0);\n"
        "}\n";
    compile(shaderString);
    ASSERT_TRUE(foundInCode("vec2 unpackUnorm2x16_emu(uint u)"));
}

// Check if PackHalf2x16 Emulation for GLSL < 4.2 compiles correctly.
TEST_F(PackUnpackTest, PackHalf2x16Emulation)
{
    const std::string &shaderString =
        "#version 300 es\n"
        "precision mediump float;\n"
        "layout(location = 0) out mediump vec4 fragColor;"
        "void main() {\n"
        "   vec2 v;\n"
        "   uint u=packHalf2x16(v);\n"
        "   fragColor = vec4(0.0);\n"
        "}\n";
    compile(shaderString);
    ASSERT_TRUE(foundInCode("uint packHalf2x16_emu(vec2 v)"));
}

// Check if UnpackHalf2x16 Emulation for GLSL < 4.2 compiles correctly.
TEST_F(PackUnpackTest, UnpackHalf2x16Emulation)
{
    const std::string &shaderString =
        "#version 300 es\n"
        "precision mediump float;\n"
        "layout(location = 0) out mediump vec4 fragColor;"
        "void main() {\n"
        "   uint u;\n"
        "   vec2 v=unpackHalf2x16(u);\n"
        "   fragColor = vec4(0.0);\n"
        "}\n";
    compile(shaderString);
    ASSERT_TRUE(foundInCode("vec2 unpackHalf2x16_emu(uint u)"));
}

} // namespace
