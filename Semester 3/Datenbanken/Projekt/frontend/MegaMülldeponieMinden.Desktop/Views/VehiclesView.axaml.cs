using Avalonia.Markup.Xaml;
using Avalonia.ReactiveUI;
using MegaMülldeponieMinden.Desktop.ViewModels;

namespace MegaMülldeponieMinden.Desktop.Views;

public class VehiclesView : ReactiveUserControl<VehiclesViewModel>
{
    public VehiclesView()
    {
        AvaloniaXamlLoader.Load(this);
    }
}
