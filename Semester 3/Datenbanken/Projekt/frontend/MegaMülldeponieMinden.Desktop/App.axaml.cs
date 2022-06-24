using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Markup.Xaml;
using MegaMülldeponieMinden.Desktop.ViewModels;
using MegaMülldeponieMinden.Desktop.Views;
using MegaMülldeponieMinden.Shared.Database;
using MegaMülldeponieMinden.Shared.Repositories;

namespace MegaMülldeponieMinden.Desktop
{
    public class App : Application
    {
        public override void Initialize()
        {
            AvaloniaXamlLoader.Load(this);
        }

        public override void OnFrameworkInitializationCompleted()
        {
            if (ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop)
            {
                var connector = new OracleConnector();
                var address = new AddressRepository(connector);
                var kind = new EmployeeKindRepository(connector);
                var employee = new EmployeeRepository(connector, address, kind);
                var depot = new DepotRepository(connector, address);
                var thirdParty = new ThirdPartyRepository(connector, address);
                var fleet = new FleetRepository(connector, address);
                var vehicle = new VehicleRepository(connector, fleet);
                var route = new RouteRepository(connector, depot, employee, thirdParty, vehicle, address);
                var disposalRegulation = new DisposalRegulationRepository(connector);
                var materialKind = new MaterialKindRepository(connector);
                var materialHazard = new MaterialHazardRepository(connector);
                var transportRegulation = new TransportRegulationRepository(connector);
                var material = new MaterialRepository(connector, disposalRegulation, materialKind, materialHazard, transportRegulation);
                
                desktop.MainWindow = new MainWindow
                {
                    DataContext = new MainWindowViewModel(
                        new EmployeesViewModel(employee, kind),
                        new RoutesViewModel(route, employee, depot, thirdParty, vehicle),
                        new VehiclesViewModel(vehicle, fleet),
                        new MaterialsViewModel(material, disposalRegulation, materialKind, materialHazard, transportRegulation)
                    ),
                };
            }

            base.OnFrameworkInitializationCompleted();
        }
    }
}
