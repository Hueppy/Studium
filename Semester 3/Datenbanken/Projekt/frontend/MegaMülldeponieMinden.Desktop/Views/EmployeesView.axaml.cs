using Avalonia.Markup.Xaml;
using Avalonia.ReactiveUI;
using MegaMülldeponieMinden.Desktop.ViewModels;

namespace MegaMülldeponieMinden.Desktop.Views;

public class EmployeesView : ReactiveUserControl<EmployeesViewModel>
{
    public EmployeesView()
    {
        AvaloniaXamlLoader.Load(this);
    }
}
