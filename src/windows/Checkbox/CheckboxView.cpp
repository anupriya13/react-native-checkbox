// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "CheckboxView.h"
#include "CheckboxView.g.cpp"

#include "NativeModules.h"
#include <UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.h>

namespace winrt::Checkbox::implementation {

    CheckboxView::CheckboxView(winrt::Microsoft::ReactNative::IReactContext const& reactContext) 
        : m_reactContext(reactContext) {
        // Initialize checkbox using XAML CheckBox control
        m_checkBox = winrt::Windows::UI::Xaml::Controls::CheckBox();
        
        // Set up event handlers
        m_checkBox.Checked([weak_this = get_weak()](auto const&, auto const&) {
            if (auto strong_this = weak_this.get()) {
                strong_this->OnValueChanged(true);
            }
        });
        
        m_checkBox.Unchecked([weak_this = get_weak()](auto const&, auto const&) {
            if (auto strong_this = weak_this.get()) {
                strong_this->OnValueChanged(false);
            }
        });
    }

    winrt::Windows::UI::Xaml::FrameworkElement CheckboxView::GetView() {
        return m_checkBox;
    }

    void CheckboxView::UpdateProperties(winrt::Microsoft::ReactNative::IJSValueReader const& reader) {
        auto const& propertyMap = winrt::Microsoft::ReactNative::JSValueObject::ReadFrom(reader);
        
        for (auto const& pair : propertyMap) {
            auto const& propertyName = pair.first;
            auto const& propertyValue = pair.second;
            
            if (propertyName == "value") {
                if (propertyValue.Type() == winrt::Microsoft::ReactNative::JSValueType::Boolean) {
                    m_checkBox.IsChecked(propertyValue.AsBoolean());
                }
            } else if (propertyName == "disabled") {
                if (propertyValue.Type() == winrt::Microsoft::ReactNative::JSValueType::Boolean) {
                    m_checkBox.IsEnabled(!propertyValue.AsBoolean());
                }
            }
        }
    }

    void CheckboxView::OnValueChanged(bool value) {
        if (m_reactContext) {
            // Create event data
            auto eventData = winrt::Microsoft::ReactNative::JSValueObject();
            eventData["target"] = m_tag;
            eventData["value"] = value;
            
            // Emit onChange event
            m_reactContext.DispatchEvent(
                m_checkBox,
                L"topChange",
                eventData);
        }
    }

    void CheckboxView::SetTag(int64_t tag) {
        m_tag = tag;
    }
}
