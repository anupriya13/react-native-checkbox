// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

#include "pch.h"
#include "CheckboxView.h"
#include <limits>

namespace winrt::Checkbox::implementation {

#ifdef RNW_NEW_ARCH

    RNCCheckboxComponentView::RNCCheckboxComponentView() {
        m_checkBox = winrt::Microsoft::UI::Xaml::Controls::CheckBox();
        
        // Subscribe to Checked/Unchecked events
        m_checkedToken = m_checkBox.Checked([weakThis = get_weak()](auto const& sender, auto const& e) {
            if (auto strongThis = weakThis.get()) {
                strongThis->OnCheckedChanged(sender, e);
            }
        });
        
        m_uncheckedToken = m_checkBox.Unchecked([weakThis = get_weak()](auto const& sender, auto const& e) {
            if (auto strongThis = weakThis.get()) {
                strongThis->OnCheckedChanged(sender, e);
            }
        });
    }

    RNCCheckboxComponentView::~RNCCheckboxComponentView() {
        if (m_checkBox) {
            m_checkBox.Checked(m_checkedToken);
            m_checkBox.Unchecked(m_uncheckedToken);
        }
    }

#endif // RNW_NEW_ARCH

    void RegisterCheckboxComponentView(
        winrt::Microsoft::ReactNative::IReactPackageBuilder const& packageBuilder) noexcept {
#ifdef RNW_NEW_ARCH
        CheckboxCodegen::RegisterCheckboxNativeComponent<winrt::Checkbox::implementation::RNCCheckboxComponentView>(
            packageBuilder,
            [](const winrt::Microsoft::ReactNative::Composition::IReactCompositionViewComponentBuilder& builder) {
                builder.as<winrt::Microsoft::ReactNative::IReactViewComponentBuilder>().XamlSupport(true);
                // Use SetContentIslandComponentViewInitializer
                builder.SetContentIslandComponentViewInitializer(
                    [](const winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView& islandView) noexcept {
                        auto userData = winrt::make_self<winrt::Checkbox::implementation::RNCCheckboxComponentView>();
                        userData->InitializeContentIsland(islandView);
                        islandView.UserData(*userData);
                    });
                // Set up initial state with zero size
                builder.as<winrt::Microsoft::ReactNative::IReactViewComponentBuilder>().SetInitialStateDataFactory(
                    [](const winrt::Microsoft::ReactNative::IComponentProps& /*props*/) noexcept {
                        return winrt::make<RNCCheckboxStateData>(winrt::Windows::Foundation::Size{ 0, 0 });
                    });

                // Register the measure function - reads from state
                builder.as<winrt::Microsoft::ReactNative::IReactViewComponentBuilder>().SetMeasureContentHandler(
                    [](winrt::Microsoft::ReactNative::ShadowNode const& shadowNode,
                        winrt::Microsoft::ReactNative::LayoutContext const&,
                        winrt::Microsoft::ReactNative::LayoutConstraints const&) noexcept {

                            auto currentState = winrt::get_self<RNCCheckboxStateData>(shadowNode.StateData());

                            if (currentState && currentState->desiredSize.Width > 0) {
                                // Return the measured size from state
                                return currentState->desiredSize;
                            }

                            // Return a default size if we don't have a measurement yet
                            return winrt::Windows::Foundation::Size{ 32, 32 };
                    });

                // Handle state updates
                builder.as<winrt::Microsoft::ReactNative::IReactViewComponentBuilder>().SetUpdateStateHandler(
                    [](const winrt::Microsoft::ReactNative::ComponentView& view,
                        const winrt::Microsoft::ReactNative::IComponentState& newState) {
                            auto islandView = view.as<winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView>();
                            auto userData = islandView.UserData().as<winrt::Checkbox::implementation::RNCCheckboxComponentView>();
                            userData->UpdateState(view, newState);
                    });
            });
#endif
    }

#ifdef RNW_NEW_ARCH
    void RNCCheckboxComponentView::InitializeContentIsland(
        const winrt::Microsoft::ReactNative::Composition::ContentIslandComponentView& islandView) {
        // Configure CheckBox
        m_checkBox.HorizontalAlignment(winrt::Microsoft::UI::Xaml::HorizontalAlignment::Left);
        m_checkBox.VerticalAlignment(winrt::Microsoft::UI::Xaml::VerticalAlignment::Center);

        // Listen for size changes on the checkbox
        m_checkBox.SizeChanged([this](auto const& /*sender*/, auto const& /*args*/) {
            RefreshSize();
        });

        m_island = winrt::Microsoft::UI::Xaml::XamlIsland{};
        m_island.Content(m_checkBox);
        islandView.Connect(m_island.ContentIsland());
        m_islandView = winrt::make_weak(islandView);
    }

    void RNCCheckboxComponentView::UpdateProps(
        const winrt::Microsoft::ReactNative::ComponentView& view,
        const winrt::com_ptr<CheckboxCodegen::CheckboxProps>& newProps,
        const winrt::com_ptr<CheckboxCodegen::CheckboxProps>& oldProps) noexcept {
        BaseCheckbox::UpdateProps(view, newProps, oldProps);

        if (!m_checkBox) {
            return;
        }

        m_updating = true;

        // Update value (checked state)
        if (newProps->value.has_value()) {
            m_checkBox.IsChecked(newProps->value.value());
        }

        // Update disabled state
        if (newProps->disabled.has_value()) {
            m_checkBox.IsEnabled(!newProps->disabled.value());
        }

        m_updating = false;

        RefreshSize();
    }

    // Measure checkbox and update state if needed.
    void RNCCheckboxComponentView::RefreshSize() {
        if (!m_checkBox) {
            return;
        }

        m_checkBox.Measure(winrt::Windows::Foundation::Size{
            std::numeric_limits<float>::infinity(),
            std::numeric_limits<float>::infinity()
        });

        auto desiredSize = m_checkBox.DesiredSize();

        if (m_state) {
            auto currentState = winrt::get_self<RNCCheckboxStateData>(m_state.Data());
            if (desiredSize != currentState->desiredSize) {
                m_state.UpdateStateWithMutation([desiredSize](winrt::Windows::Foundation::IInspectable /*data*/) {
                    return winrt::make<RNCCheckboxStateData>(desiredSize);
                });
            }
        }
    }

    void RNCCheckboxComponentView::UpdateState(
        const winrt::Microsoft::ReactNative::ComponentView& /*view*/,
        const winrt::Microsoft::ReactNative::IComponentState& newState) noexcept {
        m_state = newState;
    }

    void RNCCheckboxComponentView::OnCheckedChanged(
        winrt::Windows::Foundation::IInspectable const& /*sender*/,
        winrt::Microsoft::UI::Xaml::RoutedEventArgs const& /*e*/) {
        
        if (m_updating) {
            return;
        }

        if (auto eventEmitter = EventEmitter()) {
            CheckboxCodegen::CheckboxEventEmitter::OnChange args;
            args.value = m_checkBox.IsChecked().GetBoolean();
            eventEmitter->onChange(args);
        }
    }

#endif // defined(RNW_NEW_ARCH)

} // namespace winrt::Checkbox::implementation