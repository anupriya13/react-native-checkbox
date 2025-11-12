#include "pch.h"

#include "CheckboxView.h"

namespace winrt::Checkbox::implementation
{
void CheckboxComponentView::Initialize(const winrt::Microsoft::ReactNative::ComponentView &view) noexcept {
   m_layoutMetricChangedRevoker = view.LayoutMetricsChanged(
      winrt::auto_revoke,
      [wkThis = get_weak()](
          const winrt::IInspectable & /*sender*/, const winrt::Microsoft::ReactNative::LayoutMetricsChangedArgs &args) {
        if (auto strongThis = wkThis.get()) {
          auto visual = strongThis->m_visual;

          // Turning off default border handling has the side-effect of also stopping the visual from being positioned,
          // so unless that changes we have to position the visual ourselves
          // See https://github.com/microsoft/react-native-windows/issues/14706
          visual.Size(
              {args.NewLayoutMetrics().Frame.Width * args.NewLayoutMetrics().PointScaleFactor,
               args.NewLayoutMetrics().Frame.Height * args.NewLayoutMetrics().PointScaleFactor});
          visual.Offset({
              args.NewLayoutMetrics().Frame.X * args.NewLayoutMetrics().PointScaleFactor,
              args.NewLayoutMetrics().Frame.Y * args.NewLayoutMetrics().PointScaleFactor,
              0.0f,
          });

          auto ellipseGeometry = strongThis->m_visual.Clip()
                                     .as<winrt::Microsoft::UI::Composition::CompositionGeometricClip>()
                                     .Geometry()
                                     .as<winrt::Microsoft::UI::Composition::CompositionEllipseGeometry>();
          winrt::Windows::Foundation::Numerics::float2 radius = {
              args.NewLayoutMetrics().Frame.Width * args.NewLayoutMetrics().PointScaleFactor / 2,
              args.NewLayoutMetrics().Frame.Height * args.NewLayoutMetrics().PointScaleFactor / 2};
          ellipseGeometry.Center(radius);
          ellipseGeometry.Radius(radius);
        }
      });
}

void RegisterCheckboxComponentView(
    winrt::Microsoft::ReactNative::IReactPackageBuilder const &packageBuilder) noexcept {

   CheckboxCodegen::RegisterCheckboxNativeComponent<CheckboxComponentView>(
      packageBuilder,
      [](const winrt::Microsoft::ReactNative::Composition::IReactCompositionViewComponentBuilder &builder) {
        // Turn off default border handling, as it overrides the Clip property of the visual and doesn't render
        // correctly anyway This means we would have to implement drawing our own borders (which we don't do in this
        // example)
        builder.SetViewFeatures(
            winrt::Microsoft::ReactNative::Composition::ComponentViewFeatures::Default &
            ~winrt::Microsoft::ReactNative::Composition::ComponentViewFeatures::NativeBorder);
      });
}

winrt::Microsoft::UI::Composition::Visual CheckboxComponentView::CreateVisual(
    const winrt::Microsoft::ReactNative::ComponentView &view) noexcept {
  auto compositor = view.as<winrt::Microsoft::ReactNative::Composition::ComponentView>().Compositor();

  m_visual = compositor.CreateSpriteVisual();

  auto ellipseGeometry = compositor.CreateEllipseGeometry();
  auto clip = compositor.CreateGeometricClip();
  clip.Geometry(ellipseGeometry);
  m_visual.Clip(clip);

  return m_visual;
}

} // namespace winrt::Checkbox::implementation
