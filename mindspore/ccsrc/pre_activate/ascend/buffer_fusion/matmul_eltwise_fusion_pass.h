/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MINDSPORE_CCSRC_PRE_ACTIVATE_ASCEND_BUFFER_FUSION_PASS_MATMUL_ELTWISE_FUSION_PASS_H_
#define MINDSPORE_CCSRC_PRE_ACTIVATE_ASCEND_BUFFER_FUSION_PASS_MATMUL_ELTWISE_FUSION_PASS_H_

#include <unordered_set>
#include <vector>

#include "pre_activate/ascend/buffer_fusion/fusion_base_pass.h"
#include "ir/anf.h"
#include "pre_activate/common/pass.h"
#include "pre_activate/common/fusion_id_allocator.h"
#include "device/kernel_info.h"
#include "kernel/kernel.h"
#include "session/kernel_graph.h"

namespace mindspore {
namespace opt {
using FusedNodeRecord = std::vector<std::unordered_set<AnfNodePtr>>;

class MatmulEltwiseFusionPass : public FusionBasePass {
 public:
  explicit MatmulEltwiseFusionPass(FusionIdAllocatorPtr idAllocator)
      : FusionBasePass("MatmulEltwiseFusionPass", idAllocator) {}
  ~MatmulEltwiseFusionPass() override = default;
  void MatchSingleFusionPattern(const session::KernelGraph &kernel_graph, FusedNodeRecord *candidate_fusion) override;

 private:
  void MatchMatmulEltwise(const CNodePtr &cnode, const AnfNodePtr &relu_input, const session::KernelGraph &kernel_graph,
                          FusedNodeRecord *candidate_fusion);
};
}  // namespace opt
}  // namespace mindspore

#endif  // MINDSPORE_CCSRC_PRE_ACTIVATE_ASCEND_BUFFER_FUSION_PASS_MATMUL_ELTWISE_FUSION_PASS_H_
