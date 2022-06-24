using Avalonia.Markup.Xaml;
using Avalonia.ReactiveUI;
using MegaMülldeponieMinden.Desktop.ViewModels;

namespace MegaMülldeponieMinden.Desktop.Views;

public class RoutesView : ReactiveUserControl<RoutesViewModel>
{
    public RoutesView()
    {
        AvaloniaXamlLoader.Load(this);
    }
}
