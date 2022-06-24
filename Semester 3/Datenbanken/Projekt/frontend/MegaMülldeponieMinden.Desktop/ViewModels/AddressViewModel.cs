using System.Collections.ObjectModel;
using System.Threading.Tasks;
using MegaMülldeponieMinden.Shared.Models;
using MegaMülldeponieMinden.Shared.Repositories;

namespace MegaMülldeponieMinden.Desktop.ViewModels;

public class AddressViewModel : ViewModelBase
{
    private readonly Repository<Address> repository;
    
    public AddressViewModel(Repository<Address> repository)
    {
        this.repository = repository;
        this.Addresses = new ObservableCollection<Address>();
    }

    public ObservableCollection<Address> Addresses { get; }

    public async void Refresh()
    {
        this.Addresses.Clear();
        foreach (var address in await this.repository.Load())
        {
            this.Addresses.Add(address);
        }
    }
}
