using ReactiveUI;
using System.Collections.ObjectModel;
using System.Linq;
using System.Threading.Tasks;
using MegaMülldeponieMinden.Shared.Models;
using MegaMülldeponieMinden.Shared.Repositories;

namespace MegaMülldeponieMinden.Desktop.ViewModels;

public class RoutesViewModel : ViewModelBase
{
    private readonly Repository<Route> repository;
    private readonly Repository<Employee> employeeRepository;
    private readonly Repository<Depot> depotRepository;
    private readonly Repository<ThirdParty> thirdPartyRepository;
    private readonly Repository<Vehicle> vehicleRepository;
    private Route? selectedRoute;
    
    public RoutesViewModel(
        Repository<Route> repository,
        Repository<Employee> employeeRepository,
        Repository<Depot> depotRepository,
        Repository<ThirdParty> thirdPartyRepository,
        Repository<Vehicle> vehicleRepository)
    {
        this.repository = repository;
        this.employeeRepository = employeeRepository;
        this.depotRepository = depotRepository;
        this.thirdPartyRepository = thirdPartyRepository;
        this.vehicleRepository = vehicleRepository;
        this.Routes = new ObservableCollection<Route>();
        this.Employees = new ObservableCollection<Employee>();
        this.Depots = new ObservableCollection<Depot>();
        this.ThirdParties = new ObservableCollection<ThirdParty>();
        this.Vehicles = new ObservableCollection<Vehicle>();

        Refresh();
    }

    public ObservableCollection<Route> Routes { get; }
    public ObservableCollection<Employee> Employees { get; }
    public ObservableCollection<Depot> Depots { get; }
    public ObservableCollection<ThirdParty> ThirdParties { get; }
    public ObservableCollection<Vehicle> Vehicles { get; }
    public Route? SelectedRoute 
    {
        get => this.selectedRoute;
        set 
        {
            this.RaiseAndSetIfChanged(ref selectedRoute, value);
            this.RaisePropertyChanged("SelectedDepot");
        }
    }
    public Depot? SelectedDepot 
    {
        get => this.selectedRoute?.Depot;
        set 
        {
            if (this.selectedRoute != null) 
            {
                this.selectedRoute.Depot = value;
                this.RaisePropertyChanged("SelectedDepot");
            }
        }
    }

    public async void Refresh()
    {
        await this.employeeRepository.Refresh();
        await this.depotRepository.Refresh();
        await this.thirdPartyRepository.Refresh();
        await this.repository.Refresh();

        this.Employees.Clear();
        foreach (var employee in await this.employeeRepository.Load())
        {
            this.Employees.Add(employee);
        }

        this.Depots.Clear();
        foreach (var depot in await this.depotRepository.Load())
        {
            this.Depots.Add(depot);
        }

        this.ThirdParties.Clear();
        foreach (var thirdParty in await this.thirdPartyRepository.Load())
        {
            this.ThirdParties.Add(thirdParty);
        }

        this.Vehicles.Clear();
        foreach (var vehicle in await this.vehicleRepository.Load())
        {
            this.Vehicles.Add(vehicle);
        }

        this.Routes.Clear();
        foreach (var route in await this.repository.Load())
        {
            this.Routes.Add(route);
        }
    }

    public async void Add()
    {
        this.Routes.Add(new Route() 
        { 
            Id = -1,
            Employee = this.Employees.FirstOrDefault(),
            Depot = this.Depots.FirstOrDefault(),
            ThirdParty = this.ThirdParties.FirstOrDefault(),
            Vehicle = this.Vehicles.FirstOrDefault()
        });
    }

    public async void Save()
    {
        this.repository.Save(this.Routes);
    }

    public async void Delete()
    {
        if (this.SelectedRoute != null) 
        {
            await this.repository.Delete(this.SelectedRoute.Id);
            this.Routes.Remove(this.SelectedRoute);
        }
    }
}
