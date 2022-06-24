using Avalonia.Markup.Xaml;
using Avalonia.ReactiveUI;
using MegaMülldeponieMinden.Desktop.ViewModels;

namespace MegaMülldeponieMinden.Desktop.Views;

public class MaterialsView : ReactiveUserControl<MaterialsViewModel>
{
    public MaterialsView()
    {
        AvaloniaXamlLoader.Load(this);
    }
}
