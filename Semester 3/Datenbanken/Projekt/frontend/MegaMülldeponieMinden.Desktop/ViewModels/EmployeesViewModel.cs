using ReactiveUI;
using System.Collections.ObjectModel;
using System.Linq;
using MegaMülldeponieMinden.Shared.Models;
using MegaMülldeponieMinden.Shared.Repositories;

namespace MegaMülldeponieMinden.Desktop.ViewModels;

public class EmployeesViewModel : ViewModelBase
{
    private readonly Repository<Employee> repository;
    private readonly Repository<EmployeeKind> kindRepository;

    private Employee? selectedEmployee;
    
    public EmployeesViewModel(
        Repository<Employee> repository,
        Repository<EmployeeKind> kindRepository)
    {
        this.repository = repository;
        this.kindRepository = kindRepository;
        this.EmployeeKinds = new ObservableCollection<EmployeeKind>();
        this.Employees = new ObservableCollection<Employee>();

        Refresh();
    }

    public ObservableCollection<Employee> Employees { get; }
    public ObservableCollection<EmployeeKind> EmployeeKinds { get; }
    public Employee? SelectedEmployee 
    { 
        get => this.selectedEmployee;
        set
        {
            this.RaiseAndSetIfChanged(ref selectedEmployee, value); 
            this.RaisePropertyChanged("SelectedEmployeeKind"); 
        }
    }

    public EmployeeKind? SelectedEmployeeKind
    { 
        get => this.selectedEmployee?.Kind;
        set 
        {
            if (this.selectedEmployee != null) 
            {
                this.selectedEmployee.Kind = value;
                this.RaisePropertyChanged("SelectedEmployeeKind"); 
            }
        }
    }

    public async void Refresh()
    {
        await this.kindRepository.Refresh();
        await this.repository.Refresh();

        this.EmployeeKinds.Clear();
        foreach (var kind in await this.kindRepository.Load())
        {
            this.EmployeeKinds.Add(kind);
        }

        this.Employees.Clear();
        foreach (var employee in await this.repository.Load())
        {
            this.Employees.Add(employee);
        }
    }

    public async void Add()
    {
        this.Employees.Add(new Employee() 
        { 
            Id = -1,
            Address = new Address()
            {
                Id = -1
            },
            Kind = this.EmployeeKinds.FirstOrDefault()
        });
    }

    public async void Save()
    {
        this.repository.Save(this.Employees);
    }

    public async void Delete()
    {
        if (this.SelectedEmployee != null) 
        {
            await this.repository.Delete(this.SelectedEmployee.Id);
            this.Employees.Remove(this.SelectedEmployee);
        }
    }
}
