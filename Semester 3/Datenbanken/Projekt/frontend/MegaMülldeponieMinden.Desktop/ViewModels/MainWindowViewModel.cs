using System;
using System.Collections.Generic;
using System.Text;

namespace MegaMülldeponieMinden.Desktop.ViewModels
{
    public class MainWindowViewModel : ViewModelBase
    {
        public MainWindowViewModel(
            EmployeesViewModel employeesViewModel,
            RoutesViewModel routesViewModel,
            VehiclesViewModel vehiclesViewModel,
            MaterialsViewModel materialsViewModel)
        {
            this.EmployeesViewModel = employeesViewModel;
            this.RoutesViewModel = routesViewModel;
            this.VehiclesViewModel = vehiclesViewModel;
            this.MaterialsViewModel = materialsViewModel;
        }
        
        public EmployeesViewModel EmployeesViewModel { get; }
        public RoutesViewModel RoutesViewModel { get; }
        public VehiclesViewModel VehiclesViewModel { get; }
        public MaterialsViewModel MaterialsViewModel { get; }
    }
}
