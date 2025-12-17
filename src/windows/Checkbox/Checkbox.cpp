// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "Checkbox.h"

using namespace winrt;
using namespace winrt::Microsoft::ReactNative;

namespace winrt::Checkbox::implementation {

void CheckboxModule::Initialize(ReactContext const &reactContext) noexcept {
  m_reactContext = reactContext;
}

void CheckboxModule::multiply(double a, double b, ReactPromise<double> promise) noexcept {
  promise.Resolve(a * b);
}

void RegisterCheckboxNativeModule(IReactPackageBuilder const &packageBuilder) noexcept {
  AddAttributedModules(packageBuilder, true);
}

} // namespace winrt::Checkbox::implementation
