//===-- IOObject.cpp ------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "lldb/Utility/IOObject.h"

using namespace lldb_private;

const IOObject::WaitableHandle IOObject::kInvalidHandleValue = -1;
IOObject::~IOObject() = default;
