// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2023 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "pass_level2.h"

namespace pnnx {

class torch_stft : public GraphRewriterPass
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
10 9
pnnx.Input              input_0     0 1 input
pnnx.Input              input_1     0 1 n_fft
pnnx.Input              input_2     0 1 hop_length
pnnx.Input              input_3     0 1 win_length
pnnx.Input              input_4     0 1 window
pnnx.Input              input_5     0 1 normalized
pnnx.Input              input_6     0 1 onesided
pnnx.Input              input_7     0 1 return_complex
aten::stft              op_0        8 1 input n_fft hop_length win_length window normalized onesided return_complex out
pnnx.Output             output      1 0 out
)PNNXIR";
    }

    const char* type_str() const
    {
        return "torch.stft";
    }

    void write(Operator* op, const std::map<std::string, Parameter>& /*captured_params*/) const
    {
        op->params["pad_mode"] = "reflect";
        op->params["center"] = false;
    }
};

REGISTER_GLOBAL_PNNX_GRAPH_REWRITER_PASS(torch_stft, 20)

class torch_stft_1 : public GraphRewriterPass
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
36 35
pnnx.Input              input_0     0 1 input
pnnx.Input              input_1     0 1 n_fft
pnnx.Input              input_2     0 1 hop_length
pnnx.Input              input_3     0 1 win_length
pnnx.Input              input_4     0 1 window
pnnx.Input              input_5     0 1 normalized
pnnx.Input              input_6     0 1 onesided
pnnx.Input              input_7     0 1 return_complex
prim::Constant          op_0        0 1 4 value=0
aten::size              op_1        2 1 input 4 5
prim::NumToTensor       op_2        1 1 5 6
aten::Int               op_3        1 1 6 9
prim::Constant          op_4        0 1 11 value=1
aten::size              op_5        2 1 input 11 12
prim::NumToTensor       op_6        1 1 12 13
aten::Int               op_7        1 1 13 18
prim::Constant          op_8        0 1 62 value=1
prim::ListConstruct     op_9        3 1 62 9 18 19
aten::view              op_10       2 1 input 19 a
prim::Constant          op_11       0 1 21 value=%pad_left
prim::Constant          op_12       0 1 63 value=%pad_right
prim::ListConstruct     op_13       2 1 21 63 22
prim::Constant          op_14       0 1 23 value=%pad_mode
F.pad                   op_15       3 1 a 22 23 b
prim::Constant          op_16       0 1 64 value=1
aten::size              op_17       2 1 b 64 27
prim::NumToTensor       op_18       1 1 27 28
aten::Int               op_29       1 1 28 31
prim::Constant          op_20       0 1 33 value=2
aten::size              op_21       2 1 b 33 34
prim::NumToTensor       op_22       1 1 34 35
aten::Int               op_23       1 1 35 40
prim::ListConstruct     op_24       2 1 31 40 41
aten::view              op_25       2 1 b 41 c
aten::stft              op_26       8 1 c n_fft hop_length win_length window normalized onesided return_complex out
pnnx.Output             output      1 0 out
)PNNXIR";
    }

    const char* type_str() const
    {
        return "torch.stft";
    }

    void write(Operator* op, const std::map<std::string, Parameter>& captured_params) const
    {
        op->params["pad_mode"] = captured_params.at("pad_mode");
        op->params["center"] = true;
    }
};

REGISTER_GLOBAL_PNNX_GRAPH_REWRITER_PASS(torch_stft_1, 19)

class torch_stft_2 : public torch_stft_1
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
29 28
pnnx.Input              input_0     0 1 input
pnnx.Input              input_1     0 1 n_fft
pnnx.Input              input_2     0 1 hop_length
pnnx.Input              input_3     0 1 win_length
pnnx.Input              input_4     0 1 window
pnnx.Input              input_5     0 1 normalized
pnnx.Input              input_6     0 1 onesided
pnnx.Input              input_7     0 1 return_complex
prim::Constant          op_0        0 1 11 value=0
aten::size              op_1        2 1 input 11 12
prim::NumToTensor       op_2        1 1 12 13
aten::Int               op_3        1 1 13 18
prim::Constant          op_4        0 1 15 value=1
prim::Constant          op_5        0 1 121 value=1
prim::ListConstruct     op_6        3 1 15 121 18 19
aten::view              op_7        2 1 input 19 a
prim::Constant          op_8        0 1 22 value=%pad_left
prim::Constant          op_9        0 1 122 value=%pad_right
prim::ListConstruct     op_10       2 1 22 122 23
prim::Constant          op_11       0 1 24 value=%pad_mode
F.pad                   op_12       3 1 a 23 24 b
prim::Constant          op_13       0 1 28 value=2
aten::size              op_14       2 1 b 28 29
prim::NumToTensor       op_15       1 1 29 30
aten::Int               op_16       1 1 30 34
prim::ListConstruct     op_17       1 1 34 35
aten::view              op_18       2 1 b 35 c
aten::stft              op_19       8 1 c n_fft hop_length win_length window normalized onesided return_complex out
pnnx.Output             output      1 0 out
)PNNXIR";
    }
};

REGISTER_GLOBAL_PNNX_GRAPH_REWRITER_PASS(torch_stft_2, 19)

class torch_stft_3 : public torch_stft_1
{
public:
    const char* match_pattern_graph() const
    {
        return R"PNNXIR(7767517
29 28
pnnx.Input              input_0     0 1 input
pnnx.Input              input_1     0 1 n_fft
pnnx.Input              input_2     0 1 hop_length
pnnx.Input              input_3     0 1 win_length
pnnx.Input              input_4     0 1 window
pnnx.Input              input_5     0 1 normalized
pnnx.Input              input_6     0 1 onesided
pnnx.Input              input_7     0 1 return_complex
prim::Constant          op_0        0 1 11 value=0
aten::size              op_1        2 1 input 11 12
prim::NumToTensor       op_2        1 1 12 13
aten::Int               op_3        1 1 13 18
prim::Constant          op_4        0 1 15 value=1
prim::Constant          op_5        0 1 121 value=1
prim::ListConstruct     op_6        3 1 15 121 18 19
aten::view              op_7        2 1 input 19 a
prim::Constant          op_8        0 1 22 value=%pad_left
prim::Constant          op_9        0 1 122 value=%pad_right
prim::ListConstruct     op_10       2 1 22 122 23
prim::Constant          op_11       0 1 24 value=None
F.pad                   op_12       3 1 a 23 24 b mode=%pad_mode
prim::Constant          op_13       0 1 28 value=2
aten::size              op_14       2 1 b 28 29
prim::NumToTensor       op_15       1 1 29 30
aten::Int               op_16       1 1 30 34
prim::ListConstruct     op_17       1 1 34 35
aten::view              op_18       2 1 b 35 c
aten::stft              op_19       8 1 c n_fft hop_length win_length window normalized onesided return_complex out
pnnx.Output             output      1 0 out
)PNNXIR";
    }
};

REGISTER_GLOBAL_PNNX_GRAPH_REWRITER_PASS(torch_stft_3, 19)

} // namespace pnnx
