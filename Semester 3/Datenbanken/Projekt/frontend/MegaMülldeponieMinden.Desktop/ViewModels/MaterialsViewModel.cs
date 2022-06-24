using ReactiveUI;
using System.Collections.ObjectModel;
using System.Linq;
using System.Threading.Tasks;
using MegaMülldeponieMinden.Shared.Models;
using MegaMülldeponieMinden.Shared.Repositories;

namespace MegaMülldeponieMinden.Desktop.ViewModels;

public class MaterialsViewModel : ViewModelBase
{
    private readonly Repository<Material> repository;
    private readonly Repository<DisposalRegulation> disposalRegulationRepository;
    private readonly Repository<MaterialKind> materialKindRepository;
    private readonly Repository<MaterialHazard> materialHazardRepository;
    private readonly Repository<TransportRegulation> transportRegulationRepository;
    private Material? selectedMaterial;
    
    public MaterialsViewModel(
        Repository<Material> repository,
        Repository<DisposalRegulation> disposalRegulationRepository,
        Repository<MaterialKind> materialKindRepository,
        Repository<MaterialHazard> materialHazardRepository,
        Repository<TransportRegulation> transportRegulationRepository)
    {
        this.repository = repository;
        this.disposalRegulationRepository = disposalRegulationRepository;
        this.materialKindRepository = materialKindRepository;
        this.materialHazardRepository = materialHazardRepository;
        this.transportRegulationRepository = transportRegulationRepository;
        this.Materials = new ObservableCollection<Material>();
        this.DisposalRegulations = new ObservableCollection<DisposalRegulation>();
        this.MaterialKinds = new ObservableCollection<MaterialKind>();
        this.MaterialHazards = new ObservableCollection<MaterialHazard>();
        this.TransportRegulations = new ObservableCollection<TransportRegulation>();

        Refresh();
    }

    public ObservableCollection<Material> Materials { get; }
    public ObservableCollection<DisposalRegulation> DisposalRegulations { get; }
    public ObservableCollection<MaterialKind> MaterialKinds { get; }
    public ObservableCollection<MaterialHazard> MaterialHazards { get; }
    public ObservableCollection<TransportRegulation> TransportRegulations { get; }
    public Material? SelectedMaterial 
    {
        get => this.selectedMaterial;
        set 
        {
            this.RaiseAndSetIfChanged(ref selectedMaterial, value);
        }
    }

    public async void Refresh()
    {
        await this.disposalRegulationRepository.Refresh();
        await this.materialKindRepository.Refresh();
        await this.materialHazardRepository.Refresh();
        await this.transportRegulationRepository.Refresh();
        await this.repository.Refresh();

        this.Materials.Clear();
        this.DisposalRegulations.Clear();
        this.MaterialKinds.Clear();
        this.MaterialHazards.Clear();
        this.TransportRegulations.Clear();

        foreach (var disposalRegulation in await this.disposalRegulationRepository.Load())
        {
            this.DisposalRegulations.Add(disposalRegulation);
        }

        foreach (var materialKind in await this.materialKindRepository.Load())
        {
            this.MaterialKinds.Add(materialKind);
        }

        foreach (var materialHazard in await this.materialHazardRepository.Load())
        {
            this.MaterialHazards.Add(materialHazard);
        }

        foreach (var transportRegulation in await this.transportRegulationRepository.Load())
        {
            this.TransportRegulations.Add(transportRegulation);
        }

        foreach (var employee in await this.repository.Load())
        {
            this.Materials.Add(employee);
        }
    }

    public async void Add()
    {
        this.Materials.Add(new Material() 
        { 
            Id = -1,
            DisposalRegulation = this.DisposalRegulations.FirstOrDefault(),
            MaterialKind = this.MaterialKinds.FirstOrDefault(),
            MaterialHazard = this.MaterialHazards.FirstOrDefault(),
            TransportRegulation = this.TransportRegulations.FirstOrDefault()
        });
        this.RaisePropertyChanged("Material");
    }

    public async void Save()
    {
        this.repository.Save(this.Materials);
    }

    public async void Delete()
    {
        if (this.SelectedMaterial != null) 
        {
            await this.repository.Delete(this.SelectedMaterial.Id);
            this.Materials.Remove(this.SelectedMaterial);
        }
    }
}
