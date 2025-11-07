// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "CheckboxView.g.h"
#include "winrt/Microsoft.ReactNative.h"
#include <winrt/Windows.UI.Xaml.Controls.h>

namespace winrt::Checkbox::implementation {
    
    class CheckboxView : public CheckboxViewT<CheckboxView> {
    public:
        CheckboxView(Microsoft::ReactNative::IReactContext const& reactContext);
        void UpdateProperties(Microsoft::ReactNative::IJSValueReader const& reader);
        winrt::Windows::UI::Xaml::FrameworkElement GetView();
        void SetTag(int64_t tag);

    private:
        void OnValueChanged(bool value);
        
        Microsoft::ReactNative::IReactContext m_reactContext{ nullptr };
        winrt::Windows::UI::Xaml::Controls::CheckBox m_checkBox{ nullptr };
        int64_t m_tag{ 0 };
    };
}

namespace winrt::Checkbox::factory_implementation {
    struct CheckboxView : CheckboxViewT<CheckboxView, implementation::CheckboxView> {};
}
