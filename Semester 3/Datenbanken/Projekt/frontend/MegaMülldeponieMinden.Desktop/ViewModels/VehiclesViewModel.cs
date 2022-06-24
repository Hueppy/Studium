using ReactiveUI;
using System.Collections.ObjectModel;
using System.Linq;
using System.Threading.Tasks;
using MegaMülldeponieMinden.Shared.Models;
using MegaMülldeponieMinden.Shared.Repositories;

namespace MegaMülldeponieMinden.Desktop.ViewModels;

public class VehiclesViewModel : ViewModelBase
{
    private readonly Repository<Vehicle> repository;
    private readonly Repository<Fleet> fleetRepository;
    private Vehicle? selectedVehicle;
    
    public VehiclesViewModel(
        Repository<Vehicle> repository,
        Repository<Fleet> fleetRepository)
    {
        this.repository = repository;
        this.fleetRepository = fleetRepository;
        this.Vehicles = new ObservableCollection<Vehicle>();
        this.Fleets = new ObservableCollection<Fleet>();

        Refresh();
    }

    public ObservableCollection<Vehicle> Vehicles { get; }
    public ObservableCollection<Fleet> Fleets { get; }
    public Vehicle? SelectedVehicle 
    {
        get => this.selectedVehicle;
        set 
        {
            this.RaiseAndSetIfChanged(ref selectedVehicle, value);
            this.RaisePropertyChanged("SelectedFleet");
        }
    }
    public Fleet? SelectedFleet 
    {
        get => this.selectedVehicle?.Fleet;
        set 
        {
            if (this.selectedVehicle != null) 
            {
                this.selectedVehicle.Fleet = value;
                this.RaisePropertyChanged("SelectedFleet");
            }
        }
    }

    public async void Refresh()
    {
        await this.fleetRepository.Refresh();
        await this.repository.Refresh();

        this.Vehicles.Clear();
        this.Fleets.Clear();
        
        foreach (var fleet in await this.fleetRepository.Load())
        {
            this.Fleets.Add(fleet);
        }

        foreach (var vehicle in await this.repository.Load())
        {
            this.Vehicles.Add(vehicle);
        }
    }

    public async void Add()
    {
        this.Vehicles.Add(new Vehicle() 
        { 
            Id = -1,
            Fleet = this.Fleets.FirstOrDefault()
        });
        this.RaisePropertyChanged("Employees");
    }

    public async void Save()
    {
        this.repository.Save(this.Vehicles);
    }

    public async void Delete()
    {
        if (this.SelectedVehicle != null) 
        {
            await this.repository.Delete(this.SelectedVehicle.Id);
            this.Vehicles.Remove(this.SelectedVehicle);
        }
    }
}
