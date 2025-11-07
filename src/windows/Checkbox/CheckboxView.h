// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "CheckboxView.g.h"
#include "winrt/Microsoft.ReactNative.h"

namespace winrt::Checkbox::implementation {
    
    class CheckboxView : public CheckboxViewT<CheckboxView> {
    public:
        CheckboxView(Microsoft::ReactNative::IReactContext const& reactContext);
        void UpdateProperties(Microsoft::ReactNative::IJSValueReader const& reader);

    private:
        Microsoft::ReactNative::IReactContext m_reactContext{ nullptr };
    };
}

namespace winrt::Checkbox::factory_implementation {
    struct CheckboxView : CheckboxViewT<CheckboxView, implementation::CheckboxView> {};
}
